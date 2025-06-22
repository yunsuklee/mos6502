#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>

#include "status.h"
#include "cpu.h"

/* Arithmetic operations */
void adc(cpu_t *cpu, instruction_t *instruction); // Add with carry
void sbc(cpu_t *cpu, instruction_t *instruction); // Subtract with carry

/* Logical operations */
void and(cpu_t *cpu, instruction_t *instruction); // Logical AND
void ora(cpu_t *cpu, instruction_t *instruction); // Logical OR
void eor(cpu_t *cpu, instruction_t *instruction); // Exclusive OR

/* Shift and rotate operations */
void asl(cpu_t *cpu, instruction_t *instruction); // Arithmetic shift left
void lsr(cpu_t *cpu, instruction_t *instruction); // Logical shift right
void rol(cpu_t *cpu, instruction_t *instruction); // Rotate left
void ror(cpu_t *cpu, instruction_t *instruction); // Rotate right

/* Comparison operations */
void cmp(cpu_t *cpu, instruction_t *instruction); // Compare accumulator
void cpx(cpu_t *cpu, instruction_t *instruction); // Compare X register
void cpy(cpu_t *cpu, instruction_t *instruction); // Compare Y register
void bit(cpu_t *cpu, instruction_t *instruction); // Bit test

/* Branch operations */
void bcc(cpu_t *cpu, instruction_t *instruction); // Branch if carry clear
void bcs(cpu_t *cpu, instruction_t *instruction); // Branch if carry set
void beq(cpu_t *cpu, instruction_t *instruction); // Branch if equal (zero set)
void bne(cpu_t *cpu, instruction_t *instruction); // Branch if not equal (zero clear)
void bmi(cpu_t *cpu, instruction_t *instruction); // Branch if minus (negative set)
void bpl(cpu_t *cpu, instruction_t *instruction); // Branch if plus (negative clear)
void bvc(cpu_t *cpu, instruction_t *instruction); // Branch if overflow clear
void bvs(cpu_t *cpu, instruction_t *instruction); // Branch if overflow set

/* Jump and subroutine operations */
void jmp(cpu_t *cpu, instruction_t *instruction); // Jump
void jsr(cpu_t *cpu, instruction_t *instruction); // Jump to subroutine
void rti(cpu_t *cpu, instruction_t *instruction); // Return from subroutine
void rts(cpu_t *cpu, instruction_t *instruction); // Return from interrupt
void brk(cpu_t *cpu, instruction_t *instruction); // Force break/interrupt

/* Load and store operations */
void lda(cpu_t *cpu, instruction_t *instruction); // Load accumulator
void ldx(cpu_t *cpu, instruction_t *instruction); // Load X register
void ldy(cpu_t *cpu, instruction_t *instruction); // Load Y register
void sta(cpu_t *cpu, instruction_t *instruction); // Store accumulator
void stx(cpu_t *cpu, instruction_t *instruction); // Store X register
void sty(cpu_t *cpu, instruction_t *instruction); // Store Y register

/* Increment and decrement operations */
void inc(cpu_t *cpu, instruction_t *instruction); // Increment memory
void dec(cpu_t *cpu, instruction_t *instruction); // Decrement memory
void inx(cpu_t *cpu, instruction_t *instruction); // Increment X register
void dex(cpu_t *cpu, instruction_t *instruction); // Decrement X register
void iny(cpu_t *cpu, instruction_t *instruction); // Increment Y register
void dey(cpu_t *cpu, instruction_t *instruction); // Decrement Y register

/* Register transfer operations */
void tax(cpu_t *cpu, instruction_t *instruction); // Transfer A to X
void tay(cpu_t *cpu, instruction_t *instruction); // Transfer A to T
void txa(cpu_t *cpu, instruction_t *instruction); // Transfer X to A
void tya(cpu_t *cpu, instruction_t *instruction); // transfer Y to A
void tsx(cpu_t *cpu, instruction_t *instruction); // Transfer stack pointer to X
void txs(cpu_t *cpu, instruction_t *instruction); // Transfer X to stack pointer

/* Stack operations */
void pha(cpu_t *cpu, instruction_t *instruction); // Push accumulator
void pla(cpu_t *cpu, instruction_t *instruction); // Pull accumulator
void php(cpu_t *cpu, instruction_t *instruction); // Push processor status
void plp(cpu_t *cpu, instruction_t *instruction); // Pull processor status

/* Status flag operations */
void clc(cpu_t *cpu, instruction_t *instruction); // Clear carry flag
void sec(cpu_t *cpu, instruction_t *instruction); // Set carry flag
void cli(cpu_t *cpu, instruction_t *instruction); // Clear interrupt disable
void sei(cpu_t *cpu, instruction_t *instruction); // Set interrup disable
void cld(cpu_t *cpu, instruction_t *instruction); // Clear decimal flag
void sed(cpu_t *cpu, instruction_t *instruction); // Set decimal flag
void clv(cpu_t *cpu, instruction_t *instruction); // Clear overflow flag

/* Miscellaneous operations*/
void nop(cpu_t *cpu, instruction_t *instruction); // No operation

/* Helper functions */
void load_register(cpu_t *cpu, instruction_t *instruction, uint8_t *target_register);
void store_register(cpu_t *cpu, instruction_t *instruction, uint8_t source_register);
void compare_register(cpu_t *cpu, instruction_t *instruction, uint8_t register_value);
void increment_value(cpu_t *cpu, uint8_t *target);
void decrement_value(cpu_t *cpu, uint8_t *target);
void transfer_register(cpu_t *cpu, uint8_t source_value, uint8_t *target_register);
void clear_flag(cpu_t *cpu, status_flag_t flag);
void set_flag(cpu_t *cpu, status_flag_t flag);
void branch_if(cpu_t *cpu, instruction_t *instruction, bool condition);

#endif
