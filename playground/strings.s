.section .rodata
fmt: .string "%lld\n"
fmt_float: .string "%.15g\n"
fmt_bool: .string "%s\n"
str_true: .string "true"
str_false: .string "false"
.text
.globl main
ade_greet:
    pushq %rbp
    movq %rsp, %rbp
    leaq .Lstr_0(%rip), %rax
    jmp .Lret_ade_greet
    movq $0, %rax
.Lret_ade_greet:
    movq %rbp, %rsp
    popq %rbp
    ret
ade_pick:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rdi, -8(%rbp)
    movq -8(%rbp), %rax
    cmpq $0, %rax
    je .Lelse_0
    leaq .Lstr_1(%rip), %rax
    jmp .Lret_ade_pick
    jmp .Lend_0
.Lelse_0:
.Lend_0:
    leaq .Lstr_2(%rip), %rax
    jmp .Lret_ade_pick
    movq $0, %rax
.Lret_ade_pick:
    movq %rbp, %rsp
    popq %rbp
    ret
ade_show:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rdi, -8(%rbp)
    movq %rsi, -16(%rbp)
    movq -8(%rbp), %rax
    movq %rax, %rsi
    leaq fmt_bool(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq -16(%rbp), %rax
    movq %rax, %rsi
    leaq fmt(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $0, %rax
.Lret_ade_show:
    movq %rbp, %rsp
    popq %rbp
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    leaq .Lstr_3(%rip), %rax
    movq %rax, %rsi
    leaq fmt_bool(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    leaq .Lstr_4(%rip), %rax
    movq %rax, -8(%rbp)
    movq -8(%rbp), %rax
    movq %rax, %rsi
    leaq fmt_bool(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    leaq .Lstr_5(%rip), %rax
    movq %rax, -16(%rbp)
    leaq .Lstr_6(%rip), %rax
    movq %rax, -16(%rbp)
    movq -16(%rbp), %rax
    movq %rax, %rsi
    leaq fmt_bool(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    call ade_greet
    movq %rax, %rsi
    leaq fmt_bool(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $1, %rax
    pushq %rax
    popq %rdi
    call ade_pick
    movq %rax, %rsi
    leaq fmt_bool(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $0, %rax
    pushq %rax
    popq %rdi
    call ade_pick
    movq %rax, %rsi
    leaq fmt_bool(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    leaq .Lstr_7(%rip), %rax
    pushq %rax
    movq $42, %rax
    pushq %rax
    popq %rsi
    popq %rdi
    call ade_show
    leaq .Lstr_8(%rip), %rax
    movq %rax, %rsi
    leaq fmt_bool(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    leaq .Lstr_9(%rip), %rax
    movq %rax, %rsi
    leaq fmt_bool(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq $0, %rax
.Lret_main:
    movq %rbp, %rsp
    popq %rbp
    ret
.section .rodata
.Lstr_0: .string "hey"
.Lstr_1: .string "yes"
.Lstr_2: .string "no"
.Lstr_3: .string "hello"
.Lstr_4: .string "hi"
.Lstr_5: .string "first"
.Lstr_6: .string "second"
.Lstr_7: .string "value"
.Lstr_8: .string "tab\tseparated"
.Lstr_9: .string "two\nlines"
.section .note.GNU-stack,"",@progbits
