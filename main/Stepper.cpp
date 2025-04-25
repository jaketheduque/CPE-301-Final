#include "Stepper.h"

Stepper::Stepper(int steps_per_revolution, byte blue_wire, byte pink_wire, byte yellow_wire, byte orange_wire) {
  this->steps_per_revolution = steps_per_revolution;
  this->step = 0;
  this->blue_wire = blue_wire;
  this->pink_wire = pink_wire;
  this->yellow_wire = yellow_wire;
  this->orange_wire = orange_wire;

  set_pinmode(blue_wire, OUTPUT);
  set_pinmode(pink_wire, OUTPUT);
  set_pinmode(yellow_wire, OUTPUT);
  set_pinmode(orange_wire, OUTPUT);
}

void Stepper::energize_step(byte step) {
  switch (step) {
    case 0:
      digital_write(blue_wire, HIGH);
      digital_write(pink_wire, HIGH);
      digital_write(yellow_wire, LOW);
      digital_write(orange_wire, LOW);
      return;
    case 1:
      digital_write(blue_wire, LOW);
      digital_write(pink_wire, HIGH);
      digital_write(yellow_wire, HIGH);
      digital_write(orange_wire, LOW);
      return;
    case 2:
      digital_write(blue_wire, LOW);
      digital_write(pink_wire, LOW);
      digital_write(yellow_wire, HIGH);
      digital_write(orange_wire, HIGH);
      return;
    case 3:
      digital_write(blue_wire, HIGH);
      digital_write(pink_wire, LOW);
      digital_write(yellow_wire, LOW);
      digital_write(orange_wire, HIGH);
      return;
  }
}

void Stepper::cw_step() {
  if (step == 3) {
    step = 0;
  } else {
    step++;
  }

  energize_step(step);
}

void Stepper::ccw_step() {
  if (step == 0) {
    step = 3;
  } else {
    step--;
  }

  energize_step(step);
}

void Stepper::rotate(int rotations) {
  int num_steps = abs(rotations * steps_per_revolution);

  if (rotations < 0) {
    for (int i = 0 ; i < num_steps ; i++) {
      ccw_step();
      delay(2); // TODO implement own delay function
    }
  } else if (rotations > 0) {
    for (int i = 0 ; i < num_steps ; i++) {
      cw_step();
      delay(2);
    }
  }
}
