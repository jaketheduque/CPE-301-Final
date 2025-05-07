#include "Display.h"

Display::Display(uint8_t rs, uint8_t en, uint8_t db0, uint8_t db1, uint8_t db2, uint8_t db3, uint8_t db4, uint8_t db5, uint8_t db6, uint8_t db7) {
    this->rs = rs;
    this->en = en;
    this->db0 = db0;
    this->db1 = db1;
    this->db2 = db2;
    this->db3 = db3;
    this->db4 = db4;
    this->db5 = db5;
    this->db6 = db6;
    this->db7 = db7;

    set_pinmode(rs, OUTPUT);
    set_pinmode(en, OUTPUT);
    set_pinmode(db0, OUTPUT);
    set_pinmode(db1, OUTPUT);
    set_pinmode(db2, OUTPUT);
    set_pinmode(db3, OUTPUT);
    set_pinmode(db4, OUTPUT);
    set_pinmode(db5, OUTPUT);
    set_pinmode(db6, OUTPUT);
    set_pinmode(db7, OUTPUT);

    digital_write(en, 0);
    digital_write(db7, 0);
    digital_write(db6, 0);
    digital_write(db5, 0);
    digital_write(db4, 0);
    digital_write(db3, 0);
    digital_write(db2, 0);
    digital_write(db1, 0);
    digital_write(db0, 0);
}

void Display::enable() {
    digital_write(en, 1);
    _delay_us(20);
    digital_write(en, 0);
}

void Display::send_instruction(uint8_t data) {
    digital_write(rs, 0);

    digital_write(db7, (data & 0x80));
    digital_write(db6, (data & 0x40));
    digital_write(db5, (data & 0x20));
    digital_write(db4, (data & 0x10));
    digital_write(db3, (data & 0x08));
    digital_write(db2, (data & 0x04));
    digital_write(db1, (data & 0x02));
    digital_write(db0, (data & 0x01));

    enable();
}

void Display::print_char(uint8_t data) {
    _delay_ms(5);

    digital_write(rs, 1);

    digital_write(db7, (data & 0x80));
    digital_write(db6, (data & 0x40));
    digital_write(db5, (data & 0x20));
    digital_write(db4, (data & 0x10));
    digital_write(db3, (data & 0x08));
    digital_write(db2, (data & 0x04));
    digital_write(db1, (data & 0x02));
    digital_write(db0, (data & 0x01));

    enable();
}

void Display::init() {
    _delay_ms(20);
    send_instruction(0x38);

    _delay_ms(5);
    send_instruction(0x38);

    _delay_us(150);
    send_instruction(0x38);

    // display on, cursor off, blinking off
    display_switch(1, 0, 0);

    clear();
}

void Display::display_switch(bool display, bool cursor, bool blink) {
    uint8_t instruction = 0x00;
    instruction |= 0x08;
    instruction |= (display << 2);
    instruction |= (cursor << 1);
    instruction |= (blink << 0);

    send_instruction(instruction);
}

void Display::set_cursor(uint8_t row, uint8_t col) {
    if (row == 0) {
        send_instruction(0x80 | col);
    } else {
        send_instruction(0xC0 | col);
    }
}

void Display::print(const char *data) {
    for (uint8_t i = 0 ; i < strlen(data) ; i++) {
        print_char(data[i]);
    }
}

void Display::clear() {
    _delay_ms(5);
    send_instruction(0x01);
    _delay_ms(5);
}