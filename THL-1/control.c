#include <string.h>
#include "control.h"
#include <stdlib.h>

/* Microcode layout pattern */
uint16_t ucode[NINSTR][NSTEPS] = {
        {CO|MI, RO|II|CE, 0,     0,     0},             /* NOP  - 0b0000 */
        {CO|MI, RO|II|CE, IO|MI, RO|AI, 0},             /* LDA  - 0b0001 */
        {CO|MI, RO|II|CE, IO|AI, 0,     0},             /* LDI  - 0b0010 */
        {CO|MI, RO|II|CE, IO|MI, AO|RI, 0},             /* STA  - 0b0011 */
        {CO|MI, RO|II|CE, IO|MI, RO|BI, EO|AI},         /* ADD  - 0b0100 */
        {CO|MI, RO|II|CE, IO|MI, RO|BI, EO|EC0|AI},     /* SUB  - 0b0101 */
        {CO|MI, RO|II|CE, IO|MI, RO|BI, EO|EC1|AI},     /* AND  - 0b0110 */
        {CO|MI, RO|II|CE, IO|MI, RO|BI, EO|EC1|EC0|AI}, /* OR   - 0b0111 */
        {CO|MI, RO|II|CE, IO|JP, 0,     0},             /* JMP  - 0b1000 */
        {CO|MI, RO|II|CE, 0,     0,     0},             /* JC   - 0b1001 */
        {CO|MI, RO|II|CE, 0,     0,     0},             /* JZ   - 0b1010 */
        {CO|MI, RO|II|CE, 0,     0,     0},             /* JS   - 0b1011 */
        {CO|MI, RO|II|CE, IO|MI, RO|BI, EO|EC0},        /* CMP  - 0b1100 */
        {CO|MI, RO|II|CE, IO|MI, RO|BI, EO|EC1},        /* TEST - 0b1101 */
        {CO|MI, RO|II|CE, AO|OI, 0,     0},             /* OUT  - 0b1110 */
        {CO|MI, RO|II|CE, HLT,   0,     0}              /* HALT - 0b1111 */
};

void microcode(cu_t *cu) {

    /* Main part */

    /* Copy pattern to every location */
    for (uint8_t flag = 0; flag < NFLAGS; ++flag) {
        memcpy(cu->data[flag], ucode, sizeof(ucode));
    }

    /* Set up jump instructions */
    cu->data[SLZLCH][JC][0b010] = IO|JP;

    cu->data[SLZHCL][JZ][0b010] = IO|JP;

    cu->data[SHZLCL][JS][0b010] = IO|JP;

    cu->data[SLZHCH][JC][0b010] = IO|JP;
    cu->data[SLZHCH][JZ][0b010] = IO|JP;

    cu->data[SHZLCH][JC][0b010] = IO|JP;
    cu->data[SHZLCH][JS][0b010] = IO|JP;

    cu->data[SHZHCL][JZ][0b010] = IO|JP;
    cu->data[SHZHCL][JS][0b010] = IO|JP;

    cu->data[SHZHCH][JC][0b010] = IO|JP;
    cu->data[SHZHCH][JZ][0b010] = IO|JP;
    cu->data[SHZHCH][JS][0b010] = IO|JP;
}