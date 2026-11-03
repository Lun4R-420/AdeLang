.section .rodata
fmt: .string "%lld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $1, %rax
    pushq %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $5, %rax
    movq %rax, -8(%rbp)
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    movq %rbp, %rsp
    popq %rbp
    ret
.section .note.GNU-stack,"",@progbits
