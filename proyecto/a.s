.globl main
main:
	enter $(8*2), $0

	# AssignmentIntInt
	mov, $4, %r10
	mov %r10, -8(%rbp)

	# AdditionIntInt
	mov -8(%rbp), %r10
	add $2, %r10
	mov %r10, -16(%rbp)

	# AssignmentIntInt
	mov -16(%rbp), %r10
	mov %r10, -8(%rbp)

	mov $0, %rax
	leave
	ret
