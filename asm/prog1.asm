.model small
.stack 100h
.data
    a db 127
    b db 3
    c db 127
    d db 0
    e db 0
    two db 2
    four db 4
.code
    mov AX, @data
    mov DS, AX

    mov AL, e   ; AL = e
    mov AH, 0   ; AH = 0
    imul AX     ; AX = e^2

    mov BL, a   ; BL = a
    mov BH, 0   ; BH = 0
    adc AX, BX  ; AX = a + e^2
    imul four   ; AX = (a + e^2) * 4
    push DX
    push AX

    mov AL, b   ; AL = b
    mov AH, 0   ; AH = 0
    cbw         ; AX = b
    imul AX     ; AX = b^2
    imul two    ; AX = 2*b^2

    mov BL, a   ; BL = a
    mov BH, 0   ; BH = 0
    adc AX, BX  ; AX = a + 2*b^2
    mov CX, AX  ; CX = AX

    mov AL, c   ; AL = c
    mov AH, 0   ; AH = 0
    imul AX     ; AX = c^2

    mov BL, d   ; BL = d
    mov BH, 0   ; BH = 0
    sbb AX, BX  ; AX = c^2 - d
    
    imul CX     ; DX:AX = (a + 2*b^2)(c^2 - d)

    pop BX      ; old AX
    pop CX      ; old DX

    idiv BX     ; DX
    idiv CX     ; AX := AX/BX

    mov AX, 4c00h
    int 21h
end