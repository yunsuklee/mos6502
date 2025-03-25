#ifndef DICCIONARIO
#define DICCIONARIO

#include <stdint.h>

#include "mos6502.h"
#include "operaciones.h"
#include "direccionamiento.h"

typedef void (*operacion_t)(mos6502_t *, instruccion_t *);
typedef void (*direcc_t)(mos6502_t *, instruccion_t *);

typedef struct {   
    direcc_t direccionamiento;
    operacion_t operacion;   
    uint8_t ciclos;
} dicc_t;

extern dicc_t diccionario[]; 

#endif
