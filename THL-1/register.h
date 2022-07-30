#ifndef THL_1_REGISTER_H
#define THL_1_REGISTER_H

/* Header inclusion */
#include <stdint.h>
#include <stdbool.h>

/* New data types */
typedef struct reg {
    uint8_t data;
    bool RWB;
    bool OE;
} reg_t;

#endif
