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
