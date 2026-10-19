
.text

factorial_iterativo:
	enter $(8*6), $0

	# SaveAllArguments
	mov %rdi, -8(%rbp)

	# ComparisonEqual
	mov -8(%rbp), %r10
	mov $0, %r11
	cmp %r11, %r10
	mov $0, %r11
	mov $1, %r10
	cmove %r10, %r11
	mov %r11, -16(%rbp)

	# JmpFalse
	mov -16(%rbp), %r10
	mov $0, %r11
	cmp %r10, %r11
	je .label_0

	# ReturnFromMethod
	mov $1, %rax
	jmp .end_method_factorial_iterativo

.label_0:

	# AssignmentIntInt
	mov $1, %r10
	mov %r10, -24(%rbp)

.label_1:

	# ComparisonGreaterIntInt
	mov -8(%rbp), %r10
	mov $0, %r11
	cmp %r11, %r10
	mov $0, %r11
	mov $1, %r10
	cmovg %r10, %r11
	mov %r11, -32(%rbp)

	# JmpFalse
	mov -32(%rbp), %r10
	mov $0, %r11
	cmp %r10, %r11
	je .label_2

	# MultiplicationIntInt
	mov -24(%rbp), %r10
	mov -8(%rbp), %r11
	imul %r10, %r11
	mov %r11, -40(%rbp)

	# AssignmentIntInt
	mov -40(%rbp), %r10
	mov %r10, -24(%rbp)

	# SubtractionIntInt
	mov -8(%rbp), %r10
	sub $1, %r10
	mov %r10, -48(%rbp)

	# AssignmentIntInt
	mov -48(%rbp), %r10
	mov %r10, -8(%rbp)

	# Jmp
	jmp .label_1

.label_2:

	# ReturnFromMethod
	mov -24(%rbp), %rax
	jmp .end_method_factorial_iterativo

.end_method_factorial_iterativo:
	leave
	ret

.globl main
main:
	# note: 8 extra bytes were added (64 bits) to keep the stack aligned to 16 bytes
	enter $(8*4), $0

	# PassingArgumentForMethodCall
	mov $3, %rdi

	# CallMethod
	call factorial_iterativo

	# SavingReturnValueFromMethodInTemporal
	mov %rax, -8(%rbp)

	# PassingArgumentForMethodCall
	mov -8(%rbp), %rdi

	# CallMethod
	call factorial_iterativo

	# SavingReturnValueFromMethodInTemporal
	mov %rax, -16(%rbp)

	# AssignmentIntInt
	mov -16(%rbp), %r10
	mov %r10, -24(%rbp)

	# PassingArgumentForMethodCall
	mov -24(%rbp), %rdi

	# CallMethod
	mov $0, %rax
	call printInt

	# note: setting rax with exit code 0 (even if main doesn't return anything)
	mov $0, %rax

.end_method_main:
	leave
	ret
