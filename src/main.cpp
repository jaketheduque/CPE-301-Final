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
}

void loop() {
  DHT11Data data = sensor.getData();
  int8_t value = data.int_temp;
  printChar(0, value);

  // while (value > 0) {
  //   char digit = value % 10;

  //   printChar(0, (digit + 30));

  //   if (value < 10) {
  //     break;
  //   }

  //   value /= 10;
  // }
  // printChar(0, '\n');
}

int main() {
  setup();

  while (1) {
    loop();
  }

  return 0;
}