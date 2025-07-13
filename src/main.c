#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "core/cpu.h"

#define DEFAULT_LOG_PATH "log/log.txt"

void print_usage(const char *program_name) {
    printf("Usage: %s <rom_file> [-halt <address> | -cycles <count>] [-log <log_file>]\n\n", program_name);
    printf("Arguments:\n");
    printf("  <rom_file>           ROM file to load (required)\n");
    printf("  -halt <address>      Stop execution at hexadecimal address (e.g., 336d)\n");
    printf("  -cycles <count>      Stop execution after specified number of cycles\n");
    printf("  -log <log_file>      Log CPU state to file (optional, defaults to %s)\n\n", DEFAULT_LOG_PATH);
    printf("Examples:\n");
    printf("  %s game.rom -cycles 1000\n", program_name);
    printf("  %s game.rom -halt 336d -log debug.txt\n", program_name);
    printf("  %s game.rom -cycles 5000 -log states.log\n", program_name);
}

int main(int argc, char *argv[]) {
    // Minimum arguments: program_name, rom_file, halt_or_cycles_flag, value
    if (argc < 4) {
        print_usage(argv[0]);
        return 1;
    }

    cpu_t *cpu = cpu_create();
    if(cpu == NULL) {
        return 1;
    }

    if(!cpu_load_rom(cpu, argv[1])) {
        return 1;
    }

    if(!strcmp(argv[4], "-ciclos")) {
        long ejecutados;
        ejecutados = atoi(argv[5]);

        while(cpu->total_execution_cycles < ejecutados) {
            if(!strcmp(argv[2], "-log"))
            	cpu_log_state(cpu, argv[3]);

            cpu_execute_instruction(cpu);
        }
    }
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

    printf("Total execution cycles: %ld\n", cpu->total_execution_cycles);
    cpu_destroy(cpu);
    printf("Success!\n");
    return 0;
}

