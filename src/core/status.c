#include "status.h"

bool get_status(uint8_t *reg, flag_t flag) {
    return (*reg & flag);
}

void set_status(uint8_t *reg, flag_t flag, bool status) {
    if(status)
        *reg |= flag;
    else
        *reg &= (~flag);
}

void set_zero(uint8_t *reg, uint8_t res) {
    set_status(reg, ZERO, res == 0);
}

void set_negative(uint8_t *reg, uint8_t res) {
    set_status(reg, NEGATIVE, res & 0x80);
}

void set_carry(uint8_t *reg, uint16_t res) {
    set_status(reg, CARRY, res & 0x100);
}

void set_overflow(uint8_t *reg, uint8_t a, uint8_t b, uint8_t res) {
    set_status(reg, OVERFLOW, ((a & 0x80) == (b & 0x80)) && ((a & 0x80) != (res & 0x80)));
}

void rotate_left(uint8_t *reg, uint8_t *x) {
    uint8_t bit_caido = (*x & 0x80);
    *x <<= 1; 

    if(get_status(reg, CARRY))
        *x |= 0x01;

    set_status(reg, CARRY, bit_caido);
}

void rotate_right(uint8_t *reg, uint8_t *x) {
    uint8_t bit_caido = (*x & 0x01);
    *x >>= 1;

    if(get_status(reg, CARRY))
        *x |= 0x80;

    set_status(reg, CARRY, bit_caido);
}