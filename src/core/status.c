#include "status.h"

bool status_get_flag(const uint8_t *reg, status_flag_t flag) {
    return (*reg & flag) != 0;
}

void status_set_flag(uint8_t *reg, status_flag_t flag, bool status) {
    if(status)
        *reg |= flag;
    else
        *reg &= ~flag;
}

void status_set_carry_flag(uint8_t *reg, uint16_t result) {
    status_set_flag(reg, FLAG_CARRY, (result & BIT_8) != 0);
}

void status_set_zero_flag(uint8_t *reg, uint8_t result) {
    status_set_flag(reg, FLAG_ZERO, result == 0);
}

void status_set_overflow_flag(uint8_t *reg, uint8_t operand_a, uint8_t operand_b, uint8_t result) {
    /*
    * Set the overflow flag when:
    * 1. Both operands have the same sign bit (both positive or both negative)
    * 2. The result's sign bit differs from the operands' sign bit
    *
    * This detects a signed overflow in two's complement arithmetic
    */
   bool operands_same_sign = ((operand_a & BIT_7) == (operand_b & BIT_7));
   bool result_diff_sign = ((operand_b & BIT_7) != (result & BIT_7));

   status_set_flag(reg, FLAG_OVERFLOW, operands_same_sign && result_diff_sign);
}

void status_set_negative_flag(uint8_t *reg, uint8_t result) {
    status_set_flag(reg, FLAG_NEGATIVE, (result & BIT_7) != 0);
}

void status_rotate_left(uint8_t *reg, uint8_t *value) {
    bool is_high_bit_set = (*value & BIT_7) != 0;

    *value <<= 1;

    if(status_get_flag(reg, FLAG_CARRY))
        *value |= BIT_0;

    status_set_flag(reg, FLAG_CARRY, is_high_bit_set);
}

void status_rotate_right(uint8_t *reg, uint8_t *x) {
    bool is_low_bit_set = (*x & BIT_0) != 0;

    *x >>= 1;

    if(status_get_flag(reg, FLAG_CARRY))
        *x |= BIT_7;

    status_set_flag(reg, FLAG_CARRY, is_low_bit_set);
}