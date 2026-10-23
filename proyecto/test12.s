
.text

.globl main
main:
	# note: 8 extra bytes were added (64 bits) to keep the stack aligned to 16 bytes
	enter $(8*4), $0

	# JmpFalse
	mov $1, %r10
	mov $0, %r11
	cmp %r10, %r11
	je .label_0

	# JmpFalse
	mov $1, %r10
	mov $0, %r11
	cmp %r10, %r11
	je .label_0

	# AssignmentBoolBool
	mov $1, %r10
	mov %r10, -8(%rbp)

	# Jmp
	jmp .label_1

.label_0:

	# AssignmentBoolBool
	mov $0, %r10
	mov %r10, -8(%rbp)

.label_1:

	# JmpFalse
	mov -8(%rbp), %r10
	mov $0, %r11
	cmp %r10, %r11
	je .label_2

	# JmpFalse
	mov $1, %r10
	mov $0, %r11
	cmp %r10, %r11
	je .label_2

	# AssignmentBoolBool
	mov $1, %r10
	mov %r10, -16(%rbp)

	# Jmp
	jmp .label_3

.label_2:

	# AssignmentBoolBool
	mov $0, %r10
	mov %r10, -16(%rbp)

.label_3:

	# AssignmentBoolBool
	mov -16(%rbp), %r10
	mov %r10, -24(%rbp)

	# note: setting rax with exit code 0 (even if main doesn't return anything)
	mov $0, %rax

.end_method_main:
	leave
	ret
