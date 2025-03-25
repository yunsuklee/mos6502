#include "mos6502.h"
#include "dicc.h"

mos6502_t *crear_micro() {
    mos6502_t *m = malloc(sizeof(mos6502_t));
    if(m == NULL)
        return NULL;

    m->mem = malloc(sizeof(uint8_t) * 65536);
    if(m->mem == NULL) {
    	free(m);
    	return NULL;
    }

    m->a = m->x = m->y = 0;
    m->status = 0x00;
    m->mem = m->mem;
    m->pc = 0;
    m->sp = 0xFF;
    m->ciclos = 0;

    return m;
}

void destruir_micro(mos6502_t *m) {
	free(m->mem);
	free(m);
}

bool cargar_rom(const char *r, mos6502_t *m) {
    uint16_t i = 0;
    FILE *rom = fopen(r, "rb");
    if(rom == NULL)
        return false;

    while(fread(&m->mem[i], sizeof(uint8_t), 1, rom) == 1 && i < 65536) {        
        i++;  
    }
    
    m->pc = (m->mem[0XFFFC] >> 8) | (m->mem[0XFFFD] << 8);
    
    fclose(rom);
    return true; 
}

void resetear_microprocesador(mos6502_t *m, uint8_t *mem, uint16_t pc) {
    m->a = m->x = m->y = 0;
    m->status = 0x00;
    m->mem = mem;
    m->pc = pc;
    m->sp = 0xFF;
    m->ciclos = 0;
}

void ejecutar_instruccion(mos6502_t *m) {
    instruccion_t i;
    i.codigo = m->mem[m->pc];
    m->pc++;
    i.ciclos = diccionario[i.codigo].ciclos;
    diccionario[i.codigo].direccionamiento(m, &i);
    diccionario[i.codigo].operacion(m, &i);
    m->ciclos += i.ciclos;
}

bool set_log(const char *r, mos6502_t *m) {
    FILE *escritura = fopen(r, "a");
    if(escritura == NULL)
        return false;

    fprintf(escritura, "%04x %02x %02x %02x %02x %02x\n", m->pc, m->a, m->x, m->y, m->status, m->sp);

    fclose(escritura);
    return true;
}
