.model small
.stack 100h
.code
    mov ax, @data
    mov ds, ax

    xor bx, bx
    mov cx, 10
met1:
    inc bx
    loop met1

    mov ax, 4c00h
    int 21h
end