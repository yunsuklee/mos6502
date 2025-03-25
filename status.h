#ifndef STATUS
#define STATUS

#include <stdbool.h>
#include <stdint.h>

typedef enum {
	CARRY 				= 0x01,
	ZERO  				= 0x02, 
	INTERRUPT_DISABLE 	= 0x04,
	DECIMAL				= 0x08,
	BREAK				= 0x10,
	OVERFLOW 			= 0x40,
	NEGATIVE 			= 0x80,
} flag_t;

bool get_status(uint8_t *reg, flag_t flag);
void set_status(uint8_t *reg, flag_t flag, bool status);
void set_carry(uint8_t *reg, uint16_t res);
void set_zero(uint8_t *reg, uint8_t res);
void set_overflow(uint8_t *reg, uint8_t a, uint8_t b, uint8_t res);
void set_negative(uint8_t *reg, uint8_t res);
void rotate_left(uint8_t *reg, uint8_t *x);
void rotate_right(uint8_t *reg, uint8_t *x);

#endif