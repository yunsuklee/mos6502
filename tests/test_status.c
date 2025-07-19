#include "test_framework.h"
#include "../src/core/status.h"

void test_status_get_set_flag() {
    uint8_t status = 0x00;
    
    ASSERT(!status_get_flag(&status, FLAG_CARRY), "Carry flag should be clear initially");
    ASSERT(!status_get_flag(&status, FLAG_ZERO), "Zero flag should be clear initially");
    ASSERT(!status_get_flag(&status, FLAG_NEGATIVE), "Negative flag should be clear initially");
    
    status_set_flag(&status, FLAG_CARRY, true);
    ASSERT(status_get_flag(&status, FLAG_CARRY), "Carry flag should be set");
    ASSERT_EQ_HEX(FLAG_CARRY, status, "Status register should have carry bit set");
    
    status_set_flag(&status, FLAG_ZERO, true);
    ASSERT(status_get_flag(&status, FLAG_ZERO), "Zero flag should be set");
    ASSERT_EQ_HEX(FLAG_CARRY | FLAG_ZERO, status, "Status should have both carry and zero set");
    
    status_set_flag(&status, FLAG_CARRY, false);
    ASSERT(!status_get_flag(&status, FLAG_CARRY), "Carry flag should be cleared");
    ASSERT(status_get_flag(&status, FLAG_ZERO), "Zero flag should still be set");
    ASSERT_EQ_HEX(FLAG_ZERO, status, "Status should only have zero flag set");
    
}

void test_status_carry_flag() {
    uint8_t status = 0x00;
    
    status_set_carry_flag(&status, 0x00FF);
    ASSERT(!status_get_flag(&status, FLAG_CARRY), "No carry for result < 256");
    
    status_set_carry_flag(&status, 0x0100);
    ASSERT(status_get_flag(&status, FLAG_CARRY), "Carry should be set for result >= 256");
    
    status_set_carry_flag(&status, 0x01FF);
    ASSERT(status_get_flag(&status, FLAG_CARRY), "Carry should be set for result > 256");
    
}

void test_status_zero_flag() {
    uint8_t status = 0x00;
    
    status_set_zero_flag(&status, 0x00);
    ASSERT(status_get_flag(&status, FLAG_ZERO), "Zero flag should be set for result 0");
    
    status_set_zero_flag(&status, 0x01);
    ASSERT(!status_get_flag(&status, FLAG_ZERO), "Zero flag should be clear for non-zero result");
    
    status_set_zero_flag(&status, 0xFF);
    ASSERT(!status_get_flag(&status, FLAG_ZERO), "Zero flag should be clear for 0xFF");
    
}

void test_status_negative_flag() {
    uint8_t status = 0x00;
    
    status_set_negative_flag(&status, 0x7F);
    ASSERT(!status_get_flag(&status, FLAG_NEGATIVE), "Negative flag should be clear for positive value");
    
    status_set_negative_flag(&status, 0x80);
    ASSERT(status_get_flag(&status, FLAG_NEGATIVE), "Negative flag should be set for 0x80");
    
    status_set_negative_flag(&status, 0xFF);
    ASSERT(status_get_flag(&status, FLAG_NEGATIVE), "Negative flag should be set for 0xFF");
    
}

void test_status_overflow_flag() {
    uint8_t status = 0x00;
    
    status_set_overflow_flag(&status, 0x50, 0x50, 0xA0);
    ASSERT(status_get_flag(&status, FLAG_OVERFLOW), "Overflow: positive + positive = negative");
    
    status = 0x00;
    status_set_overflow_flag(&status, 0x50, 0x10, 0x60);
    ASSERT(!status_get_flag(&status, FLAG_OVERFLOW), "No overflow: positive + positive = positive");
    
    status = 0x00;
    status_set_overflow_flag(&status, 0xD0, 0x90, 0x60);
    ASSERT(status_get_flag(&status, FLAG_OVERFLOW), "Overflow: negative + negative = positive");
    
    status = 0x00;
    status_set_overflow_flag(&status, 0xD0, 0xD0, 0xA0);
    ASSERT(!status_get_flag(&status, FLAG_OVERFLOW), "No overflow: negative + negative = negative");
    
}