#include "test_framework.h"

int tests_run = 0;
int tests_failed = 0;
int current_test_failures = 0;

extern void test_cpu_create_destroy();
extern void test_cpu_reset();
extern void test_cpu_memory_access();

extern void test_status_get_set_flag();
extern void test_status_carry_flag();
extern void test_status_zero_flag();
extern void test_status_negative_flag();
extern void test_status_overflow_flag();

extern void test_lda_instruction();
extern void test_sta_instruction();
extern void test_adc_instruction();
extern void test_sbc_instruction();

extern void test_addressing_immediate();
extern void test_addressing_absolute();
extern void test_addressing_zero_page();
extern void test_addressing_absolute_x();
extern void test_addressing_zero_page_x();

extern int test_io();

int main() {
    printf("=== MOS6502 Emulator Test Suite ===\n\n");
    
    printf("--- CPU Core Tests ---\n");
    RUN_TEST(test_cpu_create_destroy);
    RUN_TEST(test_cpu_reset);
    RUN_TEST(test_cpu_memory_access);
    
    printf("\n--- Status Flag Tests ---\n");
    RUN_TEST(test_status_get_set_flag);
    RUN_TEST(test_status_carry_flag);
    RUN_TEST(test_status_zero_flag);
    RUN_TEST(test_status_negative_flag);
    RUN_TEST(test_status_overflow_flag);
    
    printf("\n--- Instruction Tests ---\n");
    RUN_TEST(test_lda_instruction);
    RUN_TEST(test_sta_instruction);
    RUN_TEST(test_adc_instruction);
    RUN_TEST(test_sbc_instruction);
    
    printf("\n--- Addressing Mode Tests ---\n");
    RUN_TEST(test_addressing_immediate);
    RUN_TEST(test_addressing_absolute);
    RUN_TEST(test_addressing_zero_page);
    RUN_TEST(test_addressing_absolute_x);
    RUN_TEST(test_addressing_zero_page_x);
    
    printf("\n--- Memory-Mapped I/O Tests ---\n");
    test_io();
    
    TEST_SUMMARY();
    
    return tests_failed;
}