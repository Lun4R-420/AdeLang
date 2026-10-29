.section .rodata
fmt: .string "%lld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
    movq $1, %rax
    movq %rax, -8(%rbp)
    movq $2, %rax
    movq %rax, -16(%rbp)
    movq $10, %rax
    movq %rax, -24(%rbp)
    movq -24(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $3, %rax
    movq %rax, -32(%rbp)
    movq -24(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq -8(%rbp), %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    movq %rbp, %rsp
    popq %rbp
    ret
.section .note.GNU-stack,"",@progbits
