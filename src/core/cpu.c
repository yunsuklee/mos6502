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
    cpu->status_register = 0x00;
    cpu->stack_pointer = 0xFF;
    cpu->total_execution_cycles = 0;
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
    cpu->memory = memory;
    cpu->program_counter = program_counter;
    cpu->stack_pointer = CPU_STACK_INIT;
    cpu->total_execution_cycles = 0;
}

static uint8_t cpu_fetch_opcode(cpu_t *cpu) {
    uint8_t opcode = cpu->memory[cpu->program_counter];
    cpu->program_counter++;
    return opcode;
}

void cpu_execute_instruction(cpu_t *cpu) {
    instruction_t instruction;
    instruction.opcode = cpu_fetch_opcode(cpu);

    instruction.required_execution_cycles = opcodes_dictionary[instruction.opcode].cycles;
    opcodes_dictionary[instruction.opcode].addressing_mode(cpu, &instruction);
    opcodes_dictionary[instruction.opcode].operation(cpu, &instruction);

    cpu->total_execution_cycles += instruction.required_execution_cycles;
}

static size_t cpu_load_rom_into_memory(cpu_t *cpu, FILE *rom_file) {
    uint16_t bytes_loaded = 0;

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
    cpu->program_counter = low_byte | (high_byte << 8);
}

bool cpu_load_rom(cpu_t *cpu, const char *rom_path) {
    FILE *rom_file = fopen(rom_path, "rb");
    if(rom_file == NULL)
        return false;

    size_t bytes_loaded = cpu_load_rom_into_memory(cpu, rom_file);

    cpu_set_program_counter_from_reset_vector(cpu);

    fclose(rom_file);
    return bytes_loaded > 0;
}

bool cpu_log_state(cpu_t *cpu, const char *log_file_path) {
    FILE *log_file = fopen(log_file_path, "a");
    if(log_file == NULL)
        return false;

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
