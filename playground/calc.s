.text
.globl main
main:
    movq $1, %rax
    pushq %rax
    movq $2, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    pushq %rax
    movq $3, %rax
    movq %rax, %rcx
    popq %rax
    imulq %rcx, %rax
    ret

.section .note.GNU-stack,"",@progbits
