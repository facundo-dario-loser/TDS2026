.text
.globl main

main:
	enter $(8*4), $0

	# ASSIGMENT
	movq $4, -8(%rbp)

	# ASSIGMENT
	movq $2, -16(%rbp)

	# ADD
	mov -8(%rbp), %r10
	add -16(%rbp), %r10
	mov %r10, -24(%rbp)

	# ASSIGMENT
	mov -24(%rbp), %r10
	mov %r10, -32(%rbp)

	# RETURN
	mov -32(%rbp), %eax

	leave
	ret

