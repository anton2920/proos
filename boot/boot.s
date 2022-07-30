.code16

.section .text
.globl _start
_start:
	xorw %ax, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss

	movw $0x9000, %sp
	movw %sp, %bp

	movb %dl, bootdrv

	leaw booting_str, %di
	callw prints

	# Loading kernel pt. #1 (sectors 2 - 18 (1 is loaded by BIOS already))
	movb $0x2, %ah # Command: read sectors into memory
	movb $0x0, %dh # Head number = 0
	movb bootdrv, %dl
	movb $0x0, %ch # Cylinder/Track number = 0
	movb $0x2, %cl # Sector number = 2
	movb $0x11, %al
	movw $kernel_offset, %bx # Buffer address = ES:$kernel_offset
	int $0x13

	jc _start_drive_error

	# Loading kernel pt. #2 (sectors 19 - 37)
	movb $0x0, %ah
	shlw $0x9, %ax
	addw $kernel_offset, %ax
	movw %ax, %bx # Buffer address = ES:$kernel_offset

	movb $0x2, %ah # Command: read sectors into memory
	movb $0x1, %dh # Head number = 1
	movb bootdrv, %dl
	movb $0x0, %ch # Cylinder/Track number = 0
	movb $0x1, %cl # Sector number = 1
	movb $0x12, %al
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
	.asciz "Booting... "

drive_error_str:
	.asciz "Drive read failed: "

.include "io.s" # `prints`
.include "x86prot.s" # `switch_to_protected_mode`

# Zero padding
.org 510

# Magic number at the end, so BIOS will
# recognize these 512 bytes as bootsector
.word 0xAA55
