.code16

.section .text
.globl _start
_start:
	movw $0x9000, %sp
	movw %sp, %bp

	movb %dl, bootdrv

	leaw booting_str, %di
	callw prints

	# Loading kernel
	.equ nsectors_read, 16
	movb $0x2, %ah # Command: read sectors into memory
	xorw %dx, %dx # Head number = 0
	movb bootdrv, %dl
	xorw %cx, %cx # Cylinder/Track number = 0
	movb $0x2, %cl # Sector number = 2
	movb $nsectors_read, %al
	movw $kernel_offset, %bx # Buffer address = ES:$kernel_offset
	int $0x13

	jc _start_drive_error

	# Switching to 32-bit protected mode; the point of _Noreturn
	callw switch_to_protected_mode

_start_drive_error:
	shrw $0x8, %ax
	pushw %ax

	leaw drive_error_str, %di
	callw prints

	popw %di
	callw printwln

_start_end:
	jmp .

# .section .data
bootdrv:
	.byte 0

# .section .rodata
booting_str:
	.asciz "Booting...\r\n"

drive_error_str:
	.asciz "Drive read failed: "

.include "io.s" # `prints`
.include "x86prot.s" # `switch_to_protected_mode`

# Zero padding
.org 510

# Magic number at the end, so BIOS will
# recognize these 512 bytes as bootsector
.word 0xAA55
