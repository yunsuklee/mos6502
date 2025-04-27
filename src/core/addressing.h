#ifndef ADDRESSING_H
#define ADDRESSING_H

#include <stdint.h>
#include "cpu.h"

#define BYTE_MASK           0xFF
#define HIGH_BYTE_MASK      0xFF00
#define ZERO_PAGE_MASK      0xFF
#define BIT_SHIFT_BYTE      8
#define STACK_SIZE          0xFF

/* Function pointer type for addressing modes */
typedef void (*addressing_mode_t)(cpu_t *cpu, instruction_t *instruction);

/* Simple addressing modes (no operand or register-based) */
void addressing_implied(cpu_t *cpu, instruction_t *instruction);
void addressing_accumulator(cpu_t *cpu, instruction_t *instruction);
void addressing_immediate(cpu_t *cpu, instruction_t *instruction);

/* Basic memory addressing modes */
void addressing_relative(cpu_t *cpu, instruction_t *instruction);
void addressing_absolute(cpu_t *cpu, instruction_t *instruction);
void addressing_zero_page(cpu_t *cpu, instruction_t *instruction);
void addressing_indirect(cpu_t *cpu, instruction_t *instruction);

/* Indexed addressing modes */
void addressing_absolute_x(cpu_t *cpu, instruction_t *instruction);
void addressing_absolute_y(cpu_t *cpu, instruction_t *instruction);
void addressing_zero_page_x(cpu_t *cpu, instruction_t *instruction);
void addressing_zero_page_y(cpu_t *cpu, instruction_t *instruction);

/* Indexed indirect addressing modes */
void addressing_indirect_x(cpu_t *cpu, instruction_t *instruction);
void addressing_indirect_y(cpu_t *cpu, instruction_t *instruction);

#endif