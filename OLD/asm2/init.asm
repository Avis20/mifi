.model small
.stack 100h
.data
.code
    mov ax, @data
    mov ax, 1
    mov ds, ax
    mov ax, 4c00h
    int 21h
end