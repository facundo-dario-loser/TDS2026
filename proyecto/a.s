f:
	enter $(8*8), $0

	# SaveAllArguments
	mov %rdi, -8(%rbp)
	mov %rsi, -16(%rbp)
	mov %rdx, -24(%rbp)
	mov %rcx, -32(%rbp)
	mov %r8, -40(%rbp)
	mov %r9, -48(%rbp)
	mov 16(%rbp), %r10
	mov %r10, -56(%rbp)
	mov 24(%rbp), %r10
	mov %r10, -64(%rbp)

	# ReturnFromMethod
	mov $200, %rax
	
	# printReturnedValue
	mov %rax, %rdi
	call printInt

	jmp .end_method_f

.end_method_f:
	leave
	ret

.globl main
main:
	enter $(8*4), $0

	# AssignmentIntInt
	mov $20, %r10
	mov %r10, -8(%rbp)

	# AssignmentIntInt
	mov $40, %r10
	mov %r10, -16(%rbp)

	# PassingArgumentForMethodCall
	mov -8(%rbp), %rdi

	# PassingArgumentForMethodCall
	mov -16(%rbp), %rsi

	# PassingArgumentForMethodCall
	mov $8, %rdx

	# PassingArgumentForMethodCall
	mov $9, %rcx

	# PassingArgumentForMethodCall
	mov $10, %r8

	# PassingArgumentForMethodCall
	mov $11, %r9

	# PassingArgumentForMethodCall
	mov $13, %r10
	push %r10

	# PassingArgumentForMethodCall
	mov $12, %r10
	push %r10

	# CallMethod
	call f

	# SavingReturnValueFromMethodInTemporal
	mov %rax, -24(%rbp)

	# PopingArgumentsFromStack
	pop %r10
	pop %r10

	# AssignmentIntInt
	mov -24(%rbp), %r10
	mov %r10, -32(%rbp)

	# note: setting rax with exit code 0 (even if main doesn't return anything)
	mov $0, %rax

.end_method_main:
	leave
	ret
