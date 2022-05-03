section .text

global my_strcpy

my_strcpy:
    mov rcx, rdx
    cmp rdi, rsi
    jne not_equal
    jmp exit

not_equal:
    cmp rdi, rsi
    jl simple_copy
    mov rbx, rdi
    sub rbx, rsi
    cmp rbx, rcx
    jge simple_copy

overlapping_copy:
    add rdi, rcx
    add rsi, rcx
    dec rsi
    dec rdi
    std ; set DF flag

simple_copy:
    rep movsb
    cld ; reset DF flag

exit:
    ret

