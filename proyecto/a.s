.data

.globl x
x: .quad 0

.globl y
y: .quad 0

.globl z
z: .quad 0

.globl main
main:
	enter $(8*0), $0

	# AssignmentIntInt
	mov $4, %r10
	mov %r10, x(%rip)

	# AssignmentIntInt
	mov $2, %r10
	mov %r10, y(%rip)

	# AssignmentIntInt
	mov x(%rip), %r10
	mov %r10, z(%rip)

	# note: setting rax with exit code 0 (even if main doesn't return anything)
	mov $0, %rax

.end_method_main:
	leave
	ret
