#ifndef DIRECCIONAMIENTO
#define DIRECCIONAMIENTO

#include <stdlib.h>
#include "mos6502.h"

void implicito(mos6502_t *p, instruccion_t *i);
void acumulador(mos6502_t *p, instruccion_t *i);
void inmediato(mos6502_t *p, instruccion_t *i);

void relativo(mos6502_t *p, instruccion_t *i);
void absoluto(mos6502_t *p, instruccion_t *i);
void pagina_cero(mos6502_t *p, instruccion_t *i);
void indirecto(mos6502_t *p, instruccion_t *i);

void absoluto_x(mos6502_t *p, instruccion_t *i);
void absoluto_y(mos6502_t *p, instruccion_t *i);
void pagina_cero_x(mos6502_t *p, instruccion_t *i);
void pagina_cero_y(mos6502_t *p, instruccion_t *i);
void indirecto_x(mos6502_t *p, instruccion_t *i);
void indirecto_y(mos6502_t *p, instruccion_t *i);

#endif
