.data

.globl x
x: .quad 0

.globl y
y: .quad 0

.globl main
main:
	enter $(8*12), $0

	# AssignmentIntInt
	mov $1, %r10
	mov %r10, x(%rip)

	# AssignmentIntInt
	mov $2, %r10
	mov %r10, y(%rip)

	# AssignmentIntInt
	mov $3, %r10
	mov %r10, -8(%rbp)

	# AssignmentIntInt
	mov $4, %r10
	mov %r10, -16(%rbp)

	# ModIntInt
	mov -8(%rbp), %rax
	mov -16(%rbp), %r10
	cqto # extend rax sign to rdx
	idiv %r10
	mov %rdx, -24(%rbp) # save the remainder

	# AssignmentIntInt
	mov -24(%rbp), %r10
	mov %r10, -32(%rbp)

	# ModIntInt
	mov -8(%rbp), %rax
	mov x(%rip), %r10
	cqto # extend rax sign to rdx
	idiv %r10
	mov %rdx, -40(%rbp) # save the remainder

	# AssignmentIntInt
	mov -40(%rbp), %r10
	mov %r10, -32(%rbp)

	# ModIntInt
	mov -8(%rbp), %rax
	mov $4, %r10
	cqto # extend rax sign to rdx
	idiv %r10
	mov %rdx, -48(%rbp) # save the remainder

	# AssignmentIntInt
	mov -48(%rbp), %r10
	mov %r10, -32(%rbp)

	# ModIntInt
	mov x(%rip), %rax
	mov -8(%rbp), %r10
	cqto # extend rax sign to rdx
	idiv %r10
	mov %rdx, -56(%rbp) # save the remainder

	# AssignmentIntInt
	mov -56(%rbp), %r10
	mov %r10, -32(%rbp)

	# ModIntInt
	mov x(%rip), %rax
	mov y(%rip), %r10
	cqto # extend rax sign to rdx
	idiv %r10
	mov %rdx, -64(%rbp) # save the remainder

	# AssignmentIntInt
	mov -64(%rbp), %r10
	mov %r10, -32(%rbp)

	# ModIntInt
	mov x(%rip), %rax
	mov $8, %r10
	cqto # extend rax sign to rdx
	idiv %r10
	mov %rdx, -72(%rbp) # save the remainder

	# AssignmentIntInt
	mov -72(%rbp), %r10
	mov %r10, -32(%rbp)

	# ModIntInt
	mov $9, %r10
	mov -8(%rbp), %r10
	cqto # extend rax sign to rdx
	idiv %r10
	mov %rdx, -80(%rbp) # save the remainder

	# AssignmentIntInt
	mov -80(%rbp), %r10
	mov %r10, -32(%rbp)

	# ModIntInt
	mov $9, %rax
	mov x(%rip), %r10
	cqto # extend rax sign to rdx
	idiv %r10
	mov %rdx, -88(%rbp) # save the remainder

	# AssignmentIntInt
	mov -88(%rbp), %r10
	mov %r10, -32(%rbp)

	# ModIntInt
	mov $9, %r10
	mov $14, %r10
	cqto # extend rax sign to rdx
	idiv %r10
	mov %rdx, -96(%rbp) # save the remainder

	# AssignmentIntInt
	mov -96(%rbp), %r10
	mov %r10, -32(%rbp)

	# note: setting rax with exit code 0 (even if main doesn't return anything)
	mov $0, %rax

.end_method_main:
	leave
	ret
