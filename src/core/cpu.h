#ifndef MOS6502
#define MOS6502

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    uint8_t a, x, y;    // Registros A, X e Y.
    uint16_t pc;        // Program counter.
    uint8_t status;     // Registro de status.
    uint8_t sp;         // Stack pointer.
    uint8_t *mem;       // Memoria.

    long ciclos;        // Cantidad de ciclos totales de ejecución.
} mos6502_t;

typedef struct {
    uint8_t codigo;     // Opcode.
    short ciclos;       // Cantidad de ciclos de la instrucción.
    uint8_t *m;         // Puntero al operando (registro o memoria).
    uint16_t direccion; // Dirección del operando (si corresponde).
} instruccion_t;

mos6502_t *crear_micro();
void destruir_micro(mos6502_t *m);
bool cargar_rom(const char *r, mos6502_t *m);
void resetear_microprocesador(mos6502_t *m, uint8_t *mem, uint16_t pc);
void ejecutar_instruccion(mos6502_t *m);
bool set_log(const char *r, mos6502_t *m);

#endif