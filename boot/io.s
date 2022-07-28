.code16

# void prints(const char *);
.type prints, @function
.globl prints
prints:
	movb $0xE, %ah # Teletype write to active page
	movw %di, %si
	cld

prints_loop:
	lodsb
	testb %al, %al
	jz prints_loop_end

	int $0x10

	jmp prints_loop

prints_loop_end:
	retw

# void printw(short);
.type printw, @function
.globl printw
printw:
	leaw printw_out_str, %si
	movw $printw_out_str_len - 2, %dx
	callw printw_generic
	retw

# void printwln(short);
.globl printwln
printwln:
	leaw printwln_out_str, %si
	movw $printwln_out_str_len - 4, %dx
	callw printw_generic
	retw

# static void printw_generic(short, char *, short)
.type printw_generic, @function
printw_generic:
	pushw %bp
	movw %sp, %bp

	pushw %bx

	movw %dx, %bx
	movw %di, %dx

	leaw (%bx, %si), %di
	std

	movb $'0', 2(%si)
	movb $'0', 3(%si)
	movb $'0', 4(%si)
	movb $'0', 5(%si)

printw_generic_loop:
	testw %dx, %dx
	jz printw_generic_loop_end

	movw %dx, %ax
	andw $0xF, %ax

	cmpb $0xA, %al
	jb printw_generic_if_else

	subb $0xA, %al
	addb $'A', %al

	jmp printw_generic_if_fi

printw_generic_if_else:
	addb $'0', %al

printw_generic_if_fi:
	stosb

	shrw $0x4, %dx
	jmp printw_generic_loop

printw_generic_loop_end:
	movw %si, %di
	callw prints

	popw %bx

	movw %bp, %sp
	popw %bp
	retw

# .section .data
printw_out_str:
	.asciz "0x0000"
	.equ printw_out_str_len, . - printw_out_str

printwln_out_str:
	.asciz "0x0000\r\n"
	.equ printwln_out_str_len, . - printwln_out_str
