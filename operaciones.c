#include "operaciones.h"

void adc(mos6502_t *p, instruccion_t *i) {
    uint8_t a = p->a;
    uint16_t aux = (uint16_t)p->a + (uint16_t)(*i->m) + (uint16_t)get_status(&p->status, CARRY);
    p->a = aux;

    set_carry(&p->status,aux);
    set_zero(&p->status, p->a);
    set_negative(&p->status, p->a);
    set_overflow(&p->status, a, *i->m, p->a);
}

void and(mos6502_t *p, instruccion_t *i) {
    p->a &= *i->m;
    
    set_zero(&p->status, p->a);
    set_negative(&p->status, p->a);
}

void asl(mos6502_t *p, instruccion_t *i) { 
    uint16_t aux = *i->m << 1;
    *i->m = aux;

    set_zero(&p->status, *i->m);
    set_negative(&p->status, *i->m);
    set_carry(&p->status, aux);
}

void bcc(mos6502_t *p, instruccion_t *i) {
    if(!get_status(&p->status, CARRY))
        p->pc += *((int8_t *)i->m);
}

void bcs(mos6502_t *p, instruccion_t *i) {
    if(get_status(&p->status, CARRY))
        p->pc += *((int8_t *)i->m);
}

void beq(mos6502_t *p, instruccion_t *i) {
    if(get_status(&p->status,ZERO))
        p->pc += *((int8_t *)i->m);
}

void bit(mos6502_t *p, instruccion_t *i) {
    set_negative(&p->status, *i->m);
    set_zero(&p->status, p->a & (*i->m));
    set_status(&p->status, OVERFLOW, (*i->m) & 0x40);
}

void bmi(mos6502_t *p, instruccion_t *i) {
    if(get_status(&p->status, NEGATIVE))
        p->pc += *((int8_t *)i->m);
}

void bne(mos6502_t *p, instruccion_t *i) {
    if(!get_status(&p->status, ZERO))
        p->pc += *((int8_t *)i->m);
}

void bpl(mos6502_t *p, instruccion_t *i) {
    if(!get_status(&p->status, NEGATIVE))
        p->pc += *((int8_t *)i->m);
}

void brk(mos6502_t *p, instruccion_t *i) {
    p->pc++;
    p->mem[0x100 | p->sp] = p->pc >> 8;
    p->sp--;
    p->mem[0x100 | p->sp] = p->pc;
    p->sp--;
    p->mem[0x100 | p->sp] = p->status | (1 << 4) | (1 << 5);
    p->sp--;

    set_status(&p->status, INTERRUPT_DISABLE, 1);

    p->pc = p->mem[0xFFFF] << 8;
    p->pc |= p->mem[0xFFFE];
}

void bvc(mos6502_t *p, instruccion_t *i) {  
    if(!get_status(&p->status , OVERFLOW))
        p->pc += *((int8_t *)i->m);
}

void bvs(mos6502_t *p, instruccion_t *i) {  
    if(get_status(&p->status, OVERFLOW))
        p->pc += *((int8_t *)i->m);
}

void clear(mos6502_t *p, flag_t flag) {
    set_status(&p->status, flag, 0);
}

void clc(mos6502_t *p, instruccion_t *i) {
    clear(p, CARRY);
}

void cld(mos6502_t *p, instruccion_t *i) {
    clear(p, DECIMAL);
}

void cli(mos6502_t *p, instruccion_t *i) {
    clear(p, INTERRUPT_DISABLE);
}

void clv(mos6502_t *p, instruccion_t *i) {
     clear(p, OVERFLOW);
}

void compare(mos6502_t *p, instruccion_t *i, uint8_t *registro) {
    set_status(&p->status, ZERO, *registro == (*i->m));
    set_status(&p->status, CARRY, *registro >= (*i->m));
    set_status(&p->status, NEGATIVE, *registro < (*i->m));
}

void cmp(mos6502_t *p, instruccion_t *i) {
    compare(p, i, &(p->a));
}

void cpx(mos6502_t *p, instruccion_t *i) {
    compare(p, i, &(p->x));
}

void cpy(mos6502_t *p, instruccion_t *i) {
    compare(p, i, &(p->y));
}

void decrement(mos6502_t*p, uint8_t *registro) {   
    *registro -= 1;

    set_zero(&p->status, *registro);
    set_negative(&p->status, *registro);
 }

void dec(mos6502_t *p, instruccion_t *i) {
    decrement(p, i->m);
}

void dex(mos6502_t *p, instruccion_t *i) {
    decrement(p, &(p->x));
}

void dey(mos6502_t *p, instruccion_t *i) {
    decrement(p, &(p->y));
}

void eor(mos6502_t *p, instruccion_t *i) {
    p->a ^= *i->m;

    set_zero(&p->status, p->a);
    set_negative(&p->status, p->a);
}

void increment(mos6502_t *p, uint8_t *registro) {
    *registro += 1;

    set_zero(&p->status, *registro);
    set_negative(&p->status, *registro);
}

void inc(mos6502_t *p, instruccion_t *i) {
    increment(p, i->m);
}

void inx(mos6502_t *p, instruccion_t *i) {
    increment(p, &(p->x)); 
}

void iny(mos6502_t *p, instruccion_t *i) {
    increment(p, &(p->y)); 
}

void jmp(mos6502_t *p, instruccion_t *i) {
    p->pc = i->direccion; 
}

void jsr(mos6502_t *p,instruccion_t *i) {
    p->pc--;
    p->mem[0x100 | p->sp] = p->pc >> 8;
    p->sp--;
    p->mem[0x100 | p->sp] = p->pc;
    p->sp--;
    p->pc = i->direccion; 
}

void load(mos6502_t *p, instruccion_t *i, uint8_t *registro) {
    *registro = *i->m;

    set_zero(&p->status, *i->m);
    set_negative(&p->status, *i->m);
}

void lda(mos6502_t *p, instruccion_t *i) {
    load(p, i, &(p->a));    
}

void ldx(mos6502_t *p, instruccion_t *i) {
    load(p, i, &(p->x));    
}

void ldy(mos6502_t *p, instruccion_t *i) {
    load(p, i, &(p->y));    
}

void lsr(mos6502_t *p,instruccion_t *i) {
    uint8_t bit_caido = (*i->m & 0x01);
    *i->m >>= 1;

    set_zero(&p->status, *i->m);
    set_negative(&p->status, *i->m);
    set_status(&p->status, CARRY, bit_caido);
}

void nop(mos6502_t *p, instruccion_t *i) {}

void ora(mos6502_t *p, instruccion_t *i) {
    p->a |= *i->m;
    
    set_zero(&p->status, p->a);
    set_negative(&p->status, p->a);
}

void pha(mos6502_t *p, instruccion_t *i) {
    p->mem[0x0100 | p->sp] = p->a;
    p->sp--;
}

void php(mos6502_t *p, instruccion_t *i) {
   	p->mem[0x100 | p->sp] = p->status | (1 << 4) | (1 << 5);
    p->sp--;
}

void pla(mos6502_t *p, instruccion_t *i) {
    p->sp++;
    p->a = p->mem[0x0100 | p->sp];

    set_zero(&p->status, p->a);
    set_negative(&p->status, p->a);
}   

void plp(mos6502_t *p, instruccion_t *i) {
    p->sp++;
    p->status = p->mem[0x100 | p->sp] & 0xCF;  
}   
 
void rol(mos6502_t *p, instruccion_t *i) {
    rotate_left(&p->status, i->m);

    set_zero(&p->status, *i->m);
    set_negative(&p->status, *i->m);
}

void ror(mos6502_t *p, instruccion_t *i) {  
    rotate_right(&p->status, i->m);

    set_zero(&p->status, *i->m);
    set_negative(&p->status, *i->m);
}   

void rti(mos6502_t *p, instruccion_t *i) {
  	p->sp++;
    p->status = p->mem[0x100 | p->sp] & 0xCF;
    p->sp++;
    p->pc = p->mem[0x100 | p->sp];
    p->sp++;
    p->pc |= p->mem[0x100 | p->sp] << 8;
}

void rts(mos6502_t *p, instruccion_t *i) {
    p->sp++;
    p->pc = p->mem[0x100 | p->sp] ;
    p->sp++;
    p->pc |= p->mem[0x100 | p->sp] << 8;
    p->pc++;   
}   

void sbc(mos6502_t *p, instruccion_t *i) {
    uint8_t a = p->a;
    uint16_t m = (uint16_t)(*i->m) ^ 0x00FF;
    uint16_t aux = (uint16_t)p->a + m + (uint16_t)get_status(&p->status, CARRY);
    p->a = aux;

    set_zero(&p->status, p->a);
    set_carry(&p->status, aux);
    set_negative(&p->status, p->a);
    set_overflow(&p->status, a, m, p->a);
}

void sec(mos6502_t *p, instruccion_t *i) {
    set_status(&p->status, CARRY, 1);
}

void sed(mos6502_t *p,instruccion_t *i) {
    set_status(&p->status, DECIMAL, 1);
}

void sei(mos6502_t *p,instruccion_t *i) {
    set_status(&p->status, INTERRUPT_DISABLE, 1);
}

void sta(mos6502_t *p, instruccion_t *i) {
    *i->m = p->a;
}

void stx(mos6502_t *p, instruccion_t *i) {
    *i->m = p->x;
}

void sty(mos6502_t *p, instruccion_t *i) {
    *i->m = p->y;
}

void transfer(mos6502_t *p, uint8_t *registro) {
    *registro = p->a;

    set_zero(&p->status, *registro);
    set_negative(&p->status, *registro);
}

void tax(mos6502_t *p,instruccion_t *i) {
    transfer(p, &(p->x));
}

void tay(mos6502_t *p, instruccion_t *i) {
    transfer(p, &(p->y));
}

void tsx(mos6502_t *p,instruccion_t *i) {
    p->x = p->sp;

    set_zero(&p->status, p->x);
    set_negative(&p->status, p->x);
}

void txa(mos6502_t *p,instruccion_t *i) {
    p->a = p->x;

    set_zero(&p->status, p->a);
    set_negative(&p->status, p->a);
}

void txs(mos6502_t *p,instruccion_t *i) {
    p->sp = p->x;
}

void tya(mos6502_t *p, instruccion_t *i) {
    p->a = p->y;
    
    set_zero(&p->status, p->a);
    set_negative(&p->status, p->a);
}
