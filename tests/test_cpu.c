#include "test_framework.h"
#include "../src/core/cpu.h"

void test_cpu_create_destroy() {
    cpu_t *cpu = cpu_create();
    ASSERT_CRITICAL(cpu != NULL, "CPU creation should succeed");
    ASSERT(cpu->memory != NULL, "CPU memory should be allocated");
    ASSERT_EQ(CPU_MEMORY_SIZE, 65536, "Memory size should be 64K");
    
    cpu_destroy(cpu);
}

void test_cpu_reset() {
    cpu_t *cpu = cpu_create();
    ASSERT_CRITICAL(cpu != NULL, "CPU creation should succeed");
    
    cpu->memory[CPU_RESET_VECTOR_LOW] = 0x00;
    cpu->memory[CPU_RESET_VECTOR_HIGH] = 0x80;
    
    cpu_reset(cpu, NULL, 0x8000);
    
    ASSERT_EQ_HEX(0x00, cpu->accumulator, "Accumulator should be reset to 0");
    ASSERT_EQ_HEX(0x00, cpu->x_index_register, "X register should be reset to 0");
    ASSERT_EQ_HEX(0x00, cpu->y_index_register, "Y register should be reset to 0");
    ASSERT_EQ_HEX(0x8000, cpu->program_counter, "Program counter should be set to reset vector");
    ASSERT_EQ_HEX(CPU_STATUS_CLEAR, cpu->status_register, "Status register should be cleared");
    ASSERT_EQ_HEX(CPU_STACK_INIT, cpu->stack_pointer, "Stack pointer should be initialized to 0xFF");
    ASSERT_EQ(0, cpu->total_execution_cycles, "Total cycles should be reset to 0");
    
    cpu_destroy(cpu);
}

void test_cpu_memory_access() {
    cpu_t *cpu = cpu_create();
    ASSERT_CRITICAL(cpu != NULL, "CPU creation should succeed");
    
    cpu->memory[0x1000] = 0x42;
    ASSERT_EQ_HEX(0x42, cpu->memory[0x1000], "Memory write/read should work");
    
    cpu->memory[0x0000] = 0xFF;
    cpu->memory[0xFFFF] = 0xAA;
    ASSERT_EQ_HEX(0xFF, cpu->memory[0x0000], "Memory access at start should work");
    ASSERT_EQ_HEX(0xAA, cpu->memory[0xFFFF], "Memory access at end should work");
    
    cpu_destroy(cpu);
}