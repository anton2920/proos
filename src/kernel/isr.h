#ifndef ISRS_H
#define ISRS_H


/* This defines what the stack looks like after an ISR was running */
typedef struct k_isr_registers {
    unsigned int gs, fs, es, ds;                            /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;    /* pushed by 'pusha' */
    unsigned int int_no, err_code;                          /* our 'push byte #' and err_codes do this */
    unsigned int eip, cs, eflags, useresp, ss;              /* pushed by the processor automatically */
} k_isr_registers_t;


void k_isr_exceptions_init(void);

#endif // ISRS_H
