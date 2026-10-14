f:
	# note: 8 extra bytes were added (64 bits) to keep the stack aligned to 16 bytes
	enter $(8*4), $0

	# SaveAllArguments
	mov %rdi, -8(%rbp)
	mov %rsi, -16(%rbp)

	# AdditionIntInt
	mov -8(%rbp), %r10
	add -16(%rbp), %r10
	mov %r10, -24(%rbp)

	# ReturnFromMethod
	mov -24(%rbp), %rax
	jmp .end_method_f

.end_method_f:
	leave
	ret

.globl main
main:
	# note: 8 extra bytes were added (64 bits) to keep the stack aligned to 16 bytes
	enter $(8*4), $0

	# PassingArgumentForMethodCall
	mov $1, %rdi

	# PassingArgumentForMethodCall
	mov $2, %rsi

	# CallMethod
	call f

	# SavingReturnValueFromMethodInTemporal
	mov %rax, -8(%rbp)

	# AdditionIntInt
	mov $4, %r10
	add $4, %r10
	mov %r10, -16(%rbp)

	# PassingArgumentForMethodCall
	mov -16(%rbp), %rdi

	# PassingArgumentForMethodCall
	mov $8, %rsi

	# CallMethod
	call f

	# SavingReturnValueFromMethodInTemporal
	mov %rax, -24(%rbp)

	# note: setting rax with 0 exit code (even if main doesn't return anything)
	mov $0, %rax

.end_method_main:
	leave
	ret
