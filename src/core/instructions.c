#include "instructions.h"

void adc(cpu_t *cpu, instruction_t *instruction) {
    uint8_t a = cpu->accumulator;
    uint16_t aux = (uint16_t)cpu->accumulator + (uint16_t)(*instruction->operand) + (uint16_t)status_get_flag(&cpu->status_register, FLAG_CARRY);
    cpu->accumulator = aux;

    status_set_carry_flag(&cpu->status_register,aux);
    status_set_zero_flag(&cpu->status_register, cpu->accumulator);
    status_set_negative_flag(&cpu->status_register, cpu->accumulator);
    status_set_overflow_flag(&cpu->status_register, a, *instruction->operand, cpu->accumulator);
}

void and(cpu_t *cpu, instruction_t *instruction) {
    cpu->accumulator &= *instruction->operand;

    status_set_zero_flag(&cpu->status_register, cpu->accumulator);
    status_set_negative_flag(&cpu->status_register, cpu->accumulator);
}

void asl(cpu_t *cpu, instruction_t *instruction) {
    uint16_t aux = *instruction->operand << 1;
    *instruction->operand = aux;

    status_set_zero_flag(&cpu->status_register, *instruction->operand);
    status_set_negative_flag(&cpu->status_register, *instruction->operand);
    status_set_carry_flag(&cpu->status_register, aux);
}

void bcc(cpu_t *cpu, instruction_t *instruction) {
    if(!status_get_flag(&cpu->status_register, FLAG_CARRY))
        cpu->program_counter += *((int8_t *)instruction->operand);
}

void bcs(cpu_t *cpu, instruction_t *instruction) {
    if(status_get_flag(&cpu->status_register, FLAG_CARRY))
        cpu->program_counter += *((int8_t *)instruction->operand);
}

void beq(cpu_t *cpu, instruction_t *instruction) {
    if(status_get_flag(&cpu->status_register, FLAG_ZERO))
        cpu->program_counter += *((int8_t *)instruction->operand);
}

void bit(cpu_t *cpu, instruction_t *instruction) {
    status_set_negative_flag(&cpu->status_register, *instruction->operand);
    status_set_zero_flag(&cpu->status_register, cpu->accumulator & (*instruction->operand));
    status_set_flag(&cpu->status_register, FLAG_OVERFLOW, (*instruction->operand) & 0x40);
}

void bmi(cpu_t *cpu, instruction_t *instruction) {
    if(status_get_flag(&cpu->status_register, FLAG_NEGATIVE))
        cpu->program_counter += *((int8_t *)instruction->operand);
}

void bne(cpu_t *cpu, instruction_t *instruction) {
    if(!status_get_flag(&cpu->status_register, FLAG_ZERO))
        cpu->program_counter += *((int8_t *)instruction->operand);
}

void bpl(cpu_t *cpu, instruction_t *instruction) {
    if(!status_get_flag(&cpu->status_register, FLAG_NEGATIVE))
        cpu->program_counter += *((int8_t *)instruction->operand);
}

void brk(cpu_t *cpu, instruction_t *instruction) {
    cpu->program_counter++;
    cpu->memory[0x100 | cpu->stack_pointer] = cpu->program_counter >> 8;
    cpu->stack_pointer--;
    cpu->memory[0x100 | cpu->stack_pointer] = cpu->program_counter;
    cpu->stack_pointer--;
    cpu->memory[0x100 | cpu->stack_pointer] = cpu->status_register | (1 << 4) | (1 << 5);
    cpu->stack_pointer--;

    status_set_flag(&cpu->status_register, FLAG_INTERRUPT_DISABLE, 1);

    cpu->program_counter = cpu->memory[0xFFFF] << 8;
    cpu->program_counter |= cpu->memory[0xFFFE];
}

void bvc(cpu_t *cpu, instruction_t *instruction) {
    if(!status_get_flag(&cpu->status_register , FLAG_OVERFLOW))
        cpu->program_counter += *((int8_t *)instruction->operand);
}

void bvs(cpu_t *cpu, instruction_t *instruction) {
    if(status_get_flag(&cpu->status_register, FLAG_OVERFLOW))
        cpu->program_counter += *((int8_t *)instruction->operand);
}

void clear(cpu_t *cpu, status_flag_t flag) {
    status_set_flag(&cpu->status_register, flag, 0);
}

void clc(cpu_t *cpu, instruction_t *instruction) {
    clear(cpu, FLAG_CARRY);
}

void cld(cpu_t *cpu, instruction_t *instruction) {
    clear(cpu, FLAG_DECIMAL);
}

void cli(cpu_t *cpu, instruction_t *instruction) {
    clear(cpu, FLAG_INTERRUPT_DISABLE);
}

void clv(cpu_t *cpu, instruction_t *instruction) {
     clear(cpu, FLAG_OVERFLOW);
}

void compare(cpu_t *cpu, instruction_t *instruction, uint8_t *registro) {
    status_set_flag(&cpu->status_register, FLAG_ZERO, *registro == (*instruction->operand));
    status_set_flag(&cpu->status_register, FLAG_CARRY, *registro >= (*instruction->operand));
    status_set_flag(&cpu->status_register, FLAG_NEGATIVE, *registro < (*instruction->operand));
}

void cmp(cpu_t *cpu, instruction_t *instruction) {
    compare(cpu, instruction, &(cpu->accumulator));
}

void cpx(cpu_t *cpu, instruction_t *instruction) {
    compare(cpu, instruction, &(cpu->x_index_register));
}

void cpy(cpu_t *cpu, instruction_t *instruction) {
    compare(cpu, instruction, &(cpu->y_index_register));
}

void decrement(cpu_t *cpu, uint8_t *registro) {
    *registro -= 1;

    status_set_zero_flag(&cpu->status_register, *registro);
    status_set_negative_flag(&cpu->status_register, *registro);
 }

void dec(cpu_t *cpu, instruction_t *instruction) {
    decrement(cpu, instruction->operand);
}

void dex(cpu_t *cpu, instruction_t *instruction) {
    decrement(cpu, &(cpu->x_index_register));
}

void dey(cpu_t *cpu, instruction_t *instruction) {
    decrement(cpu, &(cpu->y_index_register));
}

void eor(cpu_t *cpu, instruction_t *instruction) {
    cpu->accumulator ^= *instruction->operand;

    status_set_zero_flag(&cpu->status_register, cpu->accumulator);
    status_set_negative_flag(&cpu->status_register, cpu->accumulator);
}

void increment(cpu_t *cpu, uint8_t *registro) {
    *registro += 1;

    status_set_zero_flag(&cpu->status_register, *registro);
    status_set_negative_flag(&cpu->status_register, *registro);
}

void inc(cpu_t *cpu, instruction_t *instruction) {
    increment(cpu, instruction->operand);
}

void inx(cpu_t *cpu, instruction_t *instruction) {
    increment(cpu, &(cpu->x_index_register));
}

void iny(cpu_t *cpu, instruction_t *instruction) {
    increment(cpu, &(cpu->y_index_register));
}

void jmp(cpu_t *cpu, instruction_t *instruction) {
    cpu->program_counter = instruction->operand_address;
}

void jsr(cpu_t *cpu,instruction_t *instruction) {
    cpu->program_counter--;
    cpu->memory[0x100 | cpu->stack_pointer] = cpu->program_counter >> 8;
    cpu->stack_pointer--;
    cpu->memory[0x100 | cpu->stack_pointer] = cpu->program_counter;
    cpu->stack_pointer--;
    cpu->program_counter = instruction->operand_address;
}

void load(cpu_t *cpu, instruction_t *instruction, uint8_t *registro) {
    *registro = *instruction->operand;

    status_set_zero_flag(&cpu->status_register, *instruction->operand);
    status_set_negative_flag(&cpu->status_register, *instruction->operand);
}

void lda(cpu_t *cpu, instruction_t *instruction) {
    load(cpu, instruction, &(cpu->accumulator));
}

void ldx(cpu_t *cpu, instruction_t *instruction) {
    load(cpu, instruction, &(cpu->x_index_register));
}

void ldy(cpu_t *cpu, instruction_t *instruction) {
    load(cpu, instruction, &(cpu->y_index_register));
}

void lsr(cpu_t *cpu,instruction_t *instruction) {
    uint8_t bit_caido = (*instruction->operand & 0x01);
    *instruction->operand >>= 1;

    status_set_zero_flag(&cpu->status_register, *instruction->operand);
    status_set_negative_flag(&cpu->status_register, *instruction->operand);
    status_set_flag(&cpu->status_register, FLAG_CARRY, bit_caido);
}

void nop(cpu_t *cpu, instruction_t *instruction) {}

void ora(cpu_t *cpu, instruction_t *instruction) {
    cpu->accumulator |= *instruction->operand;

    status_set_zero_flag(&cpu->status_register, cpu->accumulator);
    status_set_negative_flag(&cpu->status_register, cpu->accumulator);
}

void pha(cpu_t *cpu, instruction_t *instruction) {
    cpu->memory[0x0100 | cpu->stack_pointer] = cpu->accumulator;
    cpu->stack_pointer--;
}

void php(cpu_t *cpu, instruction_t *instruction) {
   	cpu->memory[0x100 | cpu->stack_pointer] = cpu->status_register | (1 << 4) | (1 << 5);
    cpu->stack_pointer--;
}

void pla(cpu_t *cpu, instruction_t *instruction) {
    cpu->stack_pointer++;
    cpu->accumulator = cpu->memory[0x0100 | cpu->stack_pointer];

    status_set_zero_flag(&cpu->status_register, cpu->accumulator);
    status_set_negative_flag(&cpu->status_register, cpu->accumulator);
}

void plp(cpu_t *cpu, instruction_t *instruction) {
    cpu->stack_pointer++;
    cpu->status_register = cpu->memory[0x100 | cpu->stack_pointer] & 0xCF;
}

void rol(cpu_t *cpu, instruction_t *instruction) {
    status_rotate_left(&cpu->status_register, instruction->operand);

    status_set_zero_flag(&cpu->status_register, *instruction->operand);
    status_set_negative_flag(&cpu->status_register, *instruction->operand);
}

void ror(cpu_t *cpu, instruction_t *instruction) {
    status_rotate_right(&cpu->status_register, instruction->operand);

    status_set_zero_flag(&cpu->status_register, *instruction->operand);
    status_set_negative_flag(&cpu->status_register, *instruction->operand);
}

void rti(cpu_t *cpu, instruction_t *instruction) {
  	cpu->stack_pointer++;
    cpu->status_register = cpu->memory[0x100 | cpu->stack_pointer] & 0xCF;
    cpu->stack_pointer++;
    cpu->program_counter = cpu->memory[0x100 | cpu->stack_pointer];
    cpu->stack_pointer++;
    cpu->program_counter |= cpu->memory[0x100 | cpu->stack_pointer] << 8;
}

void rts(cpu_t *cpu, instruction_t *instruction) {
    cpu->stack_pointer++;
    cpu->program_counter = cpu->memory[0x100 | cpu->stack_pointer] ;
    cpu->stack_pointer++;
    cpu->program_counter |= cpu->memory[0x100 | cpu->stack_pointer] << 8;
    cpu->program_counter++;
}

void sbc(cpu_t *cpu, instruction_t *instruction) {
    uint8_t a = cpu->accumulator;
    uint16_t m = (uint16_t)(*instruction->operand) ^ 0x00FF;
    uint16_t aux = (uint16_t)cpu->accumulator + m + (uint16_t)status_get_flag(&cpu->status_register, FLAG_CARRY);
    cpu->accumulator = aux;

    status_set_zero_flag(&cpu->status_register, cpu->accumulator);
    status_set_carry_flag(&cpu->status_register, aux);
    status_set_negative_flag(&cpu->status_register, cpu->accumulator);
    status_set_overflow_flag(&cpu->status_register, a, m, cpu->accumulator);
}

void sec(cpu_t *cpu, instruction_t *instruction) {
    status_set_flag(&cpu->status_register, FLAG_CARRY, 1);
}

void sed(cpu_t *cpu,instruction_t *instruction) {
    status_set_flag(&cpu->status_register, FLAG_DECIMAL, 1);
}

void sei(cpu_t *cpu,instruction_t *instruction) {
    status_set_flag(&cpu->status_register, FLAG_INTERRUPT_DISABLE, 1);
}

void sta(cpu_t *cpu, instruction_t *instruction) {
    *instruction->operand = cpu->accumulator;
}

void stx(cpu_t *cpu, instruction_t *instruction) {
    *instruction->operand = cpu->x_index_register;
}

void sty(cpu_t *cpu, instruction_t *instruction) {
    *instruction->operand = cpu->y_index_register;
}

void transfer(cpu_t *cpu, uint8_t *registro) {
    *registro = cpu->accumulator;

    status_set_zero_flag(&cpu->status_register, *registro);
    status_set_negative_flag(&cpu->status_register, *registro);
}

void tax(cpu_t *cpu,instruction_t *instruction) {
    transfer(cpu, &(cpu->x_index_register));
}

void tay(cpu_t *cpu, instruction_t *instruction) {
    transfer(cpu, &(cpu->y_index_register));
}

void tsx(cpu_t *cpu,instruction_t *instruction) {
    cpu->x_index_register = cpu->stack_pointer;

    status_set_zero_flag(&cpu->status_register, cpu->x_index_register);
    status_set_negative_flag(&cpu->status_register, cpu->x_index_register);
}

void txa(cpu_t *cpu,instruction_t *instruction) {
    cpu->accumulator = cpu->x_index_register;

    status_set_zero_flag(&cpu->status_register, cpu->accumulator);
    status_set_negative_flag(&cpu->status_register, cpu->accumulator);
}

void txs(cpu_t *cpu,instruction_t *instruction) {
    cpu->stack_pointer = cpu->x_index_register;
}

void tya(cpu_t *cpu, instruction_t *instruction) {
    cpu->accumulator = cpu->y_index_register;

    status_set_zero_flag(&cpu->status_register, cpu->accumulator);
    status_set_negative_flag(&cpu->status_register, cpu->accumulator);
}
