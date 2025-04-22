#include "Constants.h"
#include "GPIO.h"

void setup() {
  set_pinmode(12, OUTPUT);
}

void loop() {
  digital_write(12, HIGH);
  delay(1000);
  digital_write(12, LOW);
  delay(1000);

  analogWrite
}

