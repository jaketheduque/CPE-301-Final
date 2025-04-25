#include "Constants.h"
#include "GPIO.h"
#include "Stepper.h"

// steps_per_revolution, blue_wire, pink_wire, yellow_wire, orange_wire
Stepper stepper = Stepper(2048, 4, 5, 6, 7);

void setup() {
}

void loop() {
  stepper.rotate(1);
}

