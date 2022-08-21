# 32: IRQ0
.globl k_irq_0
k_irq_0:
	cli
	pushl $0x0
	pushl $32
	jmp _k_irq_common_stub


# 33: IRQ1
.globl k_irq_1
k_irq_1:
	cli
	pushl $0x0
	pushl $33
	jmp _k_irq_common_stub


# 34: IRQ2
.globl k_irq_2
k_irq_2:
	cli
	pushl $0x0
	pushl $34
	jmp _k_irq_common_stub


# 35: IRQ3
.globl k_irq_3
k_irq_3:
	cli
	pushl $0x0
	pushl $35
	jmp _k_irq_common_stub


# 36: IRQ4
.globl k_irq_4
k_irq_4:
	cli
	pushl $0x0
	pushl $36
	jmp _k_irq_common_stub


# 37: IRQ5
.globl k_irq_5
k_irq_5:
	cli
	pushl $0x0
	pushl $37
	jmp _k_irq_common_stub


# 38: IRQ6
.globl k_irq_6
k_irq_6:
	cli
	pushl $0x0
	pushl $38
	jmp _k_irq_common_stub


# 39: IRQ7
.globl k_irq_7
k_irq_7:
	cli
	pushl $0x0
	pushl $39
	jmp _k_irq_common_stub


# 40: IRQ8
.globl k_irq_8
k_irq_8:
	cli
	pushl $0x0
	pushl $40
	jmp _k_irq_common_stub


# 41: IRQ9
.globl k_irq_9
k_irq_9:
	cli
	pushl $0x0
	pushl $41
	jmp _k_irq_common_stub


# 42: IRQ10
.globl k_irq_10
k_irq_10:
	cli
	pushl $0x0
	pushl $42
	jmp _k_irq_common_stub


# 43: IRQ11
.globl k_irq_11
k_irq_11:
	cli
	pushl $0x0
	pushl $43
	jmp _k_irq_common_stub


# 44: IRQ12
.globl k_irq_12
k_irq_12:
	cli
	pushl $0x0
	pushl $44
	jmp _k_irq_common_stub


# 45: IRQ13
.globl k_irq_13
k_irq_13:
	cli
	pushl $0x0
	pushl $45
	jmp _k_irq_common_stub


# 46: IRQ14
.globl k_irq_14
k_irq_14:
	cli
	pushl $0x0
	pushl $46
	jmp _k_irq_common_stub


# 47: IRQ15
.globl k_irq_15
k_irq_15:
	cli
	pushl $0x0
	pushl $47
	jmp _k_irq_common_stub


.equ data_offset, 0x10
_k_irq_common_stub:
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs

	# Load kernel data segment descriptor
	movw $data_offset, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs

	# Push stack pointer, so everything pushed so far
	# can be accessed in 'k_irq_handler'
	pushl %esp

	leal k_irq_handler, %eax
	calll *%eax

	popl %eax
	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa

	addl $0x8, %esp

	# Pops five things at once: %eip, %cs, %eflags, %esp, %ss
	iret
