#ifndef THL_1_RAM_H
#define THL_1_RAM_H

/* Header inclusion */
#include <stdint.h>
#include <stdbool.h>

/* New data types */
enum RAM_CONSTS {
    RAM_SIZE = 1 << 4
};

typedef struct ram {
    uint8_t data[RAM_SIZE];
    bool RWB;
    bool OE;
} ram_t;

#endif
