.code16

# GDT
gdt_start:

gdt_null: # the mandatory null descriptor
	.long 0x0
	.long 0x0

gdt_code: # the code segment descriptor
# base = 0x0, limit = 0xFFFFF,
# 1st flags:  (present)1 (privilege)00 (descriptor type)1 -> 0b1001
# type flags: (code)1 (conforming)0 (readable)1 (accessed)0 -> 0b1010
# 2nd flags : (granularity)1 (32-bit default)1 (64-bit seg)0 (AVL)0 -> 0b1100
	.word 0xffff # Limit (bits 0-15)
	.word 0x0 # Base (bits 0-15)
	.byte 0x0 # Base (bits 16-23)
	.byte 0b10011010 # 1st flags, type flags
	.byte 0b11001111 # 2nd flags, Limit (bits 16-19)
	.byte 0x0 # Base (bits 24-31)

gdt_data: # the data segment descriptor
# Same as code segment except for the type flags:
# type flags: (code)0 (expand down)0 (writable)1 (accessed)0 -> 0b0010
	.word 0xffff # Limit (bits 0-15)
	.word 0x0 # Base (bits 0-15)
	.byte 0x0 # Base (bits 16-23)
	.byte 0b10010010 # 1st flags, type flags
	.byte 0b11001111 # 2nd flags, Limit (bits 16 -19)
	.byte 0x0 # Base (bits 24-31)

gdt_end:
# The reason for putting a label at the end of the GDT is so we can have the assembler calculate
# the size of the GDT for the GDT decriptor (below) GDT descriptior

gdt_descriptor:
	.word gdt_end - gdt_start - 1 # Size of our GDT, always less one of the true size
	.long gdt_start # Start address of our GDT

# Define some handy constants for the GDT segment descriptor offsets, which
# are what segment registers must contain when in protected mode. For example,
# when we set DS = 0x10 in PM, the CPU knows that we mean it to use the
# segment described at offset 0x10 (i.e. 16 bytes) in our GDT, which in our
# case is the DATA segment (0x0 -> NULL # 0x08 -> CODE # 0x10 -> DATA)
.equ code_seg, gdt_code - gdt_start
.equ data_seg, gdt_data - gdt_start

.equ kernel_offset, 0x1000

# _Noreturn void switch_to_protected_mode(void)
.type switch_to_protected_mode, @function
switch_to_protected_mode:
	cli
	lgdt gdt_descriptor
	movl %cr0, %eax
	orl $0x1, %eax
	movl %eax, %cr0

	jmp $code_seg, $init_protected_mode

.code32
.extern _start_protected_mode
init_protected_mode:
	movw $data_seg, %ax
	movw %ax, %ds
	movw %ax, %ss
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs

	movl $0x90000, %esp
	movl %esp, %ebp

	jmp kernel_offset
