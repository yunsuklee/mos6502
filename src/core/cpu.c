#include "cpu.h"
#include "opcodes.h"

static bool allocate_cpu_memory(cpu_t *cpu) {
    cpu->memory = calloc(CPU_MEMORY_SIZE, sizeof(uint8_t));
    return cpu->memory != NULL;
}

static void initialize_cpu_registers(cpu_t *cpu) {
    cpu->accumulator = 0;
    cpu->x_index_register = 0;
    cpu->y_index_register = 0;
    cpu->program_counter = 0;
    cpu->status_register = CPU_STATUS_CLEAR;
    cpu->stack_pointer = CPU_STACK_INIT;
    cpu->total_execution_cycles = 0;
    cpu->halted = false;
}

cpu_t *cpu_create(void) {
    cpu_t *cpu = malloc(sizeof(cpu_t));
    if(cpu == NULL)
        return NULL;

    if(!allocate_cpu_memory(cpu)) {
        free(cpu);
        return NULL;
    }

    initialize_cpu_registers(cpu);
    return cpu;
}

void cpu_destroy(cpu_t *cpu) {
	free(cpu->memory);
	free(cpu);
}

void cpu_reset(cpu_t *cpu, uint8_t *memory, uint16_t program_counter) {
    cpu->accumulator = 0;
    cpu->x_index_register = 0;
    cpu->y_index_register = 0;
    cpu->status_register = CPU_STATUS_CLEAR;

    if (memory != NULL) {
        cpu->memory = memory;
    }

    cpu->program_counter = program_counter;
    cpu->stack_pointer = CPU_STACK_INIT;
    cpu->total_execution_cycles = 0;
    cpu->halted = false;
}

static uint8_t cpu_fetch_opcode(cpu_t *cpu) {
    uint8_t opcode = cpu->memory[cpu->program_counter];
    cpu->program_counter++;
    return opcode;
}

void cpu_execute_instruction(cpu_t *cpu) {
    instruction_t instruction;
    instruction.opcode = cpu_fetch_opcode(cpu);
    instruction.page_boundary_crossed = false;

    instruction.required_execution_cycles = opcodes_dictionary[instruction.opcode].cycles;
    opcodes_dictionary[instruction.opcode].addressing_mode(cpu, &instruction);
    opcodes_dictionary[instruction.opcode].operation(cpu, &instruction);

    if (instruction.page_boundary_crossed &&
        opcodes_dictionary[instruction.opcode].extra_cycle_for_page_cross) {
        instruction.required_execution_cycles++;
    }

    cpu->total_execution_cycles += instruction.required_execution_cycles;
}

void cpu_write_memory(cpu_t *cpu, uint16_t address, uint8_t value) {
    if (address == CPU_CHAR_OUTPUT_PORT) {
        // Handle character output
        if (value >= 0x20 && value <= 0x7E) {
            // Printable ASCII characters
            putchar(value);
        } else if (value == 0x0A) {
            // Line feed - convert to CRLF for better terminal compatibility
            putchar('\r');
            putchar('\n');
        } else if (value == 0x0D) {
            // Carriage return
            putchar('\r');
        }
        fflush(stdout);
    } else if (address == CPU_HALT_PORT) {
        // Handle halt signal - any write to this port halts the CPU
        cpu->halted = true;
        printf("Program requested halt (exit code: %d)\n", value);
    } else {
        // Normal memory write
        cpu->memory[address] = value;
    }
}

static size_t cpu_load_rom_into_memory(cpu_t *cpu, FILE *rom_file) {
    size_t bytes_loaded = 0;

    while(bytes_loaded < CPU_MEMORY_SIZE &&
          fread(&cpu->memory[bytes_loaded], sizeof(uint8_t), 1, rom_file) == 1) {
        bytes_loaded++;
    }

    return bytes_loaded;
}

static void cpu_set_program_counter_from_reset_vector(cpu_t *cpu) {
    uint8_t low_byte = cpu->memory[CPU_RESET_VECTOR_LOW];
    uint8_t high_byte = cpu->memory[CPU_RESET_VECTOR_HIGH];

    // Combine bytes to form 16-bit address (little-endian)
    cpu->program_counter = low_byte | (high_byte << BIT_SHIFT_BYTE);
}

bool cpu_load_rom(cpu_t *cpu, const char *rom_path) {
    FILE *rom_file = fopen(rom_path, "rb");
    if(rom_file == NULL) {
        return false;
    }

    size_t bytes_loaded = cpu_load_rom_into_memory(cpu, rom_file);

    cpu_set_program_counter_from_reset_vector(cpu);

    fclose(rom_file);
    return bytes_loaded > 0;
}

bool cpu_log_state(cpu_t *cpu, const char *log_file_path) {
    FILE *log_file = fopen(log_file_path, "a");
    if(log_file == NULL) {
        return false;
    }

    // Format: PC A X Y Status SP
    fprintf(log_file, "%04x %02x %02x %02x %02x %02x\n",
            cpu->program_counter,
            cpu->accumulator,
            cpu->x_index_register,
            cpu->y_index_register,
            cpu->status_register,
            cpu->stack_pointer);

    fclose(log_file);
    return true;
}
