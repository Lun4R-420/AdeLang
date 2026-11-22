.section .rodata
fmt: .string "%lld\n"
fmt_float: .string "%.15g\n"
fmt_bool: .string "%s\n"
str_true: .string "true"
str_false: .string "false"
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
    cmpq $0, %rax
    leaq str_true(%rip), %rsi
    leaq str_false(%rip), %rcx
    cmove %rcx, %rsi
    leaq fmt_bool(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $0, %rax
.Lret_main:
    movq %rbp, %rsp
    popq %rbp
    ret
.section .rodata
.section .note.GNU-stack,"",@progbits
