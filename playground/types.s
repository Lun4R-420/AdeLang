.section .rodata
fmt: .string "%lld\n"
.text
.globl main
ade_isEven:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rdi, -8(%rbp)
    movq -8(%rbp), %rax
    pushq %rax
    movq $2, %rax
    movq %rax, %rcx
    popq %rax
    cqto
    idivq %rcx
    movq %rdx, %rax
    pushq %rax
    movq $0, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    sete %al
    movzbq %al, %rax
    jmp .Lret_ade_isEven
    movq $0, %rax
.Lret_ade_isEven:
    movq %rbp, %rsp
    popq %rbp
    ret
ade_square:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rdi, -8(%rbp)
    movq -8(%rbp), %rax
    pushq %rax
    movq -8(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    imulq %rcx, %rax
    jmp .Lret_ade_square
    movq $0, %rax
.Lret_ade_square:
    movq %rbp, %rsp
    popq %rbp
    ret
ade_both:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rdi, -8(%rbp)
    movq %rsi, -16(%rbp)
    movq -8(%rbp), %rax
    cmpq $0, %rax
    je .Land_end_0
    movq -16(%rbp), %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
.Land_end_0:
    jmp .Lret_ade_both
    movq $0, %rax
.Lret_ade_both:
    movq %rbp, %rsp
    popq %rbp
    ret
ade_greet:
    pushq %rbp
    movq %rsp, %rbp
    movq $7, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $0, %rax
.Lret_ade_greet:
    movq %rbp, %rsp
    popq %rbp
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp
    movq $1, %rax
    movq %rax, -8(%rbp)
    movq $0, %rax
    movq %rax, -16(%rbp)
    movq $42, %rax
    movq %rax, -24(%rbp)
    movq -24(%rbp), %rax
    pushq %rax
    movq $8, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -32(%rbp)
    movq -8(%rbp), %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq -16(%rbp), %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq -24(%rbp), %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq -32(%rbp), %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $4, %rax
    pushq %rax
    popq %rdi
    call ade_isEven
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $7, %rax
    pushq %rax
    popq %rdi
    call ade_isEven
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $9, %rax
    pushq %rax
    popq %rdi
    call ade_square
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $1, %rax
    pushq %rax
    movq $10, %rax
    pushq %rax
    popq %rdi
    subq $8, %rsp
    call ade_isEven
    addq $8, %rsp
    pushq %rax
    popq %rsi
    popq %rdi
    call ade_both
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $1, %rax
    pushq %rax
    movq $0, %rax
    pushq %rax
    popq %rsi
    popq %rdi
    call ade_both
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    call ade_greet
    movq $3, %rax
    pushq %rax
    popq %rdi
    call ade_square
    pushq %rax
    movq $5, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setg %al
    movzbq %al, %rax
    movq %rax, -40(%rbp)
    movq -40(%rbp), %rax
    cmpq $0, %rax
    je .Lelse_1
    movq $1, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    jmp .Lend_1
.Lelse_1:
    movq $0, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
.Lend_1:
    movq $0, %rax
    movq %rax, -48(%rbp)
    movq $0, %rax
    movq %rax, -56(%rbp)
.Lwhile_2:
    movq -48(%rbp), %rax
    cmpq $0, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Lwend_2
    movq -56(%rbp), %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -56(%rbp)
    movq -56(%rbp), %rax
    pushq %rax
    movq $3, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Lelse_3
    movq $1, %rax
    movq %rax, -48(%rbp)
    jmp .Lend_3
.Lelse_3:
.Lend_3:
    jmp .Lwhile_2
.Lwend_2:
    movq -56(%rbp), %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq -16(%rbp), %rax
    cmpq $0, %rax
    sete %al
    movzbq %al, %rax
    movq %rax, -16(%rbp)
    movq -16(%rbp), %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $0, %rax
.Lret_main:
    movq %rbp, %rsp
    popq %rbp
    ret
.section .note.GNU-stack,"",@progbits
