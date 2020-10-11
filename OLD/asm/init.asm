.model small
.stack 100h
.data
; <-- your data
.code
    mov AX, @data
    mov DS, AX
; <-- your code
    mov AX, 4c00h
    int 21h
end