
.text

.globl main
main:
	enter $(8*4), $0

	# AssignmentIntInt
	mov $8, %r10
	mov %r10, -8(%rbp)

	# DivisionIntInt
	mov -8(%rbp), %rax
	mov $1, %rcx
	shr %rax # optimization (faster than idiv)
	mov %rax, -24(%rbp) # save the quotient

	# AssignmentIntInt
	mov -24(%rbp), %r10
	mov %r10, -16(%rbp)

	# DivisionIntInt
	mov $16, %rax
	mov -8(%rbp), %r10
	cqto # extend rax sign to rdx
	idiv %r10
	mov %rax, -32(%rbp) # save the quotient

	# AssignmentIntInt
	mov -32(%rbp), %r10
	mov %r10, -16(%rbp)

	# note: setting rax with exit code 0 (even if main doesn't return anything)
	mov $0, %rax

.end_method_main:
	leave
	ret
