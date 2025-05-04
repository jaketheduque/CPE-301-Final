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

// steps_per_revolution, blue_wire, pink_wire, yellow_wire, orange_wire
Stepper stepper = Stepper(2048, 4, 5, 6, 7);
DHT11 sensor = DHT11(8);
Display display = Display(53, 51, 49, 47, 45, 43, 41, 39, 37, 35);

void setup() {
  sei();
  setup_timers();

  // 103 comes from pg. 226
  Serial::begin_serial(0, 103);

  I2C::begin();

  display.init();
}

void loop() {
  display.clear();
  display.set_cursor(0, 5);
  display.print("abc");
  display.set_cursor(1, 5);
  display.print("def");

  delay(1000);
}

int main() {
  setup();

  while (1) {
    loop();
  }

  return 0;
}