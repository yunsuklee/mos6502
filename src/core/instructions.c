#include "instructions.h"

void load_register(cpu_t *cpu, instruction_t *instruction, uint8_t *target_register)
{
    *target_register = *instruction->operand;

    status_set_zero_flag(&cpu->status_register, *target_register);
    status_set_negative_flag(&cpu->status_register, *target_register);
}

void store_register(cpu_t *cpu, instruction_t *instruction, uint8_t source_register)
{
    *instruction->operand = source_register;
}

void compare_register(cpu_t *cpu, instruction_t *instruction, uint8_t register_value)
{
    uint8_t operand = *instruction->operand;

    status_set_flag(&cpu->status_register, FLAG_ZERO, register_value == operand);
    status_set_flag(&cpu->status_register, FLAG_CARRY, register_value >= operand);
    status_set_flag(&cpu->status_register, FLAG_NEGATIVE, (register_value - operand) & 0x80);
}

void increment_value(cpu_t *cpu, uint8_t *target)
{
    (*target)++;

    status_set_zero_flag(&cpu->status_register, *target);
    status_set_negative_flag(&cpu->status_register, *target);
}

void decrement_value(cpu_t *cpu, uint8_t *target)
{
    (*target)--;

    status_set_zero_flag(&cpu->status_register, *target);
    status_set_negative_flag(&cpu->status_register, *target);
}

void transfer_register(cpu_t *cpu, uint8_t source_value, uint8_t *target_register)
{
    *target_register = source_value;

    status_set_zero_flag(&cpu->status_register, *target_register);
    status_set_negative_flag(&cpu->status_register, *target_register);
}

void clear_flag(cpu_t *cpu, status_flag_t flag)
{
    status_set_flag(&cpu->status_register, flag, false);
}

void set_flag(cpu_t *cpu, status_flag_t flag)
{
    status_set_flag(&cpu->status_register, flag, true);
}

void branch_if(cpu_t *cpu, instruction_t *instruction, bool condition)
{
    if (condition)
    {
        cpu->program_counter += *((int8_t *)instruction->operand);
    }
}

/* =============================================================================
 * ARITHMETIC OPERATIONS
 * =============================================================================*/

void adc(cpu_t *cpu, instruction_t *instruction)
{
    uint8_t accumulator = cpu->accumulator;
    uint8_t operand = *instruction->operand;
    uint8_t carry = status_get_flag(&cpu->status_register, FLAG_CARRY) ? 1 : 0;

    uint16_t result = (uint16_t)accumulator + (uint16_t)operand + (uint16_t)carry;
    cpu->accumulator = (uint8_t)result;

    status_set_carry_flag(&cpu->status_register, result);
    status_set_zero_flag(&cpu->status_register, cpu->accumulator);
    status_set_negative_flag(&cpu->status_register, cpu->accumulator);
    status_set_overflow_flag(&cpu->status_register, accumulator, operand, cpu->accumulator);
}

void sbc(cpu_t *cpu, instruction_t *instruction)
{
    uint8_t accumulator = cpu->accumulator;
    uint8_t operand = *instruction->operand;
    uint8_t carry = status_get_flag(&cpu->status_register, FLAG_CARRY) ? 1 : 0;

    // SBC is equivalent to ADC with inverted operand
    uint16_t inverted_operand = operand ^ 0xFF;
    uint16_t result = (uint16_t)accumulator + inverted_operand + (uint16_t)carry;
    cpu->accumulator = (uint8_t)result;

    status_set_carry_flag(&cpu->status_register, result);
    status_set_zero_flag(&cpu->status_register, cpu->accumulator);
    status_set_negative_flag(&cpu->status_register, cpu->accumulator);
    status_set_overflow_flag(&cpu->status_register, accumulator, (uint8_t)inverted_operand, cpu->accumulator);
}

/* =============================================================================
 * LOGICAL OPERATIONS
 * =============================================================================*/

void and(cpu_t *cpu, instruction_t *instruction)
{
    cpu->accumulator &= *instruction->operand;

    status_set_zero_flag(&cpu->status_register, cpu->accumulator);
    status_set_negative_flag(&cpu->status_register, cpu->accumulator);
}

void ora(cpu_t *cpu, instruction_t *instruction)
{
    cpu->accumulator |= *instruction->operand;

    status_set_zero_flag(&cpu->status_register, cpu->accumulator);
    status_set_negative_flag(&cpu->status_register, cpu->accumulator);
}

void eor(cpu_t *cpu, instruction_t *instruction)
{
    cpu->accumulator ^= *instruction->operand;

    status_set_zero_flag(&cpu->status_register, cpu->accumulator);
    status_set_negative_flag(&cpu->status_register, cpu->accumulator);
}

/* =============================================================================
 * SHIFT AND ROTATE OPERATIONS
 * =============================================================================*/

void asl(cpu_t *cpu, instruction_t *instruction)
{
    uint16_t result = (*instruction->operand) << 1;
    *instruction->operand = (uint8_t)result;

    status_set_carry_flag(&cpu->status_register, result);
    status_set_zero_flag(&cpu->status_register, *instruction->operand);
    status_set_negative_flag(&cpu->status_register, *instruction->operand);
}

void lsr(cpu_t *cpu, instruction_t *instruction)
{
    uint8_t value = *instruction->operand;
    bool carry_out = (value & 0x01) != 0;

    *instruction->operand = value >> 1;

    status_set_flag(&cpu->status_register, FLAG_CARRY, carry_out);
    status_set_zero_flag(&cpu->status_register, *instruction->operand);
    status_set_negative_flag(&cpu->status_register, *instruction->operand);
}

void rol(cpu_t *cpu, instruction_t *instruction)
{
    status_rotate_left(&cpu->status_register, instruction->operand);

    status_set_zero_flag(&cpu->status_register, *instruction->operand);
    status_set_negative_flag(&cpu->status_register, *instruction->operand);
}

void ror(cpu_t *cpu, instruction_t *instruction)
{
    status_rotate_right(&cpu->status_register, instruction->operand);

    status_set_zero_flag(&cpu->status_register, *instruction->operand);
    status_set_negative_flag(&cpu->status_register, *instruction->operand);
}

/* =============================================================================
 * COMPARISON OPERATIONS
 * =============================================================================*/

void cmp(cpu_t *cpu, instruction_t *instruction)
{
    compare_register(cpu, instruction, cpu->accumulator);
}

void cpx(cpu_t *cpu, instruction_t *instruction)
{
    compare_register(cpu, instruction, cpu->x_index_register);
}

void cpy(cpu_t *cpu, instruction_t *instruction)
{
    compare_register(cpu, instruction, cpu->y_index_register);
}

void bit(cpu_t *cpu, instruction_t *instruction)
{
    uint8_t operand = *instruction->operand;
    uint8_t result = cpu->accumulator & operand;

    status_set_zero_flag(&cpu->status_register, result);
    status_set_flag(&cpu->status_register, FLAG_NEGATIVE, (operand & 0x80) != 0);
    status_set_flag(&cpu->status_register, FLAG_OVERFLOW, (operand & 0x40) != 0);
}

/* =============================================================================
 * BRANCH OPERATIONS
 * =============================================================================*/

void bcc(cpu_t *cpu, instruction_t *instruction)
{
    branch_if(cpu, instruction, !status_get_flag(&cpu->status_register, FLAG_CARRY));
}

void bcs(cpu_t *cpu, instruction_t *instruction)
{
    branch_if(cpu, instruction, status_get_flag(&cpu->status_register, FLAG_CARRY));
}

void beq(cpu_t *cpu, instruction_t *instruction)
{
    branch_if(cpu, instruction, status_get_flag(&cpu->status_register, FLAG_ZERO));
}

void bne(cpu_t *cpu, instruction_t *instruction)
{
    branch_if(cpu, instruction, !status_get_flag(&cpu->status_register, FLAG_ZERO));
}

void bmi(cpu_t *cpu, instruction_t *instruction)
{
    branch_if(cpu, instruction, status_get_flag(&cpu->status_register, FLAG_NEGATIVE));
}

void bpl(cpu_t *cpu, instruction_t *instruction)
{
    branch_if(cpu, instruction, !status_get_flag(&cpu->status_register, FLAG_NEGATIVE));
}

void bvc(cpu_t *cpu, instruction_t *instruction)
{
    branch_if(cpu, instruction, !status_get_flag(&cpu->status_register, FLAG_OVERFLOW));
}

void bvs(cpu_t *cpu, instruction_t *instruction)
{
    branch_if(cpu, instruction, status_get_flag(&cpu->status_register, FLAG_OVERFLOW));
}

/* =============================================================================
 * JUMP AND SUBROUTINE OPERATIONS
 * =============================================================================*/

void jmp(cpu_t *cpu, instruction_t *instruction)
{
    cpu->program_counter = instruction->operand_address;
}

void jsr(cpu_t *cpu, instruction_t *instruction)
{
    // Decrement PC since we want to return to the instruction after JSR
    cpu->program_counter--;

    // Push return address onto stack (high byte first)
    cpu->memory[0x0100 | cpu->stack_pointer] = (cpu->program_counter >> 8) & 0xFF;
    cpu->stack_pointer--;
    cpu->memory[0x0100 | cpu->stack_pointer] = cpu->program_counter & 0xFF;
    cpu->stack_pointer--;

    // Jump to subroutine
    cpu->program_counter = instruction->operand_address;
}

void rts(cpu_t *cpu, instruction_t *instruction)
{
    // Pull return address from stack (low byte first)
    cpu->stack_pointer++;
    cpu->program_counter = cpu->memory[0x0100 | cpu->stack_pointer];
    cpu->stack_pointer++;
    cpu->program_counter |= (cpu->memory[0x0100 | cpu->stack_pointer] << 8);

    // Increment PC to return to instruction after JSR
    cpu->program_counter++;
}

void rti(cpu_t *cpu, instruction_t *instruction)
{
    // Pull status register from stack (clear B and U flags)
    cpu->stack_pointer++;
    cpu->status_register = (cpu->memory[0x0100 | cpu->stack_pointer] & 0xCF) | 0x20;

    // Pull return address from stack
    cpu->stack_pointer++;
    cpu->program_counter = cpu->memory[0x0100 | cpu->stack_pointer];
    cpu->stack_pointer++;
    cpu->program_counter |= (cpu->memory[0x0100 | cpu->stack_pointer] << 8);
}

void brk(cpu_t *cpu, instruction_t *instruction)
{
    // Increment PC to point to next instruction
    cpu->program_counter++;

    // Push return address onto stack (high byte first)
    cpu->memory[0x0100 | cpu->stack_pointer] = (cpu->program_counter >> 8) & 0xFF;
    cpu->stack_pointer--;
    cpu->memory[0x0100 | cpu->stack_pointer] = cpu->program_counter & 0xFF;
    cpu->stack_pointer--;

    // Push status register with B and U flags set
    cpu->memory[0x0100 | cpu->stack_pointer] = cpu->status_register | FLAG_BREAK | FLAG_UNUSED;
    cpu->stack_pointer--;

    // Set interrupt disable flag
    status_set_flag(&cpu->status_register, FLAG_INTERRUPT_DISABLE, true);

    // Jump to interrupt vector
    cpu->program_counter = cpu->memory[0xFFFE] | (cpu->memory[0xFFFF] << 8);
}

/* =============================================================================
 * LOAD AND STORE OPERATIONS
 * =============================================================================*/

void lda(cpu_t *cpu, instruction_t *instruction)
{
    load_register(cpu, instruction, &cpu->accumulator);
}

void ldx(cpu_t *cpu, instruction_t *instruction)
{
    load_register(cpu, instruction, &cpu->x_index_register);
}

void ldy(cpu_t *cpu, instruction_t *instruction)
{
    load_register(cpu, instruction, &cpu->y_index_register);
}

void sta(cpu_t *cpu, instruction_t *instruction)
{
    store_register(cpu, instruction, cpu->accumulator);
}

void stx(cpu_t *cpu, instruction_t *instruction)
{
    store_register(cpu, instruction, cpu->x_index_register);
}

void sty(cpu_t *cpu, instruction_t *instruction)
{
    store_register(cpu, instruction, cpu->y_index_register);
}

/* =============================================================================
 * INCREMENT AND DECREMENT OPERATIONS
 * =============================================================================*/

void inc(cpu_t *cpu, instruction_t *instruction)
{
    increment_value(cpu, instruction->operand);
}

void dec(cpu_t *cpu, instruction_t *instruction)
{
    decrement_value(cpu, instruction->operand);
}

void inx(cpu_t *cpu, instruction_t *instruction)
{
    increment_value(cpu, &cpu->x_index_register);
}

void dex(cpu_t *cpu, instruction_t *instruction)
{
    decrement_value(cpu, &cpu->x_index_register);
}

void iny(cpu_t *cpu, instruction_t *instruction)
{
    increment_value(cpu, &cpu->y_index_register);
}

void dey(cpu_t *cpu, instruction_t *instruction)
{
    decrement_value(cpu, &cpu->y_index_register);
}

/* =============================================================================
 * REGISTER TRANSFER OPERATIONS
 * =============================================================================*/

void tax(cpu_t *cpu, instruction_t *instruction)
{
    transfer_register(cpu, cpu->accumulator, &cpu->x_index_register);
}

void tay(cpu_t *cpu, instruction_t *instruction)
{
    transfer_register(cpu, cpu->accumulator, &cpu->y_index_register);
}

void txa(cpu_t *cpu, instruction_t *instruction)
{
    transfer_register(cpu, cpu->x_index_register, &cpu->accumulator);
}

void tya(cpu_t *cpu, instruction_t *instruction)
{
    transfer_register(cpu, cpu->y_index_register, &cpu->accumulator);
}

void tsx(cpu_t *cpu, instruction_t *instruction)
{
    transfer_register(cpu, cpu->stack_pointer, &cpu->x_index_register);
}

void txs(cpu_t *cpu, instruction_t *instruction)
{
    // TXS doesn't affect flags
    cpu->stack_pointer = cpu->x_index_register;
}

/* =============================================================================
 * STACK OPERATIONS
 * =============================================================================*/

void pha(cpu_t *cpu, instruction_t *instruction)
{
    cpu->memory[0x0100 | cpu->stack_pointer] = cpu->accumulator;
    cpu->stack_pointer--;
}

void pla(cpu_t *cpu, instruction_t *instruction)
{
    cpu->stack_pointer++;
    cpu->accumulator = cpu->memory[0x0100 | cpu->stack_pointer];

    status_set_zero_flag(&cpu->status_register, cpu->accumulator);
    status_set_negative_flag(&cpu->status_register, cpu->accumulator);
}

void php(cpu_t *cpu, instruction_t *instruction)
{
    // Push status register with B and U flags set
    cpu->memory[0x0100 | cpu->stack_pointer] = cpu->status_register | FLAG_BREAK | FLAG_UNUSED;
    cpu->stack_pointer--;
}

void plp(cpu_t *cpu, instruction_t *instruction)
{
    cpu->stack_pointer++;
    // Clear B and U flags, keep U flag always set
    cpu->status_register = (cpu->memory[0x0100 | cpu->stack_pointer] & 0xCF) | FLAG_UNUSED;
}

/* =============================================================================
 * STATUS FLAG OPERATIONS
 * =============================================================================*/

void clc(cpu_t *cpu, instruction_t *instruction)
{
    clear_flag(cpu, FLAG_CARRY);
}

void sec(cpu_t *cpu, instruction_t *instruction)
{
    set_flag(cpu, FLAG_CARRY);
}

void cli(cpu_t *cpu, instruction_t *instruction)
{
    clear_flag(cpu, FLAG_INTERRUPT_DISABLE);
}

void sei(cpu_t *cpu, instruction_t *instruction)
{
    set_flag(cpu, FLAG_INTERRUPT_DISABLE);
}

void clv(cpu_t *cpu, instruction_t *instruction)
{
    clear_flag(cpu, FLAG_OVERFLOW);
}

void cld(cpu_t *cpu, instruction_t *instruction)
{
    clear_flag(cpu, FLAG_DECIMAL);
}

void sed(cpu_t *cpu, instruction_t *instruction)
{
    set_flag(cpu, FLAG_DECIMAL);
}

void nop(cpu_t *cpu, instruction_t *instruction)
{
    // No operation - do nothing
}