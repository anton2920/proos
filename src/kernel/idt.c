#include "../libs/stdlib.h"


struct k_idt_entry {
    unsigned short base_lo;
    unsigned short sel;    /* Our kernel segment goes here! */
    unsigned char always0; /* This will ALWAYS be set to 0! */
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct k_idt_descriptor {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));


/* Declare an IDT of 256 entries.
 * If any undefined IDT entry is hit, it normally
 * will cause an "Unhandled Interrupt" exception. Any descriptor
 * for which the 'presence' bit is cleared (0) will generate an
 * "Unhandled Interrupt" exception
 */
struct k_idt_entry interrupt_descriptor_table[256];
struct k_idt_descriptor idt_descriptor;


extern void _k_idt_load(void);


void k_idt_init_entry(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    struct k_idt_entry *entry;

    entry = &interrupt_descriptor_table[num];

    /* The interrupt routine's base address */
    entry->base_lo = (base & 0xFFFF);
    entry->base_hi = (base >> 16) & 0xFFFF;

    /* The segment or 'selector' that this IDT entry will use
     * is set here, along with any access flags.
     */
    entry->sel = sel;
    entry->always0 = 0;
    entry->flags = flags;
}


void k_idt_init(void)
{
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    idt_descriptor.limit = (sizeof(struct k_idt_entry) * 256) - 1;
    idt_descriptor.base = (unsigned int) &interrupt_descriptor_table;

    /* Clear out the entire IDT, initializing it to zeros */
    memset(&interrupt_descriptor_table, 0, sizeof(struct k_idt_entry) * 256);

    /* Points the processor's internal register to the new IDT */
    _k_idt_load();
}
