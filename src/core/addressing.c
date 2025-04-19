#include "addressing.h"

// Modos de direccionamiento de memoria

// No indexados, no en memoria
void implicito(cpu_t *cpu, instruction_t *instruction) {
	instruction->operand = NULL;
}

void acumulador(cpu_t *cpu, instruction_t *instruction) {
    instruction->operand = &(cpu->accumulator);
}

void inmediato(cpu_t *cpu, instruction_t *instruction) {
    instruction->operand = &(cpu->memory[cpu->program_counter++]);
}

// No indexados, en memoria
void relativo(cpu_t *cpu, instruction_t *instruction) {
	instruction->operand = &(cpu->memory[cpu->program_counter++]);
}

void absoluto(cpu_t *cpu, instruction_t *instruction) {
    instruction->operand_address = cpu->memory[cpu->program_counter++];
    instruction->operand_address |= cpu->memory[cpu->program_counter++] << 8;
    instruction->operand = &(cpu->memory[instruction->operand_address]);
}

void pagina_cero(cpu_t *cpu, instruction_t *instruction) {
	instruction->operand_address = cpu->memory[cpu->program_counter++];
	instruction->operand = &(cpu->memory[instruction->operand_address]);
}

void indirecto(cpu_t *cpu, instruction_t *instruction) {
	instruction->operand_address = cpu->memory[cpu->program_counter++];
    instruction->operand_address |= cpu->memory[cpu->program_counter++] << 8;
    uint16_t aux = instruction->operand_address;
    instruction->operand_address = cpu->memory[aux++];
    instruction->operand_address |= cpu->memory[aux] << 8;
}

// Indexadas
void absoluto_x(cpu_t *cpu, instruction_t *instruction) {
	instruction->operand_address = cpu->memory[cpu->program_counter++];
	instruction->operand_address |= cpu->memory[cpu->program_counter++] << 8;
	instruction->operand_address += cpu->x_index_register;
	instruction->operand = &(cpu->memory[instruction->operand_address]);
}

void absoluto_y(cpu_t *cpu, instruction_t *instruction) {
	instruction->operand_address = cpu->memory[cpu->program_counter++];
	instruction->operand_address |= cpu->memory[cpu->program_counter++] << 8;
	instruction->operand_address += cpu->y_index_register;
	instruction->operand = &(cpu->memory[instruction->operand_address]);
}

void pagina_cero_x(cpu_t *cpu, instruction_t *instruction) {
	instruction->operand_address = cpu->memory[cpu->program_counter++];
	instruction->operand_address += cpu->x_index_register;
	instruction->operand_address &= 0xFF;
	instruction->operand = &(cpu->memory[instruction->operand_address]);
}

void pagina_cero_y(cpu_t *cpu, instruction_t *instruction) {
	instruction->operand_address = cpu->memory[cpu->program_counter++];
	instruction->operand_address += cpu->y_index_register;
	instruction->operand_address &= 0xFF;
	instruction->operand = &(cpu->memory[instruction->operand_address]);
}

void indirecto_x(cpu_t *cpu, instruction_t *instruction) {
	instruction->operand_address = cpu->memory[cpu->program_counter++];
	instruction->operand_address += cpu->x_index_register;
	instruction->operand_address &= 0xFF;
	uint16_t aux = instruction->operand_address;
    instruction->operand_address = cpu->memory[aux++];
    instruction->operand_address |= cpu->memory[aux] << 8;
    instruction->operand = &(cpu->memory[instruction->operand_address]);
}

void indirecto_y(cpu_t *cpu, instruction_t *instruction) {
	instruction->operand_address = cpu->memory[cpu->program_counter++];
    uint16_t aux = instruction->operand_address;
    instruction->operand_address = cpu->memory[aux++];
    instruction->operand_address |= cpu->memory[aux] << 8;
    instruction->operand_address += cpu->y_index_register;
    instruction->operand = &(cpu->memory[instruction->operand_address]);
}
