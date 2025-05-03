#include "DS1307.h"

tm DS1307::getDatetime() {
    I2C::start(0b11010000); // start in write mode
    I2C::sendByte(0x00); // point to seconds register

    I2C::repeatStart(0b11010001); // start in read mode
    tm datetime;
    uint8_t reg_value;

    // get seconds
    reg_value = I2C::receiveByte();
    datetime.tm_sec = (reg_value & 0x0F); // save ones place
    datetime.tm_sec += 10 * ((reg_value >> 4) & 0x07); // save tens place (bit 7 is CH bit and masked out)

    // get minutes
    reg_value = I2C::receiveByte();
    datetime.tm_min = (reg_value & 0x0F); // save ones place
    datetime.tm_min += 10 * (reg_value >> 4); // save tens place

    // get hours
    reg_value = I2C::receiveByte();
    datetime.tm_hour = (reg_value & 0x0F); // save ones place
    datetime.tm_hour += 10 * (reg_value >> 4); // save tens place

    // get day of the week
    datetime.tm_wday = I2C::receiveByte();

    // get day of the year
    reg_value = I2C::receiveByte();
    datetime.tm_mday = (reg_value & 0x0F); // save ones place
    datetime.tm_mday += 10 * (reg_value >> 4); // save tens place

    // get month
    reg_value = I2C::receiveByte();
    datetime.tm_mon = (reg_value & 0x0F); // save ones place
    datetime.tm_mon += 10 * (reg_value >> 4); // save tens place
    datetime.tm_mon -= 1; // move down one so that January is 0

    // get year
    reg_value = I2C::receiveLastByte();
    datetime.tm_year = (reg_value & 0x0F); // save ones place
    datetime.tm_year += 10 * (reg_value >> 4); // save tens place
    datetime.tm_year += 100; // add 100 to be from 2000 instead of 1900

    I2C::stop();

    return datetime;
}

// takes in ISO8601 formatted string (YYYY-MM-DDTHH-mm-ss)
void DS1307::setDateTime(char input[20]) {
    // parse input
    uint8_t seconds, minutes, hours, month, day;
    uint16_t year;
    sscanf(input, "%hu-%hhu-%hhuT%hhu:%hhu:%hhu", &year, &month, &day, &hours, &minutes, &seconds);

    // modify values to match register formatting
    uint8_t seconds_reg, minutes_reg, hours_reg, month_reg, day_reg, year_reg;
    seconds_reg = (seconds % 10);
    seconds_reg |= ((seconds / 10) << 4);
    seconds_reg = 0b00110000;

    minutes_reg = (minutes % 10);
    minutes_reg |= ((minutes / 10) << 4);

    hours_reg = (hours % 10);
    hours_reg |= ((hours / 10) << 4);
    
    month_reg = (month % 10);
    month_reg |= ((month / 10) << 4);

    day_reg = (day % 10);
    day_reg |= ((day / 10) << 4);

    year %= 100;
    year_reg = (year % 10);
    year_reg |= ((year / 10) << 4);

    I2C::start(0b11010000); // start in write mode

    // this is probably useless since it is writing to the minutes register for some reason???
    I2C::sendByte(0x00); // point to seconds register
    I2C::sendByte(0x80); // stop the clock to prevent any race conditions

    I2C::repeatStart(0b11010000); // start in write mode
    I2C::sendByte(0x01); // point to minutes register
    I2C::sendByte(minutes_reg);
    I2C::sendByte(hours_reg);
    I2C::sendByte(0x00); // day of the week register
    I2C::sendByte(day_reg);
    I2C::sendByte(month_reg);
    I2C::sendByte(year_reg);

    // for SOME reason, when seconds is written to 0x00, it ends up overwriting the minutes register T_T
    // I2C::repeatStart(0b11010000); // start in write mode
    // I2C::sendByte(0x00); // point to seconds register
    // I2C::sendByte(seconds_reg); // write seconds register (restarting clock in the process)
    I2C::stop();
}