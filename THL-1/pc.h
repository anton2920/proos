#ifndef THL_1_PC_H
#define THL_1_PC_H

/* Header inclusion */
#include <stdbool.h>
#include <stdint.h>

/* New data types */
typedef struct pc {
    uint8_t data;
    bool CE;
    bool CO;
    bool J;
} pc_t;

#endif
