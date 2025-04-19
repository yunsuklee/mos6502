#ifndef DIRECCIONAMIENTO
#define DIRECCIONAMIENTO

#include <stdlib.h>
#include "cpu.h"

void implicito(cpu_t *p, instruction_t *i);
void acumulador(cpu_t *p, instruction_t *i);
void inmediato(cpu_t *p, instruction_t *i);

void relativo(cpu_t *p, instruction_t *i);
void absoluto(cpu_t *p, instruction_t *i);
void pagina_cero(cpu_t *p, instruction_t *i);
void indirecto(cpu_t *p, instruction_t *i);

void absoluto_x(cpu_t *p, instruction_t *i);
void absoluto_y(cpu_t *p, instruction_t *i);
void pagina_cero_x(cpu_t *p, instruction_t *i);
void pagina_cero_y(cpu_t *p, instruction_t *i);
void indirecto_x(cpu_t *p, instruction_t *i);
void indirecto_y(cpu_t *p, instruction_t *i);

#endif
