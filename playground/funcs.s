.section .rodata
fmt: .string "%lld\n"
.text
.globl main
ade_five:
    pushq %rbp
    movq %rsp, %rbp
    movq $5, %rax
    jmp .Lret_ade_five
    movq $0, %rax
.Lret_ade_five:
    movq %rbp, %rsp
    popq %rbp
    ret
ade_add:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rdi, -8(%rbp)
    movq %rsi, -16(%rbp)
    movq -8(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    jmp .Lret_ade_add
    movq $0, %rax
.Lret_ade_add:
    movq %rbp, %rsp
    popq %rbp
    ret
ade_max:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rdi, -8(%rbp)
    movq %rsi, -16(%rbp)
    movq -8(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Lelse_0
    movq -8(%rbp), %rax
    jmp .Lret_ade_max
    jmp .Lend_0
.Lelse_0:
.Lend_0:
    movq -16(%rbp), %rax
    jmp .Lret_ade_max
    movq $0, %rax
.Lret_ade_max:
    movq %rbp, %rsp
    popq %rbp
    ret
ade_sumTo:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
    movq %rdi, -8(%rbp)
    movq $0, %rax
    movq %rax, -16(%rbp)
    movq $1, %rax
    movq %rax, -24(%rbp)
.Lwhile_1:
    movq -24(%rbp), %rax
    pushq %rax
    movq -8(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setle %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Lwend_1
    movq -16(%rbp), %rax
    pushq %rax
    movq -24(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -16(%rbp)
    movq -24(%rbp), %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -24(%rbp)
    jmp .Lwhile_1
.Lwend_1:
    movq -16(%rbp), %rax
    jmp .Lret_ade_sumTo
    movq $0, %rax
.Lret_ade_sumTo:
    movq %rbp, %rsp
    popq %rbp
    ret
ade_greet:
    pushq %rbp
    movq %rsp, %rbp
    movq $42, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $0, %rax
.Lret_ade_greet:
    movq %rbp, %rsp
    popq %rbp
    ret
ade_sixArgs:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp
    movq %rdi, -8(%rbp)
    movq %rsi, -16(%rbp)
    movq %rdx, -24(%rbp)
    movq %rcx, -32(%rbp)
    movq %r8, -40(%rbp)
    movq %r9, -48(%rbp)
    movq -8(%rbp), %rax
    pushq %rax
    movq -16(%rbp), %rax
    pushq %rax
    movq $10, %rax
    movq %rax, %rcx
    popq %rax
    imulq %rcx, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    pushq %rax
    movq -24(%rbp), %rax
    pushq %rax
    movq $100, %rax
    movq %rax, %rcx
    popq %rax
    imulq %rcx, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    pushq %rax
    movq -32(%rbp), %rax
    pushq %rax
    movq $1000, %rax
    movq %rax, %rcx
    popq %rax
    imulq %rcx, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    pushq %rax
    movq -40(%rbp), %rax
    pushq %rax
    movq $10000, %rax
    movq %rax, %rcx
    popq %rax
    imulq %rcx, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq $100000, %rax
    movq %rax, %rcx
    popq %rax
    imulq %rcx, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    jmp .Lret_ade_sixArgs
    movq $0, %rax
.Lret_ade_sixArgs:
    movq %rbp, %rsp
    popq %rbp
    ret
ade_fact:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rdi, -8(%rbp)
    movq -8(%rbp), %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setle %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Lelse_2
    movq $1, %rax
    jmp .Lret_ade_fact
    jmp .Lend_2
.Lelse_2:
.Lend_2:
    movq -8(%rbp), %rax
    pushq %rax
    movq -8(%rbp), %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    subq %rcx, %rax
    pushq %rax
    popq %rdi
    subq $8, %rsp
    call ade_fact
    addq $8, %rsp
    movq %rax, %rcx
    popq %rax
    imulq %rcx, %rax
    jmp .Lret_ade_fact
    movq $0, %rax
.Lret_ade_fact:
    movq %rbp, %rsp
    popq %rbp
    ret
ade_fib:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rdi, -8(%rbp)
    movq -8(%rbp), %rax
    pushq %rax
    movq $2, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Lelse_3
    movq -8(%rbp), %rax
    jmp .Lret_ade_fib
    jmp .Lend_3
.Lelse_3:
.Lend_3:
    movq -8(%rbp), %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    subq %rcx, %rax
    pushq %rax
    popq %rdi
    call ade_fib
    pushq %rax
    movq -8(%rbp), %rax
    pushq %rax
    movq $2, %rax
    movq %rax, %rcx
    popq %rax
    subq %rcx, %rax
    pushq %rax
    popq %rdi
    subq $8, %rsp
    call ade_fib
    addq $8, %rsp
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    jmp .Lret_ade_fib
    movq $0, %rax
.Lret_ade_fib:
    movq %rbp, %rsp
    popq %rbp
    ret
ade_later:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rdi, -8(%rbp)
    movq -8(%rbp), %rax
    pushq %rax
    movq $2, %rax
    movq %rax, %rcx
    popq %rax
    imulq %rcx, %rax
    jmp .Lret_ade_later
    movq $0, %rax
.Lret_ade_later:
    movq %rbp, %rsp
    popq %rbp
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    call ade_five
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $2, %rax
    pushq %rax
    movq $3, %rax
    pushq %rax
    popq %rsi
    popq %rdi
    call ade_add
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $7, %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    popq %rsi
    popq %rdi
    call ade_max
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $100, %rax
    pushq %rax
    popq %rdi
    call ade_sumTo
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    call ade_greet
    movq $1, %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq $3, %rax
    pushq %rax
    movq $4, %rax
    pushq %rax
    movq $5, %rax
    pushq %rax
    movq $6, %rax
    pushq %rax
    popq %r9
    popq %r8
    popq %rcx
    popq %rdx
    popq %rsi
    popq %rdi
    call ade_sixArgs
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $1, %rax
    pushq %rax
    movq $10, %rax
    pushq %rax
    movq $20, %rax
    pushq %rax
    popq %rsi
    popq %rdi
    subq $8, %rsp
    call ade_add
    addq $8, %rsp
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $1, %rax
    pushq %rax
    movq $2, %rax
    pushq %rax
    movq $3, %rax
    pushq %rax
    popq %rsi
    popq %rdi
    subq $8, %rsp
    call ade_add
    addq $8, %rsp
    pushq %rax
    popq %rsi
    popq %rdi
    call ade_add
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $5, %rax
    movq %rax, -8(%rbp)
    movq -8(%rbp), %rax
    pushq %rax
    popq %rdi
    call ade_fact
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $20, %rax
    pushq %rax
    popq %rdi
    call ade_fib
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $7, %rax
    pushq %rax
    popq %rdi
    call ade_later
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
