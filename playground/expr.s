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
    pushq %rax
    movq $3, %rax
    movq %rax, %rcx
    popq %rax
    imulq %rcx, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq $2, %rax
    movq %rax, %rcx
    popq %rax
    cqto
    idivq %rcx
    movq %rax, %rcx
    popq %rax
    subq %rcx, %rax
    pushq %rax
    movq $5, %rax
    negq %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    sete %al
    movzbq %al, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    popq %rbp
    ret
.section .note.GNU-stack,"",@progbits
