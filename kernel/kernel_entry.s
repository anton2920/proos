.code32

.globl _start
.type _start, @function
_start:
	calll kernel_main
	jmp .
