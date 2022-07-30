.code32

.globl _start
.type _start, @function
_start:
.ifndef TEST
	calll kernel_main
.else
	calll k_test
.endif
	jmp .
