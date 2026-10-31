
.text

.globl main
main:
	# note: 8 extra bytes were added (64 bits) to keep the stack aligned to 16 bytes
	enter $(8*6), $0

	# AssignmentIntInt
	mov $20, %r10
	mov %r10, -8(%rbp)

	# PassingArgumentForMethodCall
	mov -8(%rbp), %rdi

	# CallMethod
	mov $0, %rax
	call printInt

.label_0:

	# ComparisonGreaterIntInt
	mov -8(%rbp), %r10
	mov $0, %r11
	cmp %r11, %r10
	mov $0, %r11
	mov $1, %r10
	cmovg %r10, %r11
	mov %r11, -24(%rbp)

	# JmpFalse
	mov -24(%rbp), %r10
	mov $0, %r11
	cmp %r10, %r11
	je .label_1

	# SubtractionIntInt
	mov -8(%rbp), %r10
	sub $1, %r10
	mov %r10, -32(%rbp)

	# AssignmentIntInt
	mov -32(%rbp), %r10
	mov %r10, -8(%rbp)

	# Jmp
	jmp .label_0

.label_1:

	# PassingArgumentForMethodCall
	mov -8(%rbp), %rdi

	# CallMethod
	mov $0, %rax
	call printInt

	# note: setting rax with exit code 0 (even if main doesn't return anything)
	mov $0, %rax

.end_method_main:
	leave
	ret
