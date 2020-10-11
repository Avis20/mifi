.model small
.stack 100h
.data
    a db 127
    b db 2
    d db 5
.code
    mov AX, @data
    mov DS, AX

    mov AL, a   ; AL := a
    mov AH, 0   ; AH := 0
    cbw         ; AX := a
    imul AX     ; AX := a^2
    imul AX     ; DX:AX := a^3
    mov CX, DX  ; CX := DX
    mov BX, AX  ; BX := AX

    mov AL, a   ; AL := a
    mov AH, 0   ; AH := 0
    cbw         ; AX := a
    imul AX     ; AX := a^2

    adc AX, BX  ; AX := a^5

    mov AX, 4c00h
    int 21h
end