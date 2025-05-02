#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "core/opcodes.h"
#include "core/cpu.h"

// Inicializa los registros del microprocesador
int main(int argc, char *argv[]) {
    // Si no se pasan los parametros necesarios
    if(argc < 6) {
        printf("El programa debe ejecutarse con los siguientes parametros:\n./mos6502 [nombre de archivo rom]\n-log [nombre de archivo para setear el log]\n-halt o -ciclos [numero de instruccion hexadecimal o numero de ciclos]\n");
        return 1;
    }

    cpu_t *cpu = cpu_create();
    if(cpu == NULL) {
        return 1;
    }

    if(!cpu_load_rom(cpu, argv[1])) {
        return 1;
    }

    // Condicion de corte con parametro de ciclos (83007452)
    if(!strcmp(argv[4], "-ciclos")) {
        long ejecutados;
        ejecutados = atoi(argv[5]);

        while(cpu->total_execution_cycles < ejecutados) {
            if(!strcmp(argv[2], "-log"))
            	cpu_log_state(cpu, argv[3]);

            cpu_execute_instruction(cpu);
        }
    }
    // Condicion de corte con parametro de instruccion (336d)
    else if(!strcmp(argv[4], "-halt")) {
        uint16_t aux;
        aux = (uint16_t)strtol(argv[5], NULL, 16);

        while(1) {
            if(!strcmp(argv[2], "-log"))
                cpu_log_state(cpu, argv[3]);

            if(cpu->program_counter == aux)
                break;

            cpu_execute_instruction(cpu);
        }
    }

    printf("Ciclos finales: %ld\n", cpu->total_execution_cycles);
    cpu_destroy(cpu);
    printf("Success!\n");
    return 0;
}