#ifndef IDT_H
#define IDT_H

void k_idt_init_entry(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void k_idt_init(void);

#endif // IDT_H
