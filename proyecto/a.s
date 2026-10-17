
f:
	enter $(8*2), $0

	# SaveAllArguments
	mov %rdi, -8(%rbp)

	# ComparisonGreaterIntInt
	mov -8(%rbp), %r10
	mov $2, %r11
	cmp %r11, %r10
	mov $0, %r11
	mov $1, %r10
	cmovg %r10, %r11
	mov %r11, -16(%rbp)

	# ReturnFromMethod
	mov -16(%rbp), %rax
	jmp .end_method_f

.end_method_f:
	leave
	ret

.globl main
main:
	enter $(8*6), $0

	# AssignmentIntInt
	mov $4, %r10
	mov %r10, -8(%rbp)

	# AssignmentBoolBool
	mov $1, %r10
	mov %r10, -16(%rbp)

	# AssignmentBoolBool
	mov $0, %r10
	mov %r10, -24(%rbp)

	# JmpFalse
	mov -16(%rbp), %r10
	mov $0, %r11
	cmp %r10, %r11
	je .label_0

	# PassingArgumentForMethodCall
	mov $4, %rdi

	# CallMethod
	call f

	# SavingReturnValueFromMethodInTemporal
	mov %rax, -32(%rbp)

	# JmpFalse
	mov -32(%rbp), %r10
	mov $0, %r11
	cmp %r10, %r11
	je .label_0

	# AssignmentBoolBool
	mov $1, %r10
	mov %r10, -40(%rbp)

	# Jmp
	jmp .label_1

.label_0:

	# AssignmentBoolBool
	mov $0, %r10
	mov %r10, -40(%rbp)

.label_1:

	# AssignmentBoolBool
	mov -40(%rbp), %r10
	mov %r10, -48(%rbp)

	# note: setting rax with exit code 0 (even if main doesn't return anything)
	mov $0, %rax

.end_method_main:
	leave
	ret
