#  0: Divide By Zero Exception
.globl k_isr_0
k_isr_0:
	cli
	pushl $0x0
	pushl $0
	jmp _k_isr_common_stub


#  1: Debug Exception
.globl k_isr_1
k_isr_1:
	cli
	pushl $0x0
	pushl $1
	jmp _k_isr_common_stub


#  2: Non Maskable Interrupt Exception
.globl k_isr_2
k_isr_2:
	cli
	pushl $0x0
	pushl $2
	jmp _k_isr_common_stub


#  3: Int 3 Exception
.globl k_isr_3
k_isr_3:
	cli
	pushl $0x0
	pushl $3
	jmp _k_isr_common_stub


#  4: INTO Exception
.globl k_isr_4
k_isr_4:
	cli
	pushl $0x0
	pushl $4
	jmp _k_isr_common_stub


#  5: Out of Bounds Exception
.globl k_isr_5
k_isr_5:
	cli
	pushl $0x0
	pushl $5
	jmp _k_isr_common_stub


#  6: Invalid Opcode Exception
.globl k_isr_6
k_isr_6:
	cli
	pushl $0x0
	pushl $6
	jmp _k_isr_common_stub


#  7: Coprocessor Not Available Exception
.globl k_isr_7
k_isr_7:
	cli
	pushl $0x0
	pushl $7
	jmp _k_isr_common_stub


#  8: Double Fault Exception (With Error Code!)
.globl k_isr_8
k_isr_8:
	cli
	pushl $8
	jmp _k_isr_common_stub


#  9: Coprocessor Segment Overrun Exception
.globl k_isr_9
k_isr_9:
	cli
	pushl $0x0
	pushl $9
	jmp _k_isr_common_stub


# 10: Bad TSS Exception (With Error Code!)
.globl k_isr_10
k_isr_10:
	cli
	pushl $10
	jmp _k_isr_common_stub


# 11: Segment Not Present Exception (With Error Code!)
.globl k_isr_11
k_isr_11:
	cli
	pushl $11
	jmp _k_isr_common_stub


# 12: Stack Fault Exception (With Error Code!)
.globl k_isr_12
k_isr_12:
	cli
	pushl $12
	jmp _k_isr_common_stub


# 13: General Protection Fault Exception (With Error Code!)
.globl k_isr_13
k_isr_13:
	cli
	pushl $13
	jmp _k_isr_common_stub


# 14: Page Fault Exception (With Error Code!)
.globl k_isr_14
k_isr_14:
	cli
	pushl $14
	jmp _k_isr_common_stub


# 15: Reserved Exception
.globl k_isr_15
k_isr_15:
	cli
	pushl $0x0
	pushl $15
	jmp _k_isr_common_stub


# 16: Floating Point Exception
.globl k_isr_16
k_isr_16:
	cli
	pushl $0x0
	pushl $16
	jmp _k_isr_common_stub


# 17: Alignment Check Exception
.globl k_isr_17
k_isr_17:
	cli
	pushl $0x0
	pushl $17
	jmp _k_isr_common_stub


# 18: Machine Check Exception
.globl k_isr_18
k_isr_18:
	cli
	pushl $0x0
	pushl $18
	jmp _k_isr_common_stub


# 19: Reserved
.globl k_isr_19
k_isr_19:
	cli
	pushl $0x0
	pushl $19
	jmp _k_isr_common_stub


# 20: Reserved
.globl k_isr_20
k_isr_20:
	cli
	pushl $0x0
	pushl $20
	jmp _k_isr_common_stub


# 21: Reserved
.globl k_isr_21
k_isr_21:
	cli
	pushl $0x0
	pushl $21
	jmp _k_isr_common_stub


# 22: Reserved
.globl k_isr_22
k_isr_22:
	cli
	pushl $0x0
	pushl $22
	jmp _k_isr_common_stub


# 23: Reserved
.globl k_isr_23
k_isr_23:
	cli
	pushl $0x0
	pushl $23
	jmp _k_isr_common_stub


# 24: Reserved
.globl k_isr_24
k_isr_24:
	cli
	pushl $0x0
	pushl $24
	jmp _k_isr_common_stub


# 25: Reserved
.globl k_isr_25
k_isr_25:
	cli
	pushl $0x0
	pushl $25
	jmp _k_isr_common_stub


# 26: Reserved
.globl k_isr_26
k_isr_26:
	cli
	pushl $0x0
	pushl $26
	jmp _k_isr_common_stub


# 27: Reserved
.globl k_isr_27
k_isr_27:
	cli
	pushl $0x0
	pushl $27
	jmp _k_isr_common_stub


# 28: Reserved
.globl k_isr_28
k_isr_28:
	cli
	pushl $0x0
	pushl $28
	jmp _k_isr_common_stub


# 29: Reserved
.globl k_isr_29
k_isr_29:
	cli
	pushl $0x0
	pushl $29
	jmp _k_isr_common_stub


# 30: Reserved
.globl k_isr_30
k_isr_30:
	cli
	pushl $0x0
	pushl $30
	jmp _k_isr_common_stub


# 31: Reserved
.globl k_isr_31
k_isr_31:
	cli
	pushl $0x0
	pushl $31
	jmp _k_isr_common_stub


# This is our common ISR stub. It saves the processor state, sets
# up for kernel mode segments, calls the C-level fault handler,
# and finally restores the stack frame.
.equ data_offset, 0x10
_k_isr_common_stub:
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
	# can be accessed in 'k_isrs_exception_handler'
	pushl %esp

	leal k_isr_exception_handler, %eax
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
