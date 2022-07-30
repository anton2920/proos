#ifndef THL_1_CONTROL_H
#define THL_1_CONTROL_H

/* Header inclusion */
#include <stdint.h>
#include <stdbool.h>

/* New data types */
enum CU_CONSTS {
    NSTEPS   = 0x5,
    NINSTR   = 1 << 4,
    NFLAGS   = 0x8,
    NSIGNALS = 0x10
};

enum CONTROL_SIGNALS {
    HLT  = 0b1000000000000000,
    MI   = 0b0100000000000000,
    RI   = 0b0010000000000000,
    RO   = 0b0001000000000000,
    II   = 0b0000100000000000,
    IO   = 0b0000010000000000,
    OI   = 0b0000001000000000,
    EO   = 0b0000000100000000,
    EC1  = 0b0000000010000000,
    EC0  = 0b0000000001000000,
    BI   = 0b0000000000100000,
    AI   = 0b0000000000010000,
    AO   = 0b0000000000001000,
    CE   = 0b0000000000000100,
    CO   = 0b0000000000000010,
    JP   = 0b0000000000000001,
};

enum ISA {
    NOP  = 0b0000, /* No operation */
    LDA  = 0b0001, /* Loads value from memory location to A-reg */
    LDI  = 0b0010, /* Loads immediate value to A-reg */
    STA  = 0b0011, /* Stores value from A-reg to memory location */
    ADD  = 0b0100, /* Adds value from memory location to value in A-reg */
    SUB  = 0b0101, /* Subtracts value from memory location from value in A-reg */
    AND  = 0b0110, /* Bitwise ands value from memory location with value in A-reg */
    OR   = 0b0111, /* Bitwise ors value from memory location with value in A-reg */
    JMP  = 0b1000, /* Jumps to a memory location */
    JC   = 0b1001, /* Jumps to a memory location only if carry flag is set */
    JZ   = 0b1010, /* Jumps to a memory location only if zero flag is set */
    JS   = 0b1011, /* Jumps to a memory location only if sign flag is set */
    CMP  = 0b1100, /* Compares two values by subtraction and sets flags accordingly */
    TEST = 0b1101, /* Compares two values by bitwise-and and sets flags accordingly */
    OUT  = 0b1110, /* Outputs contents of A-reg */
    HALT = 0b1111  /* Halts computer */
};

enum FLAGS {
    CF, /* Indicates if result generates carry or borrow */
    ZF, /* Indicates if result is equal to zero */
    SF, /* Indicates if sign bit in result is set */
};

enum FLAGS_SET {
    SLZLCL, /* CF = 0, ZF = 0, SF = 0 */
    SLZLCH, /* CF = 1, ZF = 0, SF = 0 */
    SLZHCL, /* CF = 0, ZF = 1, SF = 0 */
    SLZHCH, /* CF = 1, ZF = 1, SF = 0 */
    SHZLCL, /* CF = 0, ZF = 0, SF = 1 */
    SHZLCH, /* CF = 1, ZF = 0, SF = 1 */
    SHZHCL, /* CF = 0, ZF = 1, SF = 1 */
    SHZHCH  /* CF = 1, ZF = 1, SF = 1 */
};

typedef struct cu {
    uint16_t data[NFLAGS][NINSTR][NSTEPS];
    uint8_t counter;
} cu_t;

void microcode(cu_t *);

#endif
