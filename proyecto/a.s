
.text

factorial_recursivo_cola:
	enter $(8*6), $0

	# SaveAllArguments
	mov %rdi, -8(%rbp)
	mov %rsi, -16(%rbp)

	# ComparisonEqual
	mov -8(%rbp), %r10
	mov $0, %r11
	cmp %r11, %r10
	mov $0, %r11
	mov $1, %r10
	cmove %r10, %r11
	mov %r11, -24(%rbp)

	# JmpFalse
	mov -24(%rbp), %r10
	mov $0, %r11
	cmp %r10, %r11
	je .label_0

	# ReturnFromMethod
	mov -16(%rbp), %rax
	jmp .end_method_factorial_recursivo_cola

.label_0:

	# SubtractionIntInt
	mov -8(%rbp), %r10
	sub $1, %r10
	mov %r10, -32(%rbp)

	# MultiplicationIntInt
	mov -16(%rbp), %r10
	mov -8(%rbp), %r11
	imul %r10, %r11
	mov %r11, -40(%rbp)

	# PassingArgumentForMethodCall
	mov -32(%rbp), %rdi

	# PassingArgumentForMethodCall
	mov -40(%rbp), %rsi

	# CallMethod
	call factorial_recursivo_cola

	# SavingReturnValueFromMethodInTemporal
	mov %rax, -48(%rbp)

	# ReturnFromMethod
	mov -48(%rbp), %rax
	jmp .end_method_factorial_recursivo_cola

.end_method_factorial_recursivo_cola:
	leave
	ret

.globl main
main:
	# note: 8 extra bytes were added (64 bits) to keep the stack aligned to 16 bytes
	enter $(8*4), $0

	# PassingArgumentForMethodCall
	mov $3, %rdi

	# PassingArgumentForMethodCall
	mov $1, %rsi

	# CallMethod
	call factorial_recursivo_cola

	# SavingReturnValueFromMethodInTemporal
	mov %rax, -8(%rbp)

	# PassingArgumentForMethodCall
	mov -8(%rbp), %rdi

	# PassingArgumentForMethodCall
	mov $1, %rsi

	# CallMethod
	call factorial_recursivo_cola

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
