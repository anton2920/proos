.code32

.globl _start
.type _start, @function
_start:
.ifndef TEST
	calll k_main
.else
	calll k_test
.endif
	calll halt


.globl halt
.type halt, @function
halt:
	cli
halt_loop:
	hlt
	jmp halt_loop
