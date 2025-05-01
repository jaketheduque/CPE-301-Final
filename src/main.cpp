#include <stdio.h>

#include "MyArduino.h"
#include "GPIO.h"
#include "Stepper.h"
#include "Timer.h"
#include "Serial.h"
#include "DHT11.h"

// steps_per_revolution, blue_wire, pink_wire, yellow_wire, orange_wire
Stepper stepper = Stepper(2048, 4, 5, 6, 7);
DHT11 sensor = DHT11(8);

void setup() {
  sei();
  setup_timers();

  // 103 comes from pg. 226
  begin_serial(0, 103);

  sensor.begin();
}

void loop() {
  char buffer[32];
  sprintf(buffer, "Temp: %d - RH: %d", sensor.getTemperature(), sensor.getHumidity());
  println(0, buffer);

  delay(1000);
}

int main() {
  setup();

  while (1) {
    loop();
  }

  return 0;
}