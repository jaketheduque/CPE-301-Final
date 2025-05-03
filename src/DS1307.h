#ifndef DS1307_H
#define DS1307_H

#include <time.h>
#include <stdio.h>

#include "Serial.h"
#include "I2C.h"

class DS1307 {
    public:
        static tm getDatetime();

        // takes in ISO8601 formatted string
        static void setDateTime(char input[20]);
};

#endif