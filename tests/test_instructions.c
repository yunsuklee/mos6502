#include "test_framework.h"
#include "../src/core/cpu.h"
#include "../src/core/instructions.h"
#include "../src/core/status.h"

cpu_t *setup_cpu() {
    cpu_t *cpu = cpu_create();
    cpu_reset(cpu, NULL, 0x8000);
    return cpu;
}

int test_lda_instruction() {
    cpu_t *cpu = setup_cpu();
    instruction_t instruction;
    uint8_t value = 0x42;
    
    instruction.operand = &value;
    instruction.operand_address = 0x1000;
    
    cpu->accumulator = 0x00;
    lda(cpu, &instruction);
    
    ASSERT_EQ_HEX(0x42, cpu->accumulator, "LDA should load value into accumulator");
    ASSERT(!status_get_flag(&cpu->status_register, FLAG_ZERO), "Zero flag should be clear for non-zero value");
    ASSERT(!status_get_flag(&cpu->status_register, FLAG_NEGATIVE), "Negative flag should be clear for positive value");
    
    value = 0x00;
    lda(cpu, &instruction);
    ASSERT_EQ_HEX(0x00, cpu->accumulator, "LDA should load zero");
    ASSERT(status_get_flag(&cpu->status_register, FLAG_ZERO), "Zero flag should be set for zero value");
    
    value = 0x80;
    lda(cpu, &instruction);
    ASSERT_EQ_HEX(0x80, cpu->accumulator, "LDA should load negative value");
    ASSERT(status_get_flag(&cpu->status_register, FLAG_NEGATIVE), "Negative flag should be set for value with bit 7 set");
    
    cpu_destroy(cpu);
    return 0;
}

int test_sta_instruction() {
    cpu_t *cpu = setup_cpu();
    instruction_t instruction;
    
    instruction.operand_address = 0x1000;
    instruction.operand = &cpu->memory[0x1000];
    cpu->accumulator = 0x55;
    
    sta(cpu, &instruction);
    
    ASSERT_EQ_HEX(0x55, cpu->memory[0x1000], "STA should store accumulator value in memory");
    
    cpu->accumulator = 0xAA;
    instruction.operand_address = 0x2000;
    instruction.operand = &cpu->memory[0x2000];
    sta(cpu, &instruction);
    
    ASSERT_EQ_HEX(0xAA, cpu->memory[0x2000], "STA should store new accumulator value");
    ASSERT_EQ_HEX(0x55, cpu->memory[0x1000], "Previous memory location should be unchanged");
    
    cpu_destroy(cpu);
    return 0;
}

int test_adc_instruction() {
    cpu_t *cpu = setup_cpu();
    instruction_t instruction;
    uint8_t value;
    
    cpu->accumulator = 0x10;
    value = 0x20;
    instruction.operand = &value;
    
    adc(cpu, &instruction);
    
    ASSERT_EQ_HEX(0x30, cpu->accumulator, "ADC should add operand to accumulator");
    ASSERT(!status_get_flag(&cpu->status_register, FLAG_CARRY), "No carry for simple addition");
    ASSERT(!status_get_flag(&cpu->status_register, FLAG_ZERO), "Zero flag should be clear");
    ASSERT(!status_get_flag(&cpu->status_register, FLAG_OVERFLOW), "No overflow for simple addition");
    
    cpu->accumulator = 0xFF;
    value = 0x01;
    adc(cpu, &instruction);
    
    ASSERT_EQ_HEX(0x00, cpu->accumulator, "ADC should wrap around on overflow");
    ASSERT(status_get_flag(&cpu->status_register, FLAG_CARRY), "Carry should be set on overflow");
    ASSERT(status_get_flag(&cpu->status_register, FLAG_ZERO), "Zero flag should be set for result 0");
    
    cpu->status_register = 0x00;
    status_set_flag(&cpu->status_register, FLAG_CARRY, true);
    cpu->accumulator = 0x10;
    value = 0x20;
    adc(cpu, &instruction);
    
    ASSERT_EQ_HEX(0x31, cpu->accumulator, "ADC should add carry flag to result");
    
    cpu_destroy(cpu);
    return 0;
}

int test_sbc_instruction() {
    cpu_t *cpu = setup_cpu();
    instruction_t instruction;
    uint8_t value;
    
    status_set_flag(&cpu->status_register, FLAG_CARRY, true);
    cpu->accumulator = 0x30;
    value = 0x10;
    instruction.operand = &value;
    
    sbc(cpu, &instruction);
    
    ASSERT_EQ_HEX(0x20, cpu->accumulator, "SBC should subtract operand from accumulator");
    ASSERT(status_get_flag(&cpu->status_register, FLAG_CARRY), "Carry should remain set for no borrow");
    ASSERT(!status_get_flag(&cpu->status_register, FLAG_ZERO), "Zero flag should be clear");
    
    cpu->status_register = 0x00;
    status_set_flag(&cpu->status_register, FLAG_CARRY, true);
    cpu->accumulator = 0x10;
    value = 0x20;
    sbc(cpu, &instruction);
    
    ASSERT_EQ_HEX(0xF0, cpu->accumulator, "SBC should handle underflow correctly");
    ASSERT(!status_get_flag(&cpu->status_register, FLAG_CARRY), "Carry should be clear on borrow");
    ASSERT(status_get_flag(&cpu->status_register, FLAG_NEGATIVE), "Negative flag should be set");
    
    cpu_destroy(cpu);
    return 0;
}