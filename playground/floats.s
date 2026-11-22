.section .rodata
fmt: .string "%lld\n"
fmt_float: .string "%.15g\n"
fmt_bool: .string "%s\n"
str_true: .string "true"
str_false: .string "false"
.text
.globl main
ade_area:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rdi, -8(%rbp)
    movabsq $4614256650576692846, %rax
    pushq %rax
    movq -8(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    movq %rax, %xmm0
    movq %rcx, %xmm1
    mulsd %xmm1, %xmm0
    movq %xmm0, %rax
    pushq %rax
    movq -8(%rbp), %rax
    movq %rax, %rcx
    popq %rax
    movq %rax, %xmm0
    movq %rcx, %xmm1
    mulsd %xmm1, %xmm0
    movq %xmm0, %rax
    jmp .Lret_ade_area
    movq $0, %rax
.Lret_ade_area:
    movq %rbp, %rsp
    popq %rbp
    ret
ade_absf:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq %rdi, -8(%rbp)
    movq -8(%rbp), %rax
    pushq %rax
    movabsq $0, %rax
    movq %rax, %rcx
    popq %rax
    movq %rax, %xmm0
    movq %rcx, %xmm1
    ucomisd %xmm1, %xmm0
    setb %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Lelse_0
    movq -8(%rbp), %rax
    movabsq $0x8000000000000000, %rcx
    xorq %rcx, %rax
    jmp .Lret_ade_absf
    jmp .Lend_0
.Lelse_0:
.Lend_0:
    movq -8(%rbp), %rax
    jmp .Lret_ade_absf
    movq $0, %rax
.Lret_ade_absf:
    movq %rbp, %rsp
    popq %rbp
    ret
main:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
    movabsq $4609434218613702656, %rax
    movq %rax, %xmm0
    leaq fmt_float(%rip), %rdi
    movl $1, %eax
    call printf@PLT
    movabsq $4612248968380809216, %rax
    movabsq $0x8000000000000000, %rcx
    xorq %rcx, %rax
    movq %rax, %xmm0
    leaq fmt_float(%rip), %rdi
    movl $1, %eax
    call printf@PLT
    movabsq $4609434218613702656, %rax
    pushq %rax
    movabsq $4612248968380809216, %rax
    movq %rax, %rcx
    popq %rax
    movq %rax, %xmm0
    movq %rcx, %xmm1
    addsd %xmm1, %xmm0
    movq %xmm0, %rax
    movq %rax, %xmm0
    leaq fmt_float(%rip), %rdi
    movl $1, %eax
    call printf@PLT
    movabsq $4621819117588971520, %rax
    pushq %rax
    movabsq $4616189618054758400, %rax
    movq %rax, %rcx
    popq %rax
    movq %rax, %xmm0
    movq %rcx, %xmm1
    divsd %xmm1, %xmm0
    movq %xmm0, %rax
    movq %rax, %xmm0
    leaq fmt_float(%rip), %rdi
    movl $1, %eax
    call printf@PLT
    movabsq $4591870180066957722, %rax
    pushq %rax
    movabsq $4596373779694328218, %rax
    movq %rax, %rcx
    popq %rax
    movq %rax, %xmm0
    movq %rcx, %xmm1
    addsd %xmm1, %xmm0
    movq %xmm0, %rax
    movq %rax, %xmm0
    leaq fmt_float(%rip), %rdi
    movl $1, %eax
    call printf@PLT
    movabsq $4613937818241073152, %rax
    pushq %rax
    movabsq $4609434218613702656, %rax
    movabsq $0x8000000000000000, %rcx
    xorq %rcx, %rax
    movq %rax, %rcx
    popq %rax
    movq %rax, %xmm0
    movq %rcx, %xmm1
    mulsd %xmm1, %xmm0
    movq %xmm0, %rax
    movq %rax, %xmm0
    leaq fmt_float(%rip), %rdi
    movl $1, %eax
    call printf@PLT
    movabsq $4728057454355546112, %rax
    movq %rax, %xmm0
    leaq fmt_float(%rip), %rdi
    movl $1, %eax
    call printf@PLT
    movabsq $4607182418800017408, %rax
    pushq %rax
    movabsq $4613937818241073152, %rax
    movq %rax, %rcx
    popq %rax
    movq %rax, %xmm0
    movq %rcx, %xmm1
    divsd %xmm1, %xmm0
    movq %xmm0, %rax
    movq %rax, %xmm0
    leaq fmt_float(%rip), %rdi
    movl $1, %eax
    call printf@PLT
    movabsq $4612811918334230528, %rax
    pushq %rax
    movabsq $4609434218613702656, %rax
    movq %rax, %rcx
    popq %rax
    movq %rax, %xmm0
    movq %rcx, %xmm1
    ucomisd %xmm1, %xmm0
    seta %al
    movzbq %al, %rax
    cmpq $0, %rax
    leaq str_true(%rip), %rsi
    leaq str_false(%rip), %rcx
    cmove %rcx, %rsi
    leaq fmt_bool(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movabsq $4609434218613702656, %rax
    pushq %rax
    movabsq $4609434218613702656, %rax
    movq %rax, %rcx
    popq %rax
    movq %rax, %xmm0
    movq %rcx, %xmm1
    ucomisd %xmm1, %xmm0
    setbe %al
    movzbq %al, %rax
    cmpq $0, %rax
    leaq str_true(%rip), %rsi
    leaq str_false(%rip), %rcx
    cmove %rcx, %rsi
    leaq fmt_bool(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movabsq $4609434218613702656, %rax
    pushq %rax
    movabsq $4609434218613702656, %rax
    movq %rax, %rcx
    popq %rax
    movq %rax, %xmm0
    movq %rcx, %xmm1
    ucomisd %xmm1, %xmm0
    setb %al
    movzbq %al, %rax
    cmpq $0, %rax
    leaq str_true(%rip), %rsi
    leaq str_false(%rip), %rcx
    cmove %rcx, %rsi
    leaq fmt_bool(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movabsq $4613937818241073152, %rax
    pushq %rax
    movabsq $4613937818241073152, %rax
    movq %rax, %rcx
    popq %rax
    movq %rax, %xmm0
    movq %rcx, %xmm1
    ucomisd %xmm1, %xmm0
    sete %al
    movzbq %al, %rax
    cmpq $0, %rax
    leaq str_true(%rip), %rsi
    leaq str_false(%rip), %rcx
    cmove %rcx, %rsi
    leaq fmt_bool(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movabsq $4613937818241073152, %rax
    pushq %rax
    movabsq $4613937818241073152, %rax
    movq %rax, %rcx
    popq %rax
    movq %rax, %xmm0
    movq %rcx, %xmm1
    ucomisd %xmm1, %xmm0
    setne %al
    movzbq %al, %rax
    cmpq $0, %rax
    leaq str_true(%rip), %rsi
    leaq str_false(%rip), %rcx
    cmove %rcx, %rsi
    leaq fmt_bool(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movabsq $4616752568008179712, %rax
    movq %rax, -8(%rbp)
    movq -8(%rbp), %rax
    pushq %rax
    movabsq $4611686018427387904, %rax
    movq %rax, %rcx
    popq %rax
    movq %rax, %xmm0
    movq %rcx, %xmm1
    mulsd %xmm1, %xmm0
    movq %xmm0, %rax
    movq %rax, -16(%rbp)
    movq -16(%rbp), %rax
    movabsq $0x8000000000000000, %rcx
    xorq %rcx, %rax
    movq %rax, %xmm0
    leaq fmt_float(%rip), %rdi
    movl $1, %eax
    call printf@PLT
    movabsq $4611686018427387904, %rax
    pushq %rax
    popq %rdi
    call ade_area
    movq %rax, %xmm0
    leaq fmt_float(%rip), %rdi
    movl $1, %eax
    call printf@PLT
    movabsq $4612811918334230528, %rax
    movabsq $0x8000000000000000, %rcx
    xorq %rcx, %rax
    pushq %rax
    popq %rdi
    call ade_absf
    movq %rax, %xmm0
    leaq fmt_float(%rip), %rdi
    movl $1, %eax
    call printf@PLT
    movabsq $4608308318706860032, %rax
    pushq %rax
    popq %rdi
    call ade_absf
    movq %rax, %xmm0
    leaq fmt_float(%rip), %rdi
    movl $1, %eax
    call printf@PLT
    movabsq $0, %rax
    movq %rax, -24(%rbp)
    movq $0, %rax
    movq %rax, -32(%rbp)
.Lwhile_1:
    movq -32(%rbp), %rax
    pushq %rax
    movq $10, %rax
    movq %rax, %rcx
    popq %rax
    cmpq %rcx, %rax
    setl %al
    movzbq %al, %rax
    cmpq $0, %rax
    je .Lwend_1
    movq -24(%rbp), %rax
    pushq %rax
    movabsq $4602678819172646912, %rax
    movq %rax, %rcx
    popq %rax
    movq %rax, %xmm0
    movq %rcx, %xmm1
    addsd %xmm1, %xmm0
    movq %xmm0, %rax
    movq %rax, -24(%rbp)
    movq -32(%rbp), %rax
    pushq %rax
    movq $1, %rax
    movq %rax, %rcx
    popq %rax
    addq %rcx, %rax
    movq %rax, -32(%rbp)
    jmp .Lwhile_1
.Lwend_1:
    movq -24(%rbp), %rax
    movq %rax, %xmm0
    leaq fmt_float(%rip), %rdi
    movl $1, %eax
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
.section .rodata
.section .note.GNU-stack,"",@progbits
