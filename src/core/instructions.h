#ifndef OPERACIONES
#define OPERACIONES

#include <stdint.h>

#include "status.h"
#include "cpu.h"

void adc(cpu_t *cpu, instruction_t *instruction);
void and(cpu_t *cpu, instruction_t *instruction);
void asl(cpu_t *cpu, instruction_t *instruction);
void bcc(cpu_t *cpu, instruction_t *instruction);
void bcs(cpu_t *cpu, instruction_t *instruction);
void beq(cpu_t *cpu, instruction_t *instruction);
void bit(cpu_t *cpu, instruction_t *instruction);
void bmi(cpu_t *cpu, instruction_t *instruction);
void bne(cpu_t *cpu, instruction_t *instruction);
void bpl(cpu_t *cpu, instruction_t *instruction);
void brk(cpu_t *cpu, instruction_t *instruction);
void bvc(cpu_t *cpu, instruction_t *instruction);
void bvs(cpu_t *cpu, instruction_t *instruction);
void clear(cpu_t *cpu, status_flag_t flag);
void clc(cpu_t *cpu, instruction_t *instruction);
void cld(cpu_t *cpu, instruction_t *instruction);
void cli(cpu_t *cpu, instruction_t *instruction);
void clv(cpu_t *cpu, instruction_t *instruction);
void compare(cpu_t *cpu, instruction_t *instruction, uint8_t *registro);
void cmp(cpu_t *cpu, instruction_t *instruction);
void cpx(cpu_t *cpu, instruction_t *instruction);
void cpy(cpu_t *cpu, instruction_t *instruction);
void decrement(cpu_t*cpu, uint8_t *registro);
void dec(cpu_t *cpu, instruction_t *instruction);
void dex(cpu_t *cpu, instruction_t *instruction);
void dey(cpu_t *cpu, instruction_t *instruction);
void eor(cpu_t *cpu, instruction_t *instruction);
void increment(cpu_t *cpu, uint8_t *registro);
void inc(cpu_t *cpu, instruction_t *instruction);
void inx(cpu_t *cpu, instruction_t *instruction);
void iny(cpu_t *cpu, instruction_t *instruction);
void jmp(cpu_t *cpu, instruction_t *instruction);
void jsr(cpu_t *cpu, instruction_t *instruction);
void lsr(cpu_t *cpu, instruction_t *instruction);
void load(cpu_t *cpu, instruction_t *instruction, uint8_t *registro);
void lda(cpu_t *cpu, instruction_t *instruction);
void ldx(cpu_t *cpu, instruction_t *instruction);
void ldy(cpu_t *cpu, instruction_t *instruction);
void nop(cpu_t *cpu, instruction_t *instruction);
void ora(cpu_t *cpu, instruction_t *instruction);
void pha(cpu_t *cpu, instruction_t *instruction);
void php(cpu_t *cpu, instruction_t *instruction);
void pla(cpu_t *cpu, instruction_t *instruction);
void plp(cpu_t *cpu, instruction_t *instruction);
void rol(cpu_t *cpu, instruction_t *instruction);
void ror(cpu_t *cpu, instruction_t *instruction);
void rti(cpu_t *cpu, instruction_t *instruction);
void rts(cpu_t *cpu, instruction_t *instruction);
void sbc(cpu_t *cpu, instruction_t *instruction);
void sec(cpu_t *cpu, instruction_t *instruction);
void sed(cpu_t *cpu, instruction_t *instruction);
void sei(cpu_t *cpu, instruction_t *instruction);
void sta(cpu_t *cpu, instruction_t *instruction);
void stx(cpu_t *cpu, instruction_t *instruction);
void sty(cpu_t *cpu, instruction_t *instruction);
void transfer(cpu_t *cpu, uint8_t *registro);
void tax(cpu_t *cpu, instruction_t *instruction);
void tay(cpu_t *cpu, instruction_t *instruction);
void tsx(cpu_t *cpu, instruction_t *instruction);
void txa(cpu_t *cpu, instruction_t *instruction);
void txs(cpu_t *cpu, instruction_t *instruction);
void tya(cpu_t *cpu, instruction_t *instruction);

#endif
