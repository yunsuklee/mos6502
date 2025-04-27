#include "opcodes.h"

opcode_t opcodes_dictionary[] = {
    /* ADC - Add with Carry */
    [0x69] = {addressing_immediate, adc, 2},
    [0x65] = {addressing_zero_page, adc, 3},
    [0x75] = {addressing_zero_page_x, adc, 4},
    [0x6D] = {addressing_absolute, adc, 4},
    [0x7D] = {addressing_absolute_x, adc, 4},
    [0x79] = {addressing_absolute_y, adc, 4},
    [0x61] = {addressing_indirect_x, adc, 6},
    [0x71] = {addressing_indirect_y, adc, 5},

    /* AND - Logical AND */
    [0x29] = {addressing_immediate, and, 2},
    [0x25] = {addressing_zero_page, and, 3},
    [0x35] = {addressing_zero_page_x, and, 4},
    [0x2D] = {addressing_absolute, and, 4},
    [0x39] = {addressing_absolute_y, and, 4},
    [0x3D] = {addressing_absolute_x, and, 4},
    [0x21] = {addressing_indirect_x, and, 6},
    [0x31] = {addressing_indirect_y, and, 5},

    /* ASL - Arithmetic Shift Left */
    [0x0A] = {addressing_accumulator, asl, 2},
    [0x06] = {addressing_zero_page, asl, 5},
    [0x16] = {addressing_zero_page_x, asl, 6},
    [0x0E] = {addressing_absolute, asl, 6},
    [0x1E] = {addressing_absolute_x, asl, 7},

    /* Branch instructions */
    [0x90] = {addressing_relative, bcc, 2}, // Branch if Carry Clear
    [0xB0] = {addressing_relative, bcs, 2}, // Branch if Carry Set
    [0xF0] = {addressing_relative, beq, 2}, // Branch if Equal
    [0x30] = {addressing_relative, bmi, 2}, // Branch if Minus
    [0xD0] = {addressing_relative, bne, 2}, // Branch if Not Equal
    [0x10] = {addressing_relative, bpl, 2}, // Branch if Positive
    [0x50] = {addressing_relative, bvc, 2}, // Branch if  Overflow Clear
    [0x70] = {addressing_relative, bvs, 2}, // Branch if Overflow Set

    /* BIT - Bit Test */
    [0x24] = {addressing_zero_page, bit, 3},
    [0x2C] = {addressing_absolute, bit, 4},

    /* BRK - Force Interrupt */
    [0x00] = {addressing_implied, brk, 7},

    /* Flag Clear Instructions */
    [0x18] = {addressing_implied, clc, 2}, // CLC - Clear Carry Flag
    [0xD8] = {addressing_implied, cld, 2}, // CLD - Clear Decimal Mode
    [0x58] = {addressing_implied, cli, 2}, // CLI - Clear Interrupt Disable
    [0xB8] = {addressing_implied, clv, 2}, // CLV - Clear Overflow Flag

    /* CMP - Compare Accumulator */
    [0xC9] = {addressing_immediate, cmp, 2},
    [0xC5] = {addressing_zero_page, cmp, 3},
    [0xD5] = {addressing_zero_page_x, cmp, 4},
    [0xCD] = {addressing_absolute, cmp, 4},
    [0xDD] = {addressing_absolute_x, cmp, 4},
    [0xD9] = {addressing_absolute_y, cmp, 4},
    [0xC1] = {addressing_indirect_x, cmp, 6},
    [0xD1] = {addressing_indirect_y, cmp, 5},

    /* CPX - Compare X Register */
    [0xE0] = {addressing_immediate, cpx, 2},
    [0xE4] = {addressing_zero_page, cpx, 3},
    [0xEC] = {addressing_absolute, cpx, 4},

    /* CPY - Compare Y Register */
    [0xC0] = {addressing_immediate, cpy, 2},
    [0xC4] = {addressing_zero_page, cpy, 3},
    [0xCC] = {addressing_absolute, cpy, 4},

    /* DEC - Decrement Memory */
    [0xC6] = {addressing_zero_page, dec, 5},
    [0xD6] = {addressing_zero_page_x, dec, 6},
    [0xCE] = {addressing_absolute, dec, 6},
    [0xDE] = {addressing_absolute_x, dec, 7},

    /* DEX - Decrement X Register */
    [0xCA] = {addressing_implied, dex, 2},

    /* DEY - Decrement Y Register */
    [0x88] = {addressing_implied, dey, 2},

    /* EOR - Exclusive OR */
    [0x49] = {addressing_immediate, eor, 2},
    [0x45] = {addressing_zero_page, eor, 3},
    [0x55] = {addressing_zero_page_x, eor, 4},
    [0x4D] = {addressing_absolute, eor, 4},
    [0x5D] = {addressing_absolute_x, eor, 4},
    [0x59] = {addressing_absolute_y, eor, 4},
    [0x41] = {addressing_indirect_x, eor, 6},
    [0x51] = {addressing_indirect_y, eor, 5},

    /* INC - Increment Memory */
    [0xE6] = {addressing_zero_page, inc, 5},
    [0xF6] = {addressing_zero_page_x, inc, 6},
    [0xEE] = {addressing_absolute, inc, 6},
    [0xFE] = {addressing_absolute_x, inc, 7},

    /* INX - Increment X Register */
    [0xE8] = {addressing_implied, inx, 2},

    /* INY - Increment Y Register */
    [0xC8] = {addressing_implied, iny, 2},

    /* JMP - Jump */
    [0x4C] = {addressing_absolute, jmp, 3},
    [0x6C] = {addressing_indirect, jmp, 5},

    /* JSR - Jump to Subroutine */
    [0x20] = {addressing_absolute, jsr, 6},

    /* LDA - Load Accumulator */
    [0xA9] = {addressing_immediate, lda, 2},
    [0xA5] = {addressing_zero_page, lda, 3},
    [0xB5] = {addressing_zero_page_x, lda, 4},
    [0xAD] = {addressing_absolute, lda, 4},
    [0xBD] = {addressing_absolute_x, lda, 4},
    [0xB9] = {addressing_absolute_y, lda, 4},
    [0xA1] = {addressing_indirect_x, lda, 6},
    [0xB1] = {addressing_indirect_y, lda, 5},

    /* LDX - Load X Register */
    [0xA2] = {addressing_immediate, ldx, 2},
    [0xA6] = {addressing_zero_page, ldx, 3},
    [0xB6] = {addressing_zero_page_y, ldx, 4},
    [0xAE] = {addressing_absolute, ldx, 4},
    [0xBE] = {addressing_absolute_y, ldx, 4},

    /* LDY - Load Y Register */
    [0xA0] = {addressing_immediate, ldy, 2},
    [0xA4] = {addressing_zero_page, ldy, 3},
    [0xB4] = {addressing_zero_page_x, ldy, 4},
    [0xAC] = {addressing_absolute, ldy, 4},
    [0xBC] = {addressing_absolute_x, ldy, 4},

    /* LSR - Logical Shift Right */
    [0x4A] = {addressing_accumulator, lsr, 2},
    [0x46] = {addressing_zero_page, lsr, 5},
    [0x56] = {addressing_zero_page_x, lsr, 6},
    [0x4E] = {addressing_absolute, lsr, 6},
    [0x5E] = {addressing_absolute_x, lsr, 7},

    /* NOP - No Operation */
    [0xEA] = {addressing_implied, nop, 2},

    /* ORA - Logical Inclusive OR */
    [0x09] = {addressing_immediate, ora, 2},
    [0x05] = {addressing_zero_page, ora, 3},
    [0x15] = {addressing_zero_page_x, ora, 4},
    [0x0D] = {addressing_absolute, ora, 4},
    [0x1D] = {addressing_absolute_x, ora, 4},
    [0x19] = {addressing_absolute_y, ora, 4},
    [0x01] = {addressing_indirect_x, ora, 6},
    [0x11] = {addressing_indirect_y, ora, 5},

    /* Stack Instructions */
    [0x48] = {addressing_implied, pha, 3}, // PHA - Push Accumulator
    [0x08] = {addressing_implied, php, 3}, // PHP - Push Processor Status
    [0x68] = {addressing_implied, pla, 4}, // PLA - Pull Accumulator
    [0x28] = {addressing_implied, plp, 4}, // PLP - Pull Processor Status

    /* ROL - Rotate Left */
    [0x2A] = {addressing_accumulator, rol, 2},
    [0x26] = {addressing_zero_page, rol, 5},
    [0x36] = {addressing_zero_page_x, rol, 6},
    [0x2E] = {addressing_absolute, rol, 6},
    [0x3E] = {addressing_absolute_x, rol, 7},

    /* ROR - Rotate Right */
    [0x6A] = {addressing_accumulator, ror, 2},
    [0x66] = {addressing_zero_page, ror, 5},
    [0x76] = {addressing_zero_page_x, ror, 6},
    [0x6E] = {addressing_absolute, ror, 6},
    [0x7E] = {addressing_absolute_x, ror, 7},

    /* RTI - Return from Interrupt */
    [0x40] = {addressing_implied, rti, 6},

    /* RTS - Return from Subroutine*/
    [0x60] = {addressing_implied, rts, 6},

    /* SBC - Subtract with Carry */
    [0xE9] = {addressing_immediate, sbc, 2},
    [0xE5] = {addressing_zero_page, sbc, 3},
    [0xF5] = {addressing_zero_page_x, sbc, 4},
    [0xED] = {addressing_absolute, sbc, 4},
    [0xFD] = {addressing_absolute_x, sbc, 4},
    [0xF9] = {addressing_absolute_y, sbc, 4},
    [0xE1] = {addressing_indirect_x, sbc, 6},
    [0xF1] = {addressing_indirect_y, sbc, 5},

    /* Flag Set Instructions */
    [0x38] = {addressing_implied, sec, 2}, // SEC - Set Carry Flag
    [0xF8] = {addressing_implied, sed, 2}, // SED - Set Decimal Flag
    [0x78] = {addressing_implied, sei, 2}, // SEI - Set Interrupt Disable

    /* STA - Store Accumulator */
    [0x85] = {addressing_zero_page, sta, 3},
    [0x95] = {addressing_zero_page_x, sta, 4},
    [0x8D] = {addressing_absolute, sta, 4},
    [0x9D] = {addressing_absolute_x, sta, 5},
    [0x99] = {addressing_absolute_y, sta, 5},
    [0x81] = {addressing_indirect_x, sta, 6},
    [0x91] = {addressing_indirect_y, sta, 6},

    /* STX - Store X Register */
    [0x86] = {addressing_zero_page, stx, 3},
    [0x96] = {addressing_zero_page_y, stx, 4},
    [0x8E] = {addressing_absolute, stx, 4},

    /* STY - Store Y Register */
    [0x84] = {addressing_zero_page, sty, 3},
    [0x94] = {addressing_zero_page_x, sty, 4},
    [0x8C] = {addressing_absolute, sty, 4},

    /* Register Transfer Instructions */
    [0xAA] = {addressing_implied, tax, 2}, // TAX - Transfer A to X
    [0xA8] = {addressing_implied, tay, 2}, // TAY - Transfer A to Y
    [0xBA] = {addressing_implied, tsx, 2}, // TSX - Transfer S to X
    [0x8A] = {addressing_implied, txa, 2}, // TXA - Transfer X to A
    [0x9A] = {addressing_implied, txs, 2}, // TXS - Transfer X to S
    [0x98] = {addressing_implied, tya, 2}  // TYA - Transfer Y to A
};
