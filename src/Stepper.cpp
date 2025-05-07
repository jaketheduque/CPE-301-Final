#include "Stepper.h"

Stepper::Stepper(uint32_t steps_per_revolution, uint8_t blue_wire, uint8_t pink_wire, uint8_t yellow_wire, uint8_t orange_wire) {
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

void Stepper::energize_step(uint8_t step) {
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

void Stepper::rotate(double rotations) {
  uint32_t num_steps = abs(rotations * steps_per_revolution);

  if (rotations < 0) {
    for (uint32_t i = 0 ; i < num_steps ; i++) {
      ccw_step();
      _delay_ms(2);
    }
  } else if (rotations > 0) {
    for (uint32_t i = 0 ; i < num_steps ; i++) {
      cw_step();
      _delay_ms(2);
    }
  }
}
