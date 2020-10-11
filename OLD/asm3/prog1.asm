.model tiny
.stack 256
.data
    hello_str db 'Hello world'
.code
    mov ax, @data   ; поместить в AX смещение размером @data
    mov ds, ax      ; записываем смещение в ds

    mov bx, 1       ; поместить в bx 1
    mov cx, 21      ; поместить в cx 21
    mov dx, offset hello_str ; поместить в dx смещение строки

    mov ah, 40h     ; вывод строки
    int 21h         ; системное прерываение
    mov ah, 04Ch    ; завершение программы
    mov al, 1h       ; веруть код завершения 1
    int 21h         ; системное прерываение
end