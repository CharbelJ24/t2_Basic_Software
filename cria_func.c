/* Davi Teixeira 2510420 3WA */
/* Charbel Janos 2510373 3WA */

#include <stdio.h>
#include "cria_func.h"

int mult(int x, int y) {
    return x * y;
}


void cria_func(void* f, DescParam params[], int n, unsigned char codigo[]) {
    int pos = 0;

    int offsets_salvos[] = {0xF8, 0xF0, 0xE8};

    unsigned char mov_imm32[] = {0xBF, 0xBE, 0xBA};

    unsigned char modrm_load[] = {0x7D, 0x75, 0x55};

    codigo[pos++] = 0x55;
    codigo[pos++] = 0x48; codigo[pos++] = 0x89;
    codigo[pos++] = 0xE5;
    codigo[pos++] = 0x48; codigo[pos++] = 0x83;
    codigo[pos++] = 0xEC; codigo[pos++] = 0x20;

    codigo[pos++] = 0x48; codigo[pos++] = 0x89;
    codigo[pos++] = 0x7D; codigo[pos++] = 0xF8;

    codigo[pos++] = 0x48; codigo[pos++] = 0x89;
    codigo[pos++] = 0x75; codigo[pos++] = 0xF0;

    codigo[pos++] = 0x48; codigo[pos++] = 0x89;
    codigo[pos++] = 0x55; codigo[pos++] = 0xE8;

    int param_count = 0;

    for (int i = 0; i < n; i++) {

        if (params[i].orig_val == FIX) {
            if (params[i].tipo_val == INT_PAR) {
                int val = params[i].valor.v_int;
                codigo[pos++] = mov_imm32[i];
                codigo[pos++] = (val)       & 0xFF;
                codigo[pos++] = (val >> 8)  & 0xFF;
                codigo[pos++] = (val >> 16) & 0xFF;
                codigo[pos++] = (val >> 24) & 0xFF;
            } else {
                unsigned long long ptr = (unsigned long long)params[i].valor.v_ptr;
                unsigned char opcodes_ptr[] = {0xBF, 0xBE, 0xBA};
                codigo[pos++] = 0x48;
                codigo[pos++] = opcodes_ptr[i];
                for (int b = 0; b < 8; b++)
                    codigo[pos++] = (ptr >> (8*b)) & 0xFF;
            }

        } else if (params[i].orig_val == IND) {
            unsigned long long ptr = (unsigned long long)params[i].valor.v_ptr;
            codigo[pos++] = 0x48; codigo[pos++] = 0xB8;
            for (int b = 0; b < 8; b++)
                codigo[pos++] = (ptr >> (8*b)) & 0xFF;

            if (params[i].tipo_val == INT_PAR) {
                unsigned char modrm_ind[] = {0x38, 0x30, 0x10};
                codigo[pos++] = 0x8B;
                codigo[pos++] = modrm_ind[i];
            } else {
                unsigned char modrm_ind64[] = {0x38, 0x30, 0x10};
                codigo[pos++] = 0x48; codigo[pos++] = 0x8B;
                codigo[pos++] = modrm_ind64[i];
            }

        } else {
            if (params[i].tipo_val == INT_PAR) {
                codigo[pos++] = 0x8B;
                codigo[pos++] = modrm_load[i];
                codigo[pos++] = offsets_salvos[param_count];
            } else {
                codigo[pos++] = 0x48; codigo[pos++] = 0x8B;
                codigo[pos++] = modrm_load[i];
                codigo[pos++] = offsets_salvos[param_count];
            }
            param_count++;
        }
    }

    unsigned long long faddr = (unsigned long long)f;
    codigo[pos++] = 0x48; codigo[pos++] = 0xB8;
    for (int b = 0; b < 8; b++)
        codigo[pos++] = (faddr >> (8*b)) & 0xFF;
    codigo[pos++] = 0xFF; codigo[pos++] = 0xD0;

    codigo[pos++] = 0xC9;
    codigo[pos++] = 0xC3;
}