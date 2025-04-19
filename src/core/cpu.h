#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define CPU_MEMORY_SIZE 65536 // 64K (2^16 bytes)
#define CPU_STATUS_CLEAR 0x00
#define CPU_STACK_INIT 0xFF
#define CPU_RESET_VECTOR_LOW 0xFFFC
#define CPU_RESET_VECTOR_HIGH 0xFFFD

typedef struct {
    uint8_t accumulator;
    uint8_t x_index_register;
    uint8_t y_index_register;
    uint16_t program_counter;
    uint8_t status_register;
    uint8_t stack_pointer;

    uint8_t *memory;
    long total_execution_cycles;
} cpu_t;

typedef struct {
    uint8_t opcode;
    uint8_t *operand;
    uint16_t operand_address;
    short required_execution_cycles;
} instruction_t;

cpu_t *cpu_create(void);
void cpu_destroy(cpu_t *cpu);
void cpu_reset(cpu_t *cpu, uint8_t *memory, uint16_t program_counter);

void cpu_execute_instruction(cpu_t *cpu);
bool cpu_load_rom(cpu_t *cpu, const char *rom_path);
bool cpu_log_state(cpu_t *cpu, const char *log_file_path);

#endif