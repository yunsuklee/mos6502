#include "addressing.h"

void addressing_implied(cpu_t *cpu, instruction_t *instruction) {
	instruction->operand = NULL;
}

void addressing_accumulator(cpu_t *cpu, instruction_t *instruction) {
	instruction->operand = &(cpu->accumulator);
}

void addressing_immediate(cpu_t *cpu, instruction_t *instruction) {
	instruction->operand = &(cpu->memory[cpu->program_counter++]);
}

void addressing_relative(cpu_t *cpu, instruction_t *instruction) {
	instruction->operand = &(cpu->memory[cpu->program_counter++]);
}

void addressing_absolute(cpu_t *cpu, instruction_t *instruction) {
	uint8_t low_byte = cpu->memory[cpu->program_counter++];
	uint8_t high_byte = cpu->memory[cpu->program_counter++];

	instruction->operand_address = low_byte | (high_byte << BIT_SHIFT_BYTE);
	instruction->operand = &(cpu->memory[instruction->operand_address]);
}

void addressing_zero_page(cpu_t *cpu, instruction_t *instruction) {
	instruction->operand_address = cpu->memory[cpu->program_counter++];
	instruction->operand = &(cpu->memory[instruction->operand_address]);
}

void addressing_indirect(cpu_t *cpu, instruction_t *instruction) {
	uint8_t low_byte = cpu->memory[cpu->program_counter++];
	uint8_t high_byte = cpu->memory[cpu->program_counter++];

	uint16_t pointer_address = low_byte | (high_byte << BIT_SHIFT_BYTE);

	uint8_t target_low_byte = cpu->memory[pointer_address];
	uint8_t target_high_byte;

	if ((pointer_address & BYTE_MASK) == BYTE_MASK) {
		// 6502 JMP indirect bug: when pointer is at page boundary
		// high byte is fetched from start of same page, not next page
		target_high_byte = cpu->memory[pointer_address & HIGH_BYTE_MASK];
	} else {
		target_high_byte = cpu->memory[pointer_address + 1];
	}

	instruction->operand_address = target_low_byte | (target_high_byte << BIT_SHIFT_BYTE);
	instruction->operand = &(cpu->memory[instruction->operand_address]);
}

void addressing_absolute_x(cpu_t *cpu, instruction_t *instruction) {
	uint8_t low_byte = cpu->memory[cpu->program_counter++];
	uint8_t high_byte = cpu->memory[cpu->program_counter++];

	uint16_t base_address = low_byte | (high_byte << BIT_SHIFT_BYTE);

	instruction->operand_address = base_address + cpu->x_index_register;

	// Detect page boundary crossing for cycle counting
	uint16_t base_page = base_address & HIGH_BYTE_MASK;
	uint16_t final_page = instruction->operand_address & HIGH_BYTE_MASK;
	instruction->page_boundary_crossed = (base_page != final_page);

	instruction->operand = &(cpu->memory[instruction->operand_address]);
}

void addressing_absolute_y(cpu_t *cpu, instruction_t *instruction) {
	uint8_t low_byte = cpu->memory[cpu->program_counter++];
	uint8_t high_byte = cpu->memory[cpu->program_counter++];

	uint16_t base_address = low_byte | (high_byte << BIT_SHIFT_BYTE);

	instruction->operand_address = base_address + cpu->y_index_register;

	// Detect page boundary crossing for cycle counting
	uint16_t base_page = base_address & HIGH_BYTE_MASK;
	uint16_t final_page = instruction->operand_address & HIGH_BYTE_MASK;
	instruction->page_boundary_crossed = (base_page != final_page);

	instruction->operand = &(cpu->memory[instruction->operand_address]);
}

void addressing_zero_page_x(cpu_t *cpu, instruction_t *instruction) {
	uint8_t zero_page_address = cpu->memory[cpu->program_counter++];

	// Zero page addresses wrap around within the zero page
	instruction->operand_address = (zero_page_address + cpu->x_index_register) & ZERO_PAGE_MASK;
	instruction->operand = &(cpu->memory[instruction->operand_address]);
}

void addressing_zero_page_y(cpu_t *cpu, instruction_t *instruction) {
	uint8_t zero_page_address = cpu->memory[cpu->program_counter++];

	// Zero page addresses wrap around within the zero page
	instruction->operand_address = (zero_page_address + cpu->y_index_register) & ZERO_PAGE_MASK;
	instruction->operand = &(cpu->memory[instruction->operand_address]);
}

void addressing_indirect_x(cpu_t *cpu, instruction_t *instruction) {
	uint8_t zero_page_pointer = cpu->memory[cpu->program_counter++];

	// Calculate effective zero page address with X offset (wraps in zero page)
	uint8_t effective_address = (zero_page_pointer + cpu->x_index_register) & ZERO_PAGE_MASK;

	// Get target address from zero page (little-endian)
	uint8_t target_low_byte = cpu->memory[effective_address];
	uint8_t target_high_byte = cpu->memory[(effective_address + 1) & ZERO_PAGE_MASK];

	instruction->operand_address = target_low_byte | (target_high_byte << BIT_SHIFT_BYTE);
	instruction->operand = &(cpu->memory[instruction->operand_address]);
}

void addressing_indirect_y(cpu_t *cpu, instruction_t *instruction) {
	uint8_t zero_page_pointer = cpu->memory[cpu->program_counter++];

	// Get base address from zero page (little-endian)
	uint8_t base_low_byte = cpu->memory[zero_page_pointer];
	uint8_t base_high_byte = cpu->memory[(zero_page_pointer + 1) & ZERO_PAGE_MASK];

	uint16_t base_address = base_low_byte | (base_high_byte << BIT_SHIFT_BYTE);

	// Add Y offset to the indirectly obtained address
	instruction->operand_address = base_address + cpu->y_index_register;

	// Detect page boundary crossing for cycle counting
	uint16_t base_page = base_address & HIGH_BYTE_MASK;
	uint16_t final_page = instruction->operand_address & HIGH_BYTE_MASK;
	instruction->page_boundary_crossed = (base_page != final_page);

	instruction->operand = &(cpu->memory[instruction->operand_address]);
}