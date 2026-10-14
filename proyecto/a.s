.globl main
main:
	enter $(8*4), $0

	# AssignmentBoolBool
	mov $1, %r10
	mov %r10, -8(%rbp)

	# AssignmentBoolBool
	mov $0, %r10
	mov %r10, -16(%rbp)

	# And
	mov -8(%rbp), %r10
	mov -16(%rbp), %r11
	and r10, r11
	mov %r11, -24(%rbp)

	# AssignmentBoolBool
	mov -24(%rbp), %r10
	mov %r10, -32(%rbp)

	# note: setting rax with 0 exit code (even if main doesn't return anything)
	mov $0, %rax

.end_method_main:
	leave
	ret
