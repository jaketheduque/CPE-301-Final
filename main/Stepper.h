#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>
#include "GPIO.h"

class Stepper {
  private:
    byte step;
    int steps_per_revolution;

    byte blue_wire;
    byte pink_wire;
    byte yellow_wire;
    byte orange_wire;

    void energize_step(byte step);
  public:
    Stepper(int steps_per_revolution, byte blue_wire, byte pink_wire, byte yellow_wire, byte orange_wire);
    void cw_step();
    void ccw_step();
    void rotate(int rotations);
};

#endif