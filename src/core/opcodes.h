#ifndef DICCIONARIO
#define DICCIONARIO

#include <stdint.h>

#include "cpu.h"
#include "instructions.h"
#include "addressing.h"

typedef void (*operacion_t)(cpu_t *, instruction_t *);
typedef void (*direcc_t)(cpu_t *, instruction_t *);

typedef struct {
    direcc_t direccionamiento;
    operacion_t operacion;
    uint8_t ciclos;
} dicc_t;

extern dicc_t diccionario[];

#endif
