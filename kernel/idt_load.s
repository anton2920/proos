.globl _k_idt_load
.type _k_idt_load, @function
_k_idt_load:
	lidt idt_descriptor
	retl
