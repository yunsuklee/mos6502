#include "test_framework.h"
#include "../src/core/cpu.h"
#include "../src/core/addressing.h"

cpu_t *setup_cpu_addressing() {
    cpu_t *cpu = cpu_create();
    cpu_reset(cpu, NULL, 0x8000);
    return cpu;
}

void test_addressing_immediate() {
    cpu_t *cpu = setup_cpu_addressing();
    instruction_t instruction = {0};
    
    cpu->memory[0x8000] = 0x42;
    cpu->program_counter = 0x8000;
    
    addressing_immediate(cpu, &instruction);
    
    ASSERT_EQ_HEX(0x42, *instruction.operand, "Immediate addressing should read operand from PC location");
    ASSERT_EQ_HEX(0x8001, cpu->program_counter, "PC should be incremented after immediate addressing");
    
    cpu_destroy(cpu);
}

void test_addressing_absolute() {
    cpu_t *cpu = setup_cpu_addressing();
    instruction_t instruction = {0};
    
    cpu->memory[0x8000] = 0x34;
    cpu->memory[0x8001] = 0x12;
    cpu->memory[0x1234] = 0x56;
    cpu->program_counter = 0x8000;
    
    addressing_absolute(cpu, &instruction);
    
    ASSERT_EQ_HEX(0x1234, instruction.operand_address, "Absolute addressing should form 16-bit address");
    ASSERT_EQ_HEX(0x56, *instruction.operand, "Should read from calculated address");
    
    cpu_destroy(cpu);
}

void test_addressing_zero_page() {
    cpu_t *cpu = setup_cpu_addressing();
    instruction_t instruction = {0};
    
    cpu->memory[0x8000] = 0x42;
    cpu->memory[0x0042] = 0x99;
    cpu->program_counter = 0x8000;
    
    addressing_zero_page(cpu, &instruction);
    
    ASSERT_EQ_HEX(0x0042, instruction.operand_address, "Zero page addressing should use zero page");
    ASSERT_EQ_HEX(0x99, *instruction.operand, "Should read from zero page address");
    
    cpu_destroy(cpu);
}

void test_addressing_absolute_x() {
    cpu_t *cpu = setup_cpu_addressing();
    instruction_t instruction = {0};
    
    cpu->memory[0x8000] = 0x00;
    cpu->memory[0x8001] = 0x20;
    cpu->memory[0x2005] = 0x77;
    cpu->program_counter = 0x8000;
    cpu->x_index_register = 0x05;
    
    addressing_absolute_x(cpu, &instruction);
    
    ASSERT_EQ_HEX(0x2005, instruction.operand_address, "Absolute,X should add X register to base address");
    ASSERT_EQ_HEX(0x77, *instruction.operand, "Should read from indexed address");
    
    cpu_destroy(cpu);
}

void test_addressing_zero_page_x() {
    cpu_t *cpu = setup_cpu_addressing();
    instruction_t instruction = {0};
    
    cpu->memory[0x8000] = 0x80;
    cpu->memory[0x0085] = 0x33;
    cpu->program_counter = 0x8000;
    cpu->x_index_register = 0x05;
    
    addressing_zero_page_x(cpu, &instruction);
    
    ASSERT_EQ_HEX(0x0085, instruction.operand_address, "Zero page,X should add X to zero page address");
    ASSERT_EQ_HEX(0x33, *instruction.operand, "Should read from indexed zero page address");
    
    cpu->program_counter = 0x8000;
    cpu->memory[0x8000] = 0xFF;
    cpu->memory[0x0004] = 0x44;
    cpu->x_index_register = 0x05;
    
    addressing_zero_page_x(cpu, &instruction);
    
    ASSERT_EQ_HEX(0x0004, instruction.operand_address, "Zero page,X should wrap around in zero page (0xFF + 0x05 = 0x04)");
    ASSERT_EQ_HEX(0x44, *instruction.operand, "Should read from wrapped address");
    
    cpu_destroy(cpu);
}