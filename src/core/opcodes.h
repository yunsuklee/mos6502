#ifndef OPCODES_H
#define OPCODES_H

#include <stdint.h>

#include "cpu.h"
#include "instructions.h"
#include "addressing.h"

/**
 * Function pointer type for instruction operations
 * Points to functions that implement CPU instructions
 */
typedef void (*instruction_operation_t)(cpu_t *cpu, instruction_t *instruction);

/**
 * Function pointer type for addressing modes
 * Points to functions that implement different CPU addressing modes
 */
typedef void (*addressing_mode_t)(cpu_t *cpu, instruction_t *instruction);

typedef struct {
    addressing_mode_t addressing_mode;
    instruction_operation_t operation;
    uint8_t cycles;
} opcode_t;

extern opcode_t opcodes_dictionary[];

#endif
