
.text

.globl main
main:
	enter $(8*4), $0

	# AssignmentIntInt
	mov $4, %r10
	mov %r10, -8(%rbp)

	# MultiplicationIntInt
	mov -8(%rbp), %r10
	mov $1, %rcx
	shl %r10 # optimization (faster than imul)
	mov %r10, -24(%rbp)

	# AssignmentIntInt
	mov -24(%rbp), %r10
	mov %r10, -16(%rbp)

	# MultiplicationIntInt
	mov -8(%rbp), %r10
	mov $4, %r11
	imul %r10, %r11
	mov %r11, -32(%rbp)

	# AssignmentIntInt
	mov -32(%rbp), %r10
	mov %r10, -16(%rbp)

	# note: setting rax with exit code 0 (even if main doesn't return anything)
	mov $0, %rax

.end_method_main:
	leave
	ret
