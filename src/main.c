#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <errno.h>

#include "core/cpu.h"

#define DEFAULT_LOG_PATH "logs/log.txt"

void print_usage(const char *program_name) {
    printf("Usage: %s <rom_file> [options]\n\n", program_name);
    printf("Arguments:\n");
    printf("  <rom_file>           ROM file to load (required)\n");
    printf("  -halt <address>      Stop execution at hexadecimal address (e.g., 336d)\n");
    printf("  -cycles <count>      Stop execution after specified number of cycles\n");
    printf("  -log <log_file>      Log CPU state to file (optional, defaults to %s)\n", DEFAULT_LOG_PATH);
    printf("  -nolog               Disable logging\n\n");
    printf("If neither -halt nor -cycles is specified, the program will run until\n");
    printf("it writes to the halt port ($E001) or encounters an infinite loop.\n\n");
    printf("Examples:\n");
    printf("  %s hello.rom                    # Run until program halts\n", program_name);
    printf("  %s game.rom -cycles 1000        # Run for 1000 cycles\n", program_name);
    printf("  %s game.rom -halt 336d          # Stop at address 0x336d\n", program_name);
    printf("  %s game.rom -nolog              # Run without logging\n", program_name);
}

bool create_log_directory(const char *log_path) {
    // Extract directory from log path
    char *last_slash = strrchr(log_path, '/');
    if (last_slash == NULL) {
        return true; // No directory to create
    }

    // Create a copy of the path up to the last slash
    size_t dir_len = last_slash - log_path;
    char *dir_path = malloc(dir_len + 1);
    if (dir_path == NULL) {
        return false;
    }

    strncpy(dir_path, log_path, dir_len);
    dir_path[dir_len] = '\0';

    // Create directory (mkdir returns 0 on success, -1 on failure)
    // Note: This is Unix/Linux specific. For Windows, use _mkdir
    #ifdef _WIN32
        int result = _mkdir(dir_path);
    #else
        int result = mkdir(dir_path, 0755);
    #endif

    free(dir_path);

    // Return true if directory was created or already exists
    return result == 0 || errno == EEXIST;
}

int main(int argc, char *argv[]) {
    // Minimum arguments: program_name, rom_file
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    // Parse arguments
    const char *rom_file = argv[1];
    const char *log_file = DEFAULT_LOG_PATH;
    bool use_halt = false;
    bool use_cycles = false;
    bool enable_logging = true;
    uint16_t halt_address = 0;
    long target_cycles = 0;

    // Parse optional flags
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-halt") == 0) {
            if (i + 1 >= argc) {
                printf("Error: -halt flag requires a hexadecimal address\n");
                print_usage(argv[0]);
                return 1;
            }
            if (use_cycles) {
                printf("Error: Cannot use both -halt and -cycles flags\n");
                print_usage(argv[0]);
                return 1;
            }
            halt_address = (uint16_t)strtol(argv[i + 1], NULL, 16);
            use_halt = true;
            i++; // Skip the address argument
        }
        else if (strcmp(argv[i], "-cycles") == 0) {
            if (i + 1 >= argc) {
                printf("Error: -cycles flag requires a number\n");
                print_usage(argv[0]);
                return 1;
            }
            if (use_halt) {
                printf("Error: Cannot use both -halt and -cycles flags\n");
                print_usage(argv[0]);
                return 1;
            }
            target_cycles = atol(argv[i + 1]);
            if (target_cycles <= 0) {
                printf("Error: Cycle count must be a positive number\n");
                return 1;
            }
            use_cycles = true;
            i++; // Skip the cycle count argument
        }
        else if (strcmp(argv[i], "-log") == 0) {
            if (i + 1 >= argc) {
                printf("Error: -log flag requires a filename\n");
                print_usage(argv[0]);
                return 1;
            }
            log_file = argv[i + 1];
            i++; // Skip the filename argument
        }
        else if (strcmp(argv[i], "-nolog") == 0) {
            enable_logging = false;
        }
        else {
            printf("Error: Unknown flag '%s'\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }
    }

    // Create CPU
    cpu_t *cpu = cpu_create();
    if(cpu == NULL) {
        printf("Error: Failed to create CPU\n");
        return 1;
    }

    // Load ROM
    if(!cpu_load_rom(cpu, argv[1])) {
        printf("Error: Failed to load ROM file '%s'\n", rom_file);
        cpu_destroy(cpu);
        return 1;
    }

    // Create log directory if needed
    if (enable_logging && !create_log_directory(log_file)) {
        printf("Warning: Could not create log directory for '%s'\n", log_file);
    }

    printf("Starting MOS 6502 emulation...\n");
    printf("ROM file: %s\n", rom_file);
    if (use_halt) {
        printf("Execution mode: Halt at address 0x%04X\n", halt_address);
    } else if (use_cycles) {
        printf("Execution mode: Run for %ld cycles\n", target_cycles);
    } else {
        printf("Execution mode: Run until program halts\n");
    }
    if (enable_logging) {
        printf("Logging to: %s\n", log_file);
    }
    printf("\n");

    // Main execution loop
    while (!cpu->halted) {
        if (enable_logging) {
            cpu_log_state(cpu, log_file);
        }

        // Check exit conditions before executing next instruction
        if (use_cycles && cpu->total_execution_cycles >= target_cycles) {
            printf("Reached target cycle count (%ld)\n", target_cycles);
            break;
        }
        if (use_halt && cpu->program_counter == halt_address) {
            printf("Reached halt address (0x%04X)\n", halt_address);
            break;
        }

        cpu_execute_instruction(cpu);
    }

    printf("Execution completed!\n");
    printf("Final cycles: %ld\n", cpu->total_execution_cycles);
    printf("Final PC: 0x%04X\n", cpu->program_counter);

    if (enable_logging) {
        printf("CPU state log saved to: %s\n", log_file);
    }

    cpu_destroy(cpu);
    return 0;
}

