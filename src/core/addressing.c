#include "addressing.h"

// Modos de direccionamiento de memoria

// No indexados, no en memoria
void implicito(mos6502_t *p, instruccion_t *i) {
	i->m = NULL;
}

void acumulador(mos6502_t *p, instruccion_t *i) {
    i->m = &(p->a);
}

void inmediato(mos6502_t *p, instruccion_t *i) {
    i->m = &(p->mem[p->pc++]);
}

// No indexados, en memoria
void relativo(mos6502_t *p, instruccion_t *i) {
	i->m = &(p->mem[p->pc++]);
}

void absoluto(mos6502_t *p, instruccion_t *i) {
    i->direccion = p->mem[p->pc++];
    i->direccion |= p->mem[p->pc++] << 8;
    i->m = &(p->mem[i->direccion]);
}

void pagina_cero(mos6502_t *p, instruccion_t *i) {
	i->direccion = p->mem[p->pc++];
	i->m = &(p->mem[i->direccion]);
}

void indirecto(mos6502_t *p, instruccion_t *i) {
	i->direccion = p->mem[p->pc++];
    i->direccion |= p->mem[p->pc++] << 8;
    uint16_t aux = i->direccion;
    i->direccion = p->mem[aux++];
    i->direccion |= p->mem[aux] << 8;
}

// Indexadas
void absoluto_x(mos6502_t *p, instruccion_t *i) {
	i->direccion = p->mem[p->pc++];
	i->direccion |= p->mem[p->pc++] << 8;
	i->direccion += p->x;
	i->m = &(p->mem[i->direccion]);
}

void absoluto_y(mos6502_t *p, instruccion_t *i) {
	i->direccion = p->mem[p->pc++];
	i->direccion |= p->mem[p->pc++] << 8;
	i->direccion += p->y;
	i->m = &(p->mem[i->direccion]);
}

void pagina_cero_x(mos6502_t *p, instruccion_t *i) {
	i->direccion = p->mem[p->pc++];
	i->direccion += p->x;
	i->direccion &= 0xFF;
	i->m = &(p->mem[i->direccion]);
}

void pagina_cero_y(mos6502_t *p, instruccion_t *i) {
	i->direccion = p->mem[p->pc++];
	i->direccion += p->y;
	i->direccion &= 0xFF;
	i->m = &(p->mem[i->direccion]);
}

void indirecto_x(mos6502_t *p, instruccion_t *i) {
	i->direccion = p->mem[p->pc++];
	i->direccion += p->x;
	i->direccion &= 0xFF;
	uint16_t aux = i->direccion;
    i->direccion = p->mem[aux++];
    i->direccion |= p->mem[aux] << 8;
    i->m = &(p->mem[i->direccion]);
}

void indirecto_y(mos6502_t *p, instruccion_t *i) {
	i->direccion = p->mem[p->pc++];
    uint16_t aux = i->direccion;
    i->direccion = p->mem[aux++];
    i->direccion |= p->mem[aux] << 8;
    i->direccion += p->y;
    i->m = &(p->mem[i->direccion]);
}
