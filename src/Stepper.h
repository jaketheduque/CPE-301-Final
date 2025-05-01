#ifndef STEPPER_H
#define STEPPER_H

#include <inttypes.h>
#include <stdlib.h>
#include <util/delay.h>

#include "GPIO.h"
#include "Timer.h"

class Stepper {
  private:
    uint8_t step;
    uint32_t steps_per_revolution;

    uint8_t blue_wire;
    uint8_t pink_wire;
    uint8_t yellow_wire;
    uint8_t orange_wire;

    void energize_step(uint8_t step);
  public:
    Stepper(uint32_t steps_per_revolution, uint8_t blue_wire, uint8_t pink_wire, uint8_t yellow_wire, uint8_t orange_wire);
    void cw_step();
    void ccw_step();
    void rotate(uint32_t rotations);
};

#endif