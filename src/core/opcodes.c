#include "opcodes.h"

dicc_t diccionario[] = {
    [0x69] = {inmediato, adc, 2},
    [0x65] = {pagina_cero, adc, 3},
    [0x75] = {pagina_cero_x, adc, 4},
    [0x6D] = {absoluto, adc, 4},
    [0x7D] = {absoluto_x, adc, 4},
    [0x79] = {absoluto_y, adc, 4},
    [0x61] = {indirecto_x, adc, 6},
    [0x71] = {indirecto_y, adc, 5},

    [0x29] = {inmediato, and, 2},
    [0x25] = {pagina_cero, and, 3},
    [0x35] = {pagina_cero_x, and, 4},
    [0x2D] = {absoluto, and, 4},
    [0x39] = {absoluto_y, and, 4},
    [0x3D] = {absoluto_x, and, 4},
    [0x21] = {indirecto_x, and, 6},
    [0x31] = {indirecto_y, and, 5},

    [0x0A] = {acumulador, asl, 2},
    [0x06] = {pagina_cero, asl, 5},
    [0x16] = {pagina_cero_x, asl, 6},
    [0x0E] = {absoluto, asl, 6},
    [0x1E] = {absoluto_x, asl, 7},

    [0x90] = {relativo, bcc, 2},

    [0xB0] = {relativo, bcs, 2},

    [0xF0] = {relativo, beq, 2},

    [0x24] = {pagina_cero, bit, 3},
    [0x2C] = {absoluto, bit, 4},

    [0x30] = {relativo, bmi, 2},

    [0xD0] = {relativo, bne, 2},

    [0x10] = {relativo, bpl, 2},

    [0x00] = {implicito, brk, 7},

    [0x50] = {relativo, bvc, 2},

    [0x70] = {relativo, bvs, 2},

    [0x18] = {implicito, clc, 2},

    [0xD8] = {implicito, cld, 2},

    [0x58] = {implicito, cli, 2},

    [0xB8] = {implicito, clv, 2},

    [0xC9] = {inmediato, cmp, 2},
    [0xC5] = {pagina_cero, cmp, 3},
    [0xD5] = {pagina_cero_x, cmp, 4},
    [0xCD] = {absoluto, cmp, 4},
    [0xDD] = {absoluto_x, cmp, 4},
    [0xD9] = {absoluto_y, cmp, 4},
    [0xC1] = {indirecto_x, cmp, 6},
    [0xD1] = {indirecto_y, cmp, 5},

    [0xE0] = {inmediato, cpx, 2},
    [0xE4] = {pagina_cero, cpx, 3},
    [0xEC] = {absoluto, cpx, 4},

    [0xC0] = {inmediato, cpy, 2},
    [0xC4] = {pagina_cero, cpy, 3},
    [0xCC] = {absoluto, cpy, 4},

    [0xC6] = {pagina_cero, dec, 5},
    [0xD6] = {pagina_cero_x, dec, 6},
    [0xCE] = {absoluto, dec, 6},
    [0xDE] = {absoluto_x, dec, 7},

    [0xCA] = {implicito, dex, 2},

    [0x88] = {implicito, dey, 2},

    [0x49] = {inmediato, eor, 2},
    [0x45] = {pagina_cero, eor, 3},
    [0x55] = {pagina_cero_x, eor, 4},
    [0x4D] = {absoluto, eor, 4},
    [0x5D] = {absoluto_x, eor, 4},
    [0x59] = {absoluto_y, eor, 4},
    [0x41] = {indirecto_x, eor, 6},
    [0x51] = {indirecto_y, eor, 5},

    [0xE6] = {pagina_cero, inc, 5},
    [0xF6] = {pagina_cero_x, inc, 6},
    [0xEE] = {absoluto, inc, 6},
    [0xFE] = {absoluto_x, inc, 7},

    [0xE8] = {implicito, inx, 2},

    [0xC8] = {implicito, iny, 2},

    [0x4C] = {absoluto, jmp, 3},
    [0x6C] = {indirecto, jmp, 5},

    [0x20] = {absoluto, jsr, 6},

    [0xA9] = {inmediato, lda, 2},
    [0xA5] = {pagina_cero, lda, 3},
    [0xB5] = {pagina_cero_x, lda, 4},
    [0xAD] = {absoluto, lda, 4},
    [0xBD] = {absoluto_x, lda, 4},
    [0xB9] = {absoluto_y, lda, 4},
    [0xA1] = {indirecto_x, lda, 6},
    [0xB1] = {indirecto_y, lda, 5},

    [0xA2] = {inmediato, ldx, 2},
    [0xA6] = {pagina_cero, ldx, 3},
    [0xB6] = {pagina_cero_y, ldx, 4},
    [0xAE] = {absoluto, ldx, 4},
    [0xBE] = {absoluto_y, ldx, 4},

    [0xA0] = {inmediato, ldy, 2},
    [0xA4] = {pagina_cero, ldy, 3},
    [0xB4] = {pagina_cero_x, ldy, 4},
    [0xAC] = {absoluto, ldy, 4},
    [0xBC] = {absoluto_x, ldy, 4},

    [0x4A] = {acumulador, lsr, 2},
    [0x46] = {pagina_cero, lsr, 5},
    [0x56] = {pagina_cero_x, lsr, 6},
    [0x4E] = {absoluto, lsr, 6},
    [0x5E] = {absoluto_x, lsr, 7},

    [0xEA] = {implicito, nop, 2},

    [0x09] = {inmediato, ora, 2},
    [0x05] = {pagina_cero, ora, 3},
    [0x15] = {pagina_cero_x, ora, 4},
    [0x0D] = {absoluto, ora, 4},
    [0x1D] = {absoluto_x, ora, 4},
    [0x19] = {absoluto_y, ora, 4},
    [0x01] = {indirecto_x, ora, 6},
    [0x11] = {indirecto_y, ora, 5},

    [0x48] = {implicito, pha, 3},

    [0x08] = {implicito, php, 3},

    [0x68] = {implicito, pla, 4},

    [0x28] = {implicito, plp, 4},

    [0x2A] = {acumulador, rol, 2},
    [0x26] = {pagina_cero, rol, 5},
    [0x36] = {pagina_cero_x, rol, 6},
    [0x2E] = {absoluto, rol, 6},
    [0x3E] = {absoluto_x, rol, 7},

    [0x6A] = {acumulador, ror, 2},
    [0x66] = {pagina_cero, ror, 5},
    [0x76] = {pagina_cero_x, ror, 6},
    [0x6E] = {absoluto, ror, 6},
    [0x7E] = {absoluto_x, ror, 7},

    [0x40] = {implicito, rti, 6},

    [0x60] = {implicito, rts, 6},

    [0xE9] = {inmediato, sbc, 2},
    [0xE5] = {pagina_cero, sbc, 3},
    [0xF5] = {pagina_cero_x, sbc, 4},
    [0xED] = {absoluto, sbc, 4},
    [0xFD] = {absoluto_x, sbc, 4},
    [0xF9] = {absoluto_y, sbc, 4},
    [0xE1] = {indirecto_x, sbc, 6},
    [0xF1] = {indirecto_y, sbc, 5},

    [0x38] = {implicito, sec, 2},

    [0xF8] = {implicito, sed, 2},

    [0x78] = {implicito, sei, 2},

    [0x85] = {pagina_cero, sta, 3},
    [0x95] = {pagina_cero_x, sta, 4},
    [0x8D] = {absoluto, sta, 4},
    [0x9D] = {absoluto_x, sta, 5},
    [0x99] = {absoluto_y, sta, 5},
    [0x81] = {indirecto_x, sta, 6},
    [0x91] = {indirecto_y, sta, 6},

    [0x86] = {pagina_cero, stx, 3},
    [0x96] = {pagina_cero_y, stx, 4},
    [0x8E] = {absoluto, stx, 4},

    [0x84] = {pagina_cero, sty, 3},
    [0x94] = {pagina_cero_x, sty, 4},
    [0x8C] = {absoluto, sty, 4},

    [0xAA] = {implicito, tax, 2},

    [0xA8] = {implicito, tay, 2},

    [0xBA] = {implicito, tsx, 2},

    [0x8A] = {implicito, txa, 2},

    [0x9A] = {implicito, txs, 2},

    [0x98] = {implicito, tya, 2}
};
