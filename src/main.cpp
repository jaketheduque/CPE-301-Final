#include <stdio.h>
#include <time.h>

#include "MyArduino.h"
#include "GPIO.h"
#include "Stepper.h"
#include "Timer.h"
#include "Serial.h"
#include "DHT11.h"
#include "I2C.h"
#include "DS1307.h"
#include "Display.h"
#include "WaterSensor.h"

enum State {
  DISABLED,
  IDLE,
  ERROR,
  RUNNING
};

#define RESET_BUTTON 2
#define MOTOR_PIN 9
#define BLUE_LED 23
#define GREEN_LED 25
#define YELLOW_LED 27
#define RED_LED 29

#define POT_CHANNEL 0
#define WATER_SENSOR_CHANNEL 1

#define TEMP_THRESHOLD 30
#define WATER_LEVEL_THRESHOLD 50
#define MIN_STEPPER_ROTATION 0.05
#define DEBOUNCE_TIME 30

#define DISPLAY_UPDATE_INTERVAL ((uint64_t) (60L * 1000L))

// steps_per_revolution, blue_wire, pink_wire, yellow_wire, orange_wire
Stepper stepper = Stepper(2048, 4, 5, 6, 7);
DHT11 sensor = DHT11(8);
WaterSensor water_sensor = WaterSensor(10, 1);
Display display = Display(53, 51, 49, 47, 45, 43, 41, 39, 37, 35);

float current_vent_position = 0.0;
uint64_t last_display_update = 0;
State last_state_actioned = IDLE;
State current_state = IDLE;

char *prepend_time(const char* data);
void update_current_temp_humidity();

void update_current_state();
void action_current_state();
void update_vent_position();

ISR(INT4_vect) {
  static uint64_t last_interrupt_time = 0;
  if (millis() - last_interrupt_time > DEBOUNCE_TIME) {
    if (water_sensor.read() >= WATER_LEVEL_THRESHOLD) {
      if (current_state == ERROR) {
        current_state = IDLE;
      } else if (current_state == DISABLED) {
        current_state = IDLE;
      } else {
        current_state = DISABLED;
      }
    } else {
      current_state = ERROR;
    }
  }
  last_interrupt_time = millis();
}

void setup() {
  sei();
  setup_timers();

  // 103 comes from pg. 226
  Serial::begin_serial(0, 103);
  I2C::begin();
  display.init();
  analog_init();

  // enable falling edge interrupt for digital pin 2
  sbi(EICRB, ISC41);
  sbi(EIMSK, INT4);

  set_pinmode(MOTOR_PIN, OUTPUT);
  set_pinmode(BLUE_LED, OUTPUT);
  set_pinmode(RED_LED, OUTPUT);
  set_pinmode(YELLOW_LED, OUTPUT);
  set_pinmode(GREEN_LED, OUTPUT);
  set_pinmode(RESET_BUTTON, INPUT_PULLUP);

  // start off in IDLE
  digital_write(GREEN_LED, HIGH);
}

void loop() {
  update_current_state();
  action_current_state();

  if (current_state == IDLE || current_state == RUNNING) {
    update_vent_position();

    // print humidity and temperature
    if (current_state != DISABLED && current_state != ERROR) {
      if ((millis() - last_display_update > DISPLAY_UPDATE_INTERVAL) || (last_display_update == 0)) {
        update_current_temp_humidity();
        last_display_update = millis();
      }
    }
  }

  delay(100);
}

int main() {
  setup();

  while (1) {
    loop();
  }

  return 0;
}

char *prepend_time(const char* data) {
  tm current_time = DS1307::getDatetime();
  char time[64];
  strftime(time, sizeof(time), "(%H:%M:%S) ", &current_time);
  return strcat(time, data);
}

void update_current_temp_humidity() {
  tm current_time = DS1307::getDatetime();
  char time[64];
  strftime(time, sizeof(time), "%H:%M", &current_time);

  char buffer[64];
  sprintf(buffer, "%d%% | %d C", sensor.getHumidity(), sensor.getTemperature());
  
  display.clear();
  display.set_cursor(0, 5);
  display.print(time);
  display.set_cursor(1, 3);
  display.print(buffer);
}

void update_current_state() {
  if (current_state == DISABLED || current_state == ERROR) {
    return;
  } else if (water_sensor.read() < WATER_LEVEL_THRESHOLD) {
    current_state = ERROR;
  } else if (sensor.getTemperature() >= TEMP_THRESHOLD) {
    current_state = RUNNING;
  } else {
    current_state = IDLE;
  }
}

void action_current_state() {
  if (current_state == last_state_actioned) {
    return;
  }

  switch (current_state) {
    case ERROR:
      Serial::println(0, prepend_time("State changed to ERROR"));

      digital_write(MOTOR_PIN, LOW);

      digital_write(YELLOW_LED, LOW);
      digital_write(RED_LED, HIGH);
      digital_write(BLUE_LED, LOW);
      digital_write(GREEN_LED, LOW);

      display.clear();
      display.print("Water level");
      display.set_cursor(1, 0);
      display.print("too low!");
      break;
    case DISABLED:
      Serial::println(0, prepend_time("State changed to DISABLED"));
      current_state = DISABLED;

      digital_write(YELLOW_LED, HIGH);
      digital_write(RED_LED, LOW);
      digital_write(BLUE_LED, LOW);
      digital_write(GREEN_LED, LOW);

      digital_write(MOTOR_PIN, LOW);

      display.clear();
      display.print("Disabled!");

      break;
    case IDLE:
      Serial::println(0, prepend_time("State changed to IDLE"));

      digital_write(YELLOW_LED, LOW);
      digital_write(RED_LED, LOW);
      digital_write(BLUE_LED, LOW);
      digital_write(GREEN_LED, HIGH);

      digital_write(MOTOR_PIN, LOW);

      update_current_temp_humidity();
      last_display_update = millis();
      break;
    case RUNNING:
      Serial::println(0, prepend_time("State changed to RUNNING"));

      digital_write(YELLOW_LED, LOW);
      digital_write(RED_LED, LOW);
      digital_write(BLUE_LED, HIGH);
      digital_write(GREEN_LED, LOW);

      digital_write(MOTOR_PIN, HIGH);

      update_current_temp_humidity();
      last_display_update = millis();
      break;
  }

  last_state_actioned = current_state;
}

void update_vent_position() {
  uint8_t pot_value = analog_read(POT_CHANNEL);
  float new_vent_position = ((float) pot_value / (float) 255);

  if (fabs(new_vent_position - current_vent_position) > MIN_STEPPER_ROTATION) {
    stepper.rotate(new_vent_position - current_vent_position);
    current_vent_position = new_vent_position;
  }
}