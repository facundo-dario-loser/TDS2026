
.globl main
main:
	enter $(8*8), $0

	# ComparisonSmallerIntInt
	mov -8(%rbp), %r10
	mov -16(%rbp), %r11
	cmp %r11, %r10
	mov $0, %r11
	mov $1, %r10
	cmovl %r10, %r11
	mov %r11, -24(%rbp)

	# AssignmentBoolBool
	mov -24(%rbp), %r10
	mov %r10, -32(%rbp)

	# ComparisonEqual
	mov -8(%rbp), %r10
	mov -16(%rbp), %r11
	cmp %r11, %r10
	mov $0, %r11
	mov $1, %r10
	cmove %r10, %r11
	mov %r11, -40(%rbp)

	# AssignmentBoolBool
	mov -40(%rbp), %r10
	mov %r10, -48(%rbp)

	# JmpFalse
	mov -32(%rbp), %r10
	mov $0, %r11
	cmp %r10, %r11
	je .label_0

	# JmpFalse
	mov -48(%rbp), %r10
	mov $0, %r11
	cmp %r10, %r11
	je .label_0

	# AssignmentBoolBool
	mov $1, %r10
	mov %r10, -56(%rbp)

	# Jmp
	jmp .label_1

.label_0:

	# AssignmentBoolBool
	mov $0, %r10
	mov %r10, -56(%rbp)

.label_1:

	# AssignmentBoolBool
	mov -56(%rbp), %r10
	mov %r10, -64(%rbp)

	# note: setting rax with exit code 0 (even if main doesn't return anything)
	mov $0, %rax

.end_method_main:
	leave
	ret
