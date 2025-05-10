#ifndef DISPLAY_H
#define DISPLAY_H

#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "Serial.h"
#include "GPIO.h"

/**
 * https://github.com/krovma/LCD1602/tree/master used as a reference for debugging
 */
class Display {
    private:
        uint8_t rs;
        // with rw pin tied to ground, always in write mode
        uint8_t en;
        uint8_t db0, db1, db2, db3, db4, db5, db6, db7;

        void enable();
        void send_instruction(uint8_t data);
        void print_char(const uint8_t data);
    public:
        Display(uint8_t rs, uint8_t en, uint8_t db0, uint8_t db1, uint8_t db2, uint8_t db3, uint8_t db4, uint8_t db5, uint8_t db6, uint8_t db7);

        void init();
        void display_switch(bool display, bool cursor, bool blink);
        void set_cursor(uint8_t row, uint8_t col);
        void print(const char *data);
        void clear();
};

#endif