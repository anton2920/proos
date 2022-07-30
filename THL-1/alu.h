#ifndef THL_1_ALU_H
#define THL_1_ALU_H

/* Header inclusion */
#include <stdint.h>
#include "register.h"

/* New data types */
enum ALU_CTRL {
    ALU_ADD = 0b00,
    ALU_SUB = 0b01,
    ALU_AND = 0b10,
    ALU_OR  = 0b11,
    ALU_CONTROL_SIZE = 0x02
};

typedef struct ALU {
    bool ctrl[ALU_CONTROL_SIZE];
    reg_t *a, *b;
    bool OE;
} alu_t;

uint8_t perform_alu(alu_t *alu, reg_t *flags);

#endif
