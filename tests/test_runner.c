#include "test_framework.h"

int tests_run = 0;
int tests_failed = 0;

extern int test_cpu_create_destroy();
extern int test_cpu_reset();
extern int test_cpu_memory_access();

extern int test_status_get_set_flag();
extern int test_status_carry_flag();
extern int test_status_zero_flag();
extern int test_status_negative_flag();
extern int test_status_overflow_flag();

extern int test_lda_instruction();
extern int test_sta_instruction();
extern int test_adc_instruction();
extern int test_sbc_instruction();

extern int test_addressing_immediate();
extern int test_addressing_absolute();
extern int test_addressing_zero_page();
extern int test_addressing_absolute_x();
extern int test_addressing_zero_page_x();

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
    
    TEST_SUMMARY();
    
    return tests_failed;
}