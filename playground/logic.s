.section .rodata
fmt: .string "%lld\n"
.text
.globl main
ade_sideEffect:
    pushq %rbp
    movq %rsp, %rbp
    movq $999, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $1, %rax
    jmp .Lret_ade_sideEffect
    movq $0, %rax
.Lret_ade_sideEffect:
    movq %rbp, %rsp
    popq %rbp
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp
    movq $1, %rax
    cmpq $0, %rax
    je .Land_end_0
    movq $1, %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
.Land_end_0:
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $1, %rax
    cmpq $0, %rax
    je .Land_end_1
    movq $0, %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
.Land_end_1:
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $0, %rax
    cmpq $0, %rax
    jne .Lor_true_2
    movq $1, %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
    jmp .Lor_end_2
.Lor_true_2:
    movq $1, %rax
.Lor_end_2:
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $0, %rax
    cmpq $0, %rax
    jne .Lor_true_3
    movq $0, %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
    jmp .Lor_end_3
.Lor_true_3:
    movq $1, %rax
.Lor_end_3:
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $3, %rax
    pushq %rax
    movq $2, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Land_end_4
    movq $2, %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setg %al
    movzbq %al, %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
.Land_end_4:
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $1, %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    pushq %rax
    movq $2, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    jne .Lor_true_5
    movq $5, %rax
    pushq %rax
    movq $9, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setg %al
    movzbq %al, %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
    jmp .Lor_end_5
.Lor_true_5:
    movq $1, %rax
.Lor_end_5:
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $0, %rax
    cmpq $0, %rax
    je .Land_end_7
    movq $1, %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
.Land_end_7:
    cmpq $0, %rax
    jne .Lor_true_6
    movq $1, %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
    jmp .Lor_end_6
.Lor_true_6:
    movq $1, %rax
.Lor_end_6:
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $1, %rax
    cmpq $0, %rax
    jne .Lor_true_8
    movq $0, %rax
    cmpq $0, %rax
    je .Land_end_9
    movq $0, %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
.Land_end_9:
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
    jmp .Lor_end_8
.Lor_true_8:
    movq $1, %rax
.Lor_end_8:
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $1, %rax
    cmpq $0, %rax
    je .Land_end_10
    movq $0, %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
.Land_end_10:
    cmpq $0, %rax
    sete %al
    movzbq %al, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $0, %rax
    movq %rax, -8(%rbp)
    movq -8(%rbp), %rax
    pushq %rax
    movq $0, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Land_end_11
    movq $10, %rax
    pushq %rax
    movq -8(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    cqto
    idivq %rcx
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setg %al
    movzbq %al, %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
.Land_end_11:
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq -8(%rbp), %rax
    pushq %rax
    movq $0, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    jne .Lor_true_12
    movq $10, %rax
    pushq %rax
    movq -8(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    cqto
    idivq %rcx
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setg %al
    movzbq %al, %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
    jmp .Lor_end_12
.Lor_true_12:
    movq $1, %rax
.Lor_end_12:
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $0, %rax
    cmpq $0, %rax
    je .Land_end_13
    call ade_sideEffect
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
.Land_end_13:
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $1, %rax
    cmpq $0, %rax
    jne .Lor_true_14
    call ade_sideEffect
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
    jmp .Lor_end_14
.Lor_true_14:
    movq $1, %rax
.Lor_end_14:
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $1, %rax
    cmpq $0, %rax
    je .Land_end_15
    call ade_sideEffect
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
.Land_end_15:
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $5, %rax
    movq %rax, -16(%rbp)
    movq $10, %rax
    movq %rax, -24(%rbp)
    movq -16(%rbp), %rax
    pushq %rax
    movq -24(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Land_end_17
    movq -24(%rbp), %rax
    pushq %rax
    movq $20, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setl %al
    movzbq %al, %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
.Land_end_17:
    cmpq $0, %rax
    je .Lelse_16
    movq $100, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    jmp .Lend_16
.Lelse_16:
.Lend_16:
    movq -16(%rbp), %rax
    pushq %rax
    movq -24(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    jne .Lor_true_19
    movq -24(%rbp), %rax
    pushq %rax
    movq $10, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    sete %al
    movzbq %al, %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
    jmp .Lor_end_19
.Lor_true_19:
    movq $1, %rax
.Lor_end_19:
    cmpq $0, %rax
    je .Lelse_18
    movq $200, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    jmp .Lend_18
.Lelse_18:
.Lend_18:
    movq $0, %rax
    movq %rax, -32(%rbp)
    movq $0, %rax
    movq %rax, -40(%rbp)
.Lwhile_20:
    movq -32(%rbp), %rax
    pushq %rax
    movq $20, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Land_end_21
    movq -40(%rbp), %rax
    pushq %rax
    movq $3, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setl %al
    movzbq %al, %rax
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
.Land_end_21:
    cmpq $0, %rax
    je .Lwend_20
    movq -32(%rbp), %rax
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
    cmpq $0, %rax
    jne .Lor_true_23
    movq -32(%rbp), %rax
    pushq %rax
    movq $5, %rax
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
    movq $0, %rcx
    cmpq %rcx, %rax
    setne %al
    movzbq %al, %rax
    jmp .Lor_end_23
.Lor_true_23:
    movq $1, %rax
.Lor_end_23:
    cmpq $0, %rax
    je .Lelse_22
    movq -40(%rbp), %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -40(%rbp)
    jmp .Lend_22
.Lelse_22:
.Lend_22:
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -32(%rbp)
    jmp .Lwhile_20
.Lwend_20:
    movq -40(%rbp), %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq -32(%rbp), %rax
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
