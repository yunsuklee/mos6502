#include "test_framework.h"
#include "../src/core/cpu.h"
#include <stdio.h>
#include <string.h>


void test_character_output_port() {
    cpu_t *cpu = cpu_create();
    ASSERT(cpu != NULL, "CPU creation failed");
    
    // Test writing printable character to output port
    cpu_write_memory(cpu, CPU_CHAR_OUTPUT_PORT, 'H');
    
    // Test writing newline
    cpu_write_memory(cpu, CPU_CHAR_OUTPUT_PORT, 0x0A);
    
    // Test writing non-printable character (should be ignored)
    cpu_write_memory(cpu, CPU_CHAR_OUTPUT_PORT, 0x01);
    
    // Test writing to regular memory (should store normally)
    cpu_write_memory(cpu, 0x1000, 0x42);
    ASSERT_EQ(cpu->memory[0x1000], 0x42, "Regular memory write failed");
    
    cpu_destroy(cpu);
}

void test_halt_port() {
    cpu_t *cpu = cpu_create();
    ASSERT(cpu != NULL, "CPU creation failed");
    
    // Initially CPU should not be halted
    ASSERT_EQ(cpu->halted, false, "CPU should not be halted initially");
    
    // Write to halt port with exit code 0
    cpu_write_memory(cpu, CPU_HALT_PORT, 0);
    ASSERT_EQ(cpu->halted, true, "CPU should be halted after halt port write");
    
    cpu_destroy(cpu);
}

void test_halt_port_with_exit_code() {
    cpu_t *cpu = cpu_create();
    ASSERT(cpu != NULL, "CPU creation failed");
    
    // Write to halt port with exit code 42
    cpu_write_memory(cpu, CPU_HALT_PORT, 42);
    ASSERT_EQ(cpu->halted, true, "CPU should be halted with exit code");
    
    cpu_destroy(cpu);
}

void test_memory_mapped_io_boundaries() {
    cpu_t *cpu = cpu_create();
    ASSERT(cpu != NULL, "CPU creation failed");
    
    // Test addresses around I/O ports
    cpu_write_memory(cpu, CPU_CHAR_OUTPUT_PORT - 1, 0x55);
    ASSERT_EQ(cpu->memory[CPU_CHAR_OUTPUT_PORT - 1], 0x55, "Memory before char port should work normally");
    
    cpu_write_memory(cpu, CPU_HALT_PORT + 1, 0xAA);
    ASSERT_EQ(cpu->memory[CPU_HALT_PORT + 1], 0xAA, "Memory after halt port should work normally");
    
    // CPU should not be halted by non-halt port writes
    ASSERT_EQ(cpu->halted, false, "CPU should not be halted by regular memory writes");
    
    cpu_destroy(cpu);
}

void test_multiple_character_output() {
    cpu_t *cpu = cpu_create();
    ASSERT(cpu != NULL, "CPU creation failed");
    
    // Test writing multiple characters
    const char *test_string = "Hello";
    for (int i = 0; test_string[i] != '\0'; i++) {
        cpu_write_memory(cpu, CPU_CHAR_OUTPUT_PORT, test_string[i]);
    }
    
    // CPU should still be running
    ASSERT_EQ(cpu->halted, false, "CPU should not be halted by character output");
    
    cpu_destroy(cpu);
}

int test_io() {
    printf("Testing memory-mapped I/O...\n");
    
    RUN_TEST(test_character_output_port);
    RUN_TEST(test_halt_port);
    RUN_TEST(test_halt_port_with_exit_code);
    RUN_TEST(test_memory_mapped_io_boundaries);
    RUN_TEST(test_multiple_character_output);
    
    return current_test_failures;
}