#ifndef OPERACIONES
#define OPERACIONES

#include <stdint.h>

#include "status.h"
#include "cpu.h"

void adc(mos6502_t *p, instruccion_t *i);
void and(mos6502_t *p, instruccion_t *i);
void asl(mos6502_t *p, instruccion_t *i);
void bcc(mos6502_t *p, instruccion_t *i); 
void bcs(mos6502_t *p, instruccion_t *i);
void beq(mos6502_t *p, instruccion_t *i);
void bit(mos6502_t *p, instruccion_t *i);
void bmi(mos6502_t *p, instruccion_t *i);
void bne(mos6502_t *p, instruccion_t *i);
void bpl(mos6502_t *p, instruccion_t *i);
void brk(mos6502_t *p, instruccion_t *i);
void bvc(mos6502_t *p, instruccion_t *i);
void bvs(mos6502_t *p, instruccion_t *i);
void clear(mos6502_t *p, flag_t flag);
void clc(mos6502_t *p, instruccion_t *i);
void cld(mos6502_t *p, instruccion_t *i);
void cli(mos6502_t *p, instruccion_t *i);
void clv(mos6502_t *p, instruccion_t *i);
void compare(mos6502_t *p, instruccion_t *i, uint8_t *registro);
void cmp(mos6502_t *p, instruccion_t *i);
void cpx(mos6502_t *p, instruccion_t *i);
void cpy(mos6502_t *p, instruccion_t *i);
void decrement(mos6502_t*p, uint8_t *registro);
void dec(mos6502_t *p, instruccion_t *i);
void dex(mos6502_t *p, instruccion_t *i);
void dey(mos6502_t *p, instruccion_t *i);
void eor(mos6502_t *p, instruccion_t *i);
void increment(mos6502_t *p, uint8_t *registro);
void inc(mos6502_t *p, instruccion_t *i);
void inx(mos6502_t *p, instruccion_t *i);
void iny(mos6502_t *p, instruccion_t *i);
void jmp(mos6502_t *p, instruccion_t *i);
void jsr(mos6502_t *p, instruccion_t *i);
void lsr(mos6502_t *p, instruccion_t *i);
void load(mos6502_t *p, instruccion_t *i, uint8_t *registro);
void lda(mos6502_t *p, instruccion_t *i);
void ldx(mos6502_t *p, instruccion_t *i);
void ldy(mos6502_t *p, instruccion_t *i);
void nop(mos6502_t *p, instruccion_t *i);
void ora(mos6502_t *p, instruccion_t *i);
void pha(mos6502_t *p, instruccion_t *i);
void php(mos6502_t *p, instruccion_t *i);
void pla(mos6502_t *p, instruccion_t *i);
void plp(mos6502_t *p, instruccion_t *i);
void rol(mos6502_t *p, instruccion_t *i);
void ror(mos6502_t *p, instruccion_t *i);
void rti(mos6502_t *p, instruccion_t *i);
void rts(mos6502_t *p, instruccion_t *i);
void sbc(mos6502_t *p, instruccion_t *i);
void sec(mos6502_t *p, instruccion_t *i);
void sed(mos6502_t *p, instruccion_t *i);
void sei(mos6502_t *p, instruccion_t *i);
void sta(mos6502_t *p, instruccion_t *i);
void stx(mos6502_t *p, instruccion_t *i);
void sty(mos6502_t *p, instruccion_t *i);
void transfer(mos6502_t *p, uint8_t *registro);
void tax(mos6502_t *p, instruccion_t *i);
void tay(mos6502_t *p, instruccion_t *i);
void tsx(mos6502_t *p, instruccion_t *i);
void txa(mos6502_t *p, instruccion_t *i);
void txs(mos6502_t *p, instruccion_t *i);
void tya(mos6502_t *p, instruccion_t *i);

#endif
