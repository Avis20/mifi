.model small
.stack 10h
.data
    hello db 'hello world $'
.code
    mov ax, @data
    mov ds, ax

    mov dx, offset hello
    mov ah, 09h

    int 21h
    mov ah, 04Ch
    mov al, 1
    int 21h
end