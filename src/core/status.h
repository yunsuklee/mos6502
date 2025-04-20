#ifndef STATUS_H
#define STATUS_H

#include <stdbool.h>
#include <stdint.h>

/* Common bit masks used for CPU operations */
#define BIT_0           	0x01    /* Least significant bit (rightmost) */
#define BIT_7           	0x80    /* Sign bit in an 8-bit value */
#define BIT_8           	0x100   /* Carry bit for 8-bit operations */

/**
 * CPU Status Register Flag Bits
 * Each flag represents a specific condition in the 6502 processor
 */
typedef enum {
    FLAG_CARRY              = 0x01, /* Bit 0: Carry flag */
    FLAG_ZERO               = 0x02, /* Bit 1: Zero flag */
    FLAG_INTERRUPT_DISABLE  = 0x04, /* Bit 2: Interrupt disable flag */
    FLAG_DECIMAL            = 0x08, /* Bit 3: Decimal mode flag */
    FLAG_BREAK              = 0x10, /* Bit 4: Break command flag */
    FLAG_UNUSED             = 0x20, /* Bit 5: Unused, always set to 1 in PHP/BRK */
    FLAG_OVERFLOW           = 0x40, /* Bit 6: Overflow flag */
    FLAG_NEGATIVE           = 0x80, /* Bit 7: Negative flag */
} status_flag_t;

bool status_get_flag(const uint8_t *reg, status_flag_t flag);
void status_set_flag(uint8_t *reg, status_flag_t flag, bool status);
void status_set_carry_flag(uint8_t *reg, uint16_t result);
void status_set_zero_flag(uint8_t *reg, uint8_t result);
void status_set_overflow_flag(uint8_t *reg, uint8_t operand_a, uint8_t operand_b, uint8_t result);
void status_set_negative_flag(uint8_t *reg, uint8_t result);
void status_rotate_left(uint8_t *reg, uint8_t *value);
void status_rotate_right(uint8_t *reg, uint8_t *value);

#endif