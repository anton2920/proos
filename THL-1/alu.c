#include "alu.h"

uint8_t perform_alu(alu_t *alu, reg_t *flags) {

    /* Initializing variables */
    uint16_t tmp = 0;
    uint8_t res = 0;

    /* Main part */
    switch (alu->ctrl[1] << 1 | alu->ctrl[0]) {
        case ALU_ADD:
            tmp = alu->a->data + alu->b->data;
            res = tmp & 0xFF;
            flags->data |= ((tmp & (1 << 8)) >> 8);
            flags->data |= ((tmp == 0) << 1);
            flags->data |= ((tmp < 0) << 2);
            break;
        case ALU_SUB:
            tmp = alu->a->data + (~alu->b->data + 1);
            res = tmp & 0xFF;
            flags->data |= ((tmp & (1 << 8)) >> 8);
            flags->data |= ((tmp == 0) << 1);
            flags->data |= ((tmp < 0) << 2);
            break;
        case ALU_AND:
            res = alu->a->data & alu->b->data;
            flags->data |= ((tmp & (1 << 8)) >> 8);
            flags->data |= ((tmp == 0) << 1);
            flags->data |= ((tmp < 0) << 2);
            break;
        case ALU_OR:
            res = alu->a->data | alu->b->data;
            flags->data |= ((tmp & (1 << 8)) >> 8);
            flags->data |= ((tmp == 0) << 1);
            flags->data |= ((tmp < 0) << 2);
            break;
        default:
            break;
    }

    /* Returning value */
    return res;
}