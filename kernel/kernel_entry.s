.code32

.globl _start
.type _start, @function
_start:
.ifndef TEST
	calll k_main
.else
	calll k_test
.endif
_end:
	hlt
	jmp _end


.globl _k_gdt_flush
.type _k_gdt_flush, @function
.equ code_offset, 0x8 # second entry
.equ data_offset, 0x10 # third entry
_k_gdt_flush:
	lgdt gdt_descriptor
	movw $data_offset, %ax
	movw %ax, %ds
	movw %ax, %ss
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs

	jmp $code_offset, $_k_gdt_flush_flush

_k_gdt_flush_flush:
	retl


.globl _k_idt_load
.type _k_idt_load, @function
_k_idt_load:
	lidt idt_descriptor
	retl
