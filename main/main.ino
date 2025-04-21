#include "Constants.h"
#include "GPIO.h"

void setup() {
  set_pinmode(12, OUTPUT);
}

void loop() {
  write(12, HIGH);
  delay(1000);
  write(12, LOW);
  delay(1000);
}

