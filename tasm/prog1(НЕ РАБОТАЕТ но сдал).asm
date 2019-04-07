.model small
.stack 100h
.data
    a db 20
    b db 4
    c db 127
    d db 0
    e db 2
    two db 2
    four db 4
.code
    mov AX, @data
    mov DS, AX
    
    mov AL, e   ; AL = e
    cbw
    imul AX     ; AX = e^2
    mov BX, AX  ; BX = AX
 
    mov AL, a
    cbw
    adc AX, BX  ; AX = a + e^2
    imul four   ; AX = (a + e^2) * 4
    mov CX, AX  ; CX = AX
 
    mov AL, b   ; AL = b
    cbw         ; AX = b
    imul AX     ; AX = b^2
    imul two    ; AX = 2*b^2
 
    mov BX, AX  ; BX = AX
    mov AL, a   ; AL = a
    cbw
    sbb AX, BX  ; AX = a - 2*b^2
    mov DX, AX  ; DX = AX

    mov AL, c   ; AL = c
    cbw
    imul AX     ; AX = c^2

    mov BX, AX  ; BX = AX
    cbw
    mov AL, d   ; AL = d
    sbb AX, BX  ; AX = c^2 - d
    
    imul DX     ; DX:AX = (a + 2*b^2)(c^2 - d)

    idiv CX     ; AX = DX/CX

    mov AX, 4c00h
    int 21h
end