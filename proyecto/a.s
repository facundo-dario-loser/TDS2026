.data

.globl x
x: .quad 0

f:
	enter $(8*2), $0

	# SaveAllArguments
	mov %rdi, -8(%rbp)

	# AdditionIntInt
	mov x(%rip), %r10
	add -8(%rbp), %r10
	mov %r10, -16(%rbp)

	# ReturnFromMethod
	mov -16(%rbp), %rax
	jmp .end_method_f

.end_method_f:
	leave
	ret

.globl main
main:
	enter $(8*2), $0

	# PassingArgumentForMethodCall
	mov $4, %rdi

	# CallMethod
	call f

	# SavingReturnValueFromMethodInTemporal
	mov %rax, -8(%rbp)

	# AssignmentIntInt
	mov -8(%rbp), %r10
	mov %r10, -16(%rbp)

	# note: setting rax with exit code 0 (even if main doesn't return anything)
	mov $0, %rax

.end_method_main:
	leave
	ret
