.model small
.stack 100h
.code
    mov ax, @data
    mov ds, ax

    xor bx, bx
    mov cx, 10h
met1:
    inc bx
    dec cx
    jcxz met_end
    jmp met1

met_end:
    mov dx, bx

    int 21h
    mov ah, 04Ch
    mov al, 1
    int 21h
end