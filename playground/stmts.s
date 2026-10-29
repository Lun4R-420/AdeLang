.section .rodata
fmt: .string "%lld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    movq $1, %rax
    pushq %rax
    movq $2, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $10, %rax
    pushq %rax
    movq $3, %rax
    movq %rax, %rcx
    popq %rax
    cqto
    idivq %rcx
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $7, %rax
    pushq %rax
    movq $6, %rax
    movq %rax, %rcx
    popq %rax
    imulq %rcx, %rax
    movq $5, %rax
    negq %rax
    pushq %rax
    movq $2, %rax
    movq %rax, %rcx
    popq %rax
    imulq %rcx, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    movq %rbp, %rsp
    popq %rbp
    ret
.section .note.GNU-stack,"",@progbits
