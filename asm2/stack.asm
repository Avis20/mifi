.model small
.stack 100h
.data
    hello_str db 'Hello'
.code
    mov ax, @data
    mov ds, ax
    mov ah, 04Ch
    mov al, 1
    push ax     ; Добавляем в стек
    mov bx, 1
    mov cx, 21h
    mov dx, offset hello_str
    mov ah, 40h
    int 21h
    pop ax      ; Забираем из стека
    int 21h
end