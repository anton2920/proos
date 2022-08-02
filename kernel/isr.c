#include "../libs/assert.h"
#include "../libs/stdlib.h"

#include "idt.h"
#include "isr.h"


/* These are function prototypes for all the exception
 * handlers: The first 32 entries in the IDT are reserved
 * by Intel, and are designed to service exceptions!
 */
extern void k_isr_0(void);
extern void k_isr_1(void);
extern void k_isr_2(void);
extern void k_isr_3(void);
extern void k_isr_4(void);
extern void k_isr_5(void);
extern void k_isr_6(void);
extern void k_isr_7(void);
extern void k_isr_8(void);
extern void k_isr_9(void);
extern void k_isr_10(void);
extern void k_isr_11(void);
extern void k_isr_12(void);
extern void k_isr_13(void);
extern void k_isr_14(void);
extern void k_isr_15(void);
extern void k_isr_16(void);
extern void k_isr_17(void);
extern void k_isr_18(void);
extern void k_isr_19(void);
extern void k_isr_20(void);
extern void k_isr_21(void);
extern void k_isr_22(void);
extern void k_isr_23(void);
extern void k_isr_24(void);
extern void k_isr_25(void);
extern void k_isr_26(void);
extern void k_isr_27(void);
extern void k_isr_28(void);
extern void k_isr_29(void);
extern void k_isr_30(void);
extern void k_isr_31(void);


static void (*isr_routines[])(void) =
{
    k_isr_0,  k_isr_1,  k_isr_2,  k_isr_3,  k_isr_4,  k_isr_5,  k_isr_6,  k_isr_7,
    k_isr_8,  k_isr_9,  k_isr_10, k_isr_11, k_isr_12, k_isr_13, k_isr_14, k_isr_15,
    k_isr_16, k_isr_17, k_isr_18, k_isr_19, k_isr_20, k_isr_21, k_isr_22, k_isr_23,
    k_isr_24, k_isr_25, k_isr_26, k_isr_27, k_isr_28, k_isr_29, k_isr_30, k_isr_31
};


/* We set the access flags to 0x8E. This means that the entry is present, is
 * running in ring 0 (kernel level), and has the lower 5 bits
 * set to the required '14', which is represented by 'E' in hex.
 */
void k_isr_exceptions_init(void)
{
    unsigned long i;

    for (i = 0; i < sizeof(isr_routines) / sizeof(isr_routines[0]); ++i) {
        k_idt_init_entry(i, (unsigned int) isr_routines[i], 0x08, 0x8E);
    }
}


/* This is a simple string array. It contains the message that
*  corresponds to each and every exception. We get the correct
*  message by accessing like:
*  exception_message[interrupt_number] */
static char *_k_isr_exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};


/* All of our Exception handling Interrupt Service Routines will
*  point to this function. This will tell us what exception has
*  happened! Right now, we simply halt the system by hitting an
*  endless loop. All ISRs disable interrupts while they are being
*  serviced as a 'locking' mechanism to prevent an IRQ from
*  happening and messing up kernel data structures */
#define k_screen_prints_on_red(str) (k_screen_prints_ex((str), VGA_TEXT_BG(VGA_RED) | VGA_WHITE))


void k_isr_exception_handler(k_isr_registers_t *regs)
{
    assert(regs->int_no < 32);
    k_screen_prints_on_red(_k_isr_exception_messages[regs->int_no]);
    k_screen_prints_on_red(" exception\r\n");
    abort();
}
