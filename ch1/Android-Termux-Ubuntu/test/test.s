	.arch armv8-a
	.file	"test.c"
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"Hello, World!/n"
	.align	3
.LC1:
	.string	"1 + 2 = %d/n"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	mov	w0, 3
	str	w0, [x29, 28]
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	adrp	x0, .LC1
	add	x0, x0, :lo12:.LC1
	ldr	w1, [x29, 28]
	bl	printf
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
