
.text

.globl main
main:
	# note: 8 extra bytes were added (64 bits) to keep the stack aligned to 16 bytes
	enter $(8*8), $0

	# AssignmentIntInt
	mov $2, %r10
	mov %r10, -8(%rbp)

	# AssignmentIntInt
	mov $9, %r10
	mov %r10, -16(%rbp)

	# AdditionIntInt
	mov -8(%rbp), %r10
	add -16(%rbp), %r10
	mov %r10, -24(%rbp)

	# AssignmentIntInt
	mov -24(%rbp), %r10
	mov %r10, -32(%rbp)

	# PassingArgumentForMethodCall
	mov -32(%rbp), %rdi

	# CallMethod
	mov $0, %rax
	call printInt

	# AssignmentIntInt
	mov $2, %r10
	mov %r10, -8(%rbp)

	# AssignmentIntInt
	mov $9, %r10
	mov %r10, -16(%rbp)

	# SubtractionIntInt
	mov -16(%rbp), %r10
	sub -8(%rbp), %r10
	mov %r10, -40(%rbp)

	# AssignmentIntInt
	mov -40(%rbp), %r10
	mov %r10, -32(%rbp)

	# PassingArgumentForMethodCall
	mov -32(%rbp), %rdi

	# CallMethod
	mov $0, %rax
	call printInt

	# AssignmentIntInt
	mov $4, %r10
	mov %r10, -8(%rbp)

	# AssignmentIntInt
	mov $6, %r10
	mov %r10, -16(%rbp)

	# MultiplicationIntInt
	mov -8(%rbp), %r10
	mov -16(%rbp), %r11
	imul %r10, %r11
	mov %r11, -48(%rbp)

	# AssignmentIntInt
	mov -48(%rbp), %r10
	mov %r10, -32(%rbp)

	# PassingArgumentForMethodCall
	mov -32(%rbp), %rdi

	# CallMethod
	mov $0, %rax
	call printInt

	# AssignmentIntInt
	mov $8, %r10
	mov %r10, -8(%rbp)

	# AssignmentIntInt
	mov $4, %r10
	mov %r10, -16(%rbp)

	# DivisionIntInt
	mov -8(%rbp), %rax
	mov -16(%rbp), %r10
	cqto # extend rax sign to rdx
	idiv %r10
	mov %rax, -56(%rbp) # save the quotient

	# AssignmentIntInt
	mov -56(%rbp), %r10
	mov %r10, -32(%rbp)

	# PassingArgumentForMethodCall
	mov -32(%rbp), %rdi

	# CallMethod
	mov $0, %rax
	call printInt

	# note: setting rax with exit code 0 (even if main doesn't return anything)
	mov $0, %rax

.end_method_main:
	leave
	ret
