f:
	enter $(8*3), $0

	# SaveAllArguments
	mov %rdi, -8(%rbp)
	mov %rsi, -16(%rbp)

	# AdditionIntInt
	mov -8(%rbp), %r10
	add -16(%rbp), %r10
	mov %r10, -24(%rbp)

	# ReturnFromMethod
	mov -24(%rbp), rax

	leave
	ret

.globl main
main:
	enter $(8*3), $0

