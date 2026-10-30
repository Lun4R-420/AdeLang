.section .rodata
fmt: .string "%lld\n"
.text
.globl main
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $96, %rsp
    movq $1, %rax
    movq %rax, -8(%rbp)
    movq $0, %rax
    movq %rax, -16(%rbp)
.Lwhile_0:
    movq -8(%rbp), %rax
    pushq %rax
    movq $10, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setle %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Lwend_0
    movq -16(%rbp), %rax
    pushq %rax
    movq -8(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -16(%rbp)
    movq -8(%rbp), %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -8(%rbp)
    jmp .Lwhile_0
.Lwend_0:
    movq -16(%rbp), %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $3, %rax
    movq %rax, -24(%rbp)
.Lwhile_1:
    movq -24(%rbp), %rax
    pushq %rax
    movq $0, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setg %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Lwend_1
    movq -24(%rbp), %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq -24(%rbp), %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    subq %rcx, %rax
    movq %rax, -24(%rbp)
    jmp .Lwhile_1
.Lwend_1:
.Lwhile_2:
    movq $0, %rax
    cmpq $0, %rax
    je .Lwend_2
    movq $999, %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    jmp .Lwhile_2
.Lwend_2:
    movq $0, %rax
    movq %rax, -32(%rbp)
    movq $0, %rax
    movq %rax, -40(%rbp)
.Lwhile_3:
    movq -40(%rbp), %rax
    pushq %rax
    movq $10, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Lwend_3
    movq -40(%rbp), %rax
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
    je .Lelse_4
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -32(%rbp)
    jmp .Lend_4
.Lelse_4:
.Lend_4:
    movq -40(%rbp), %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -40(%rbp)
    jmp .Lwhile_3
.Lwend_3:
    movq -32(%rbp), %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $1, %rax
    movq %rax, -48(%rbp)
    movq $0, %rax
    movq %rax, -56(%rbp)
.Lwhile_5:
    movq -48(%rbp), %rax
    pushq %rax
    movq $3, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setle %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Lwend_5
    movq $1, %rax
    movq %rax, -64(%rbp)
.Lwhile_6:
    movq -64(%rbp), %rax
    pushq %rax
    movq $3, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setle %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Lwend_6
    movq -56(%rbp), %rax
    pushq %rax
    movq -48(%rbp), %rax
    pushq %rax
    movq -64(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    imulq %rcx, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -56(%rbp)
    movq -64(%rbp), %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -64(%rbp)
    jmp .Lwhile_6
.Lwend_6:
    movq -48(%rbp), %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -48(%rbp)
    jmp .Lwhile_5
.Lwend_5:
    movq -56(%rbp), %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $0, %rax
    movq %rax, -72(%rbp)
    movq $1, %rax
    movq %rax, -80(%rbp)
    movq $0, %rax
    movq %rax, -88(%rbp)
.Lwhile_7:
    movq -88(%rbp), %rax
    pushq %rax
    movq $10, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Lwend_7
    movq -72(%rbp), %rax
    pushq %rax
    movq -80(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -96(%rbp)
    movq -80(%rbp), %rax
    movq %rax, -72(%rbp)
    movq -96(%rbp), %rax
    movq %rax, -80(%rbp)
    movq -88(%rbp), %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -88(%rbp)
    jmp .Lwhile_7
.Lwend_7:
    movq -72(%rbp), %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    movq %rbp, %rsp
    popq %rbp
    ret
.section .note.GNU-stack,"",@progbits
