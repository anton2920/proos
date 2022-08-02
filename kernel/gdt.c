#include "gdt.h"


struct k_gdt_entry {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

struct k_gdt_descriptor {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct k_gdt_entry global_descriptor_table[3];
struct k_gdt_descriptor gdt_descriptor;


extern void _k_gdt_flush(void);


static void _k_gdt_init_entry(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    struct k_gdt_entry *entry;

    entry = &global_descriptor_table[num];

    /* Set up the descriptor base address */
    entry->base_low = (base & 0xFFFF);
    entry->base_middle = (base >> 16) & 0xFF;
    entry->base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    entry->limit_low = (limit & 0xFFFF);
    entry->granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    entry->granularity |= (gran & 0xF0);
    entry->access = access;
}


/* Should be called by main. This will set up the special GDT
 * pointer, set up the first 3 entries in our GDT, and then
 * finally call gdt_flush() in our assembler file in order
 * to tell the processor where the new GDT is and update the
 * new segment registers
 */
void k_gdt_init(void)
{
    /* Set up the GDT pointer and limit */
    gdt_descriptor.limit = (sizeof(struct k_gdt_entry) * 3) - 1;
    gdt_descriptor.base = (unsigned int) &global_descriptor_table;

    /* Our NULL descriptor */
    _k_gdt_init_entry(0, 0, 0, 0, 0);

    /* The second entry is our Code Segment. The base address
     * is 0, the limit is 4GBytes, it uses 4KByte granularity,
     * uses 32-bit opcodes, and is a Code Segment descriptor.
     */
    _k_gdt_init_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* The third entry is our Data Segment. It's EXACTLY the
     * same as our code segment, but the descriptor type in
     * this entry's access byte says it's a Data Segment
     */
    _k_gdt_init_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /* Flush out the old GDT and install the new changes! */
    _k_gdt_flush();
}
