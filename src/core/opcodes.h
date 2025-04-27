#ifndef OPCODES_H
#define OPCODES_H

#include <stdint.h>

#include "cpu.h"
#include "instructions.h"
#include "addressing.h"

/* Function pointer type for instruction operations */
typedef void (*instruction_operation_t)(cpu_t *cpu, instruction_t *instruction);

typedef struct {
    addressing_mode_t addressing_mode;
    instruction_operation_t operation;
    uint8_t cycles;
    bool extra_cycle_for_page_cross;
} opcode_t;

extern opcode_t opcodes_dictionary[];

#endif