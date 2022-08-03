#include "../libs/stdio.h"

#include "idt.h"
#include "isr.h"
#include "irq.h"


#ifndef NULL
#define NULL (void *) 0
#endif

#define PIC1_ADDRESS 0x20
#define PIC1_CMD     PIC1_ADDRESS
#define PIC1_DATA    0x21

#define PIC2_ADDRESS 0xA0
#define PIC2_CMD     PIC2_ADDRESS
#define PIC2_DATA    0xA1

#define PIC_EOI 0x20 /* End-of-interrupt */

#define IRQ_BASE 32


enum icw1_cmds {
    ICW1_ICW4       = 1 << 0,    /* ICW4 (not) needed */
    ICW1_SINGLE     = 1 << 1,    /* Single (cascade) mode */
    ICW1_INTERVAL4  = 1 << 2,    /* Call address interval 4 (8) */
    ICW1_LEVEL      = 1 << 3,    /* Level triggered (edge) mode */
    ICW1_INIT       = 1 << 4     /* Initialization - required! */
};


enum icw4_cmds {
    ICW4_8086       = 0x01,     /* 8086/88 (MCS-80/85) mode */
    ICW4_AUTO       = 0x02,     /* Auto (normal) EOI */
    ICW4_BUF_SLAVE  = 0x08,     /* Buffered mode/slave */
    ICW4_BUF_MASTER = 0x0C,     /* Buffered mode/master */
    ICW4_SFNM       = 0x10      /* Special fully nested (not) */
};


/* These are own ISRs that point to our special IRQ handler
 * instead of the regular 'k_isr_exception_handler' function
 */
extern void k_irq_0(void);
extern void k_irq_1(void);
extern void k_irq_2(void);
extern void k_irq_3(void);
extern void k_irq_4(void);
extern void k_irq_5(void);
extern void k_irq_6(void);
extern void k_irq_7(void);
extern void k_irq_8(void);
extern void k_irq_9(void);
extern void k_irq_10(void);
extern void k_irq_11(void);
extern void k_irq_12(void);
extern void k_irq_13(void);
extern void k_irq_14(void);
extern void k_irq_15(void);


static void (*irq_handers[]) =
{
    k_irq_0, k_irq_1, k_irq_2,  k_irq_3,  k_irq_4,  k_irq_5,  k_irq_6,  k_irq_7,
    k_irq_8, k_irq_9, k_irq_10, k_irq_11, k_irq_12, k_irq_13, k_irq_14, k_irq_15
};


/* This array is actually an array of function pointers. We use
 * this to handle custom IRQ handlers for a given IRQ
 */
static k_irq_handler_cb_t irq_handlers_cbs[] =
{
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};


/* This installs a custom IRQ handler for the given IRQ */
void k_irq_install_handler_cb(int irq, k_irq_handler_cb_t cb)
{
    irq_handlers_cbs[irq] = cb;
}


/* This clears the handler for a given IRQ */
void k_irq_uninstall_handler_cb(int irq)
{
    irq_handlers_cbs[irq] = NULL;
}


/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15.
 * This is a problem in protected mode, because IDT entry 8 is a Double Fault!
 * Without remapping, every time IRQ0 fires, you get a Double Fault Exception, which is NOT actually
 * what's happening. We send commands to the Programmable Interrupt Controller (PICs - also called the 8259's) in
 * order to make IRQ0 to 15 be remapped to IDT entries 32 to 47
 */
static void _k_irq_remap(void)
{
    unsigned char mask1, mask2;

    mask1 = inb(PIC1_DATA);
    mask2 = inb(PIC2_DATA);

    /* Start initialization in sequence (cascade mode) */
    outb(PIC1_CMD, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_CMD, ICW1_INIT | ICW1_ICW4);

    /* Offsets in IDT for master and slave PICs */
    outb(PIC1_DATA, IRQ_BASE);
    outb(PIC2_DATA, IRQ_BASE + 8);

    /* Telling master about slave and assigning identity to slave.
     * TODO: replace magic numbers with something more reasonable. */
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);

    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    /* Restore saved masks */
    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);
}


/* We first remap the interrupt controllers, and then we install
 * the appropriate ISRs to the correct entries in the IDT. This
 * is just like installing the exception handlers
 */
void k_irq_init(void)
{
    unsigned int i;

    _k_irq_remap();

    for (i = 0; i < sizeof(irq_handers) / sizeof(irq_handers[0]); ++i) {
        k_idt_init_entry(i + IRQ_BASE, (unsigned int) irq_handers[i], 0x08, 0x8E);
    }
}


void k_irq_handler(k_irq_registers_t *regs)
{
    /* This is a blank function pointer */
    k_irq_handler_cb_t cb;

    /* Find out if we have a custom handler to run for this
     * IRQ, and then finally, run it
     */
    cb = irq_handlers_cbs[regs->int_no - IRQ_BASE];
    if (cb != NULL) {
        cb(regs);
    }

    /* If the IDT entry that was invoked was greater than 40
     * (meaning IRQ8 - 15), then we need to send an EOI to
     * the slave controller
     */
    if (regs->int_no >= 40) {
        outb(PIC2_CMD, PIC_EOI);
    }

    /* In either case, we need to send an EOI to the master
     * interrupt controller too
     */
    outb(PIC1_CMD, PIC_EOI);
}
