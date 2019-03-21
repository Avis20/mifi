.model small
.stack 100h
.data
    a db 10
    b db 2
    c db 6
    d db 5
    e db 2
.code
    mov AX, @data
    mov DS, AX

    mov AL, b   ; AL := b
    cbw         ; AX := b
    mov BX, AX  ; BX := AX
    imul b      ; AX := b^2
    mov BL, 2   ; BL := 2
    imul BX     ; AX := 2*b^2
    mov BL, a   ; BX := a
    cbw         ; BX := a
    sbb BX, AX  ; BX := a - 2*b^2
    push BX     ; stack = AX

    mov AL, c   ; AL := c
    cbw         ; AX := c
    mov BX, AX  ; BX := AX
    imul c      ; AX := c^2
    mov BL, 2   ; BL := 2
    imul BX     ; AX := (c^2)*2
    mov BL, d   ; BX := d
    sbb AX, BX  ; AX := AX - d
    pop BX      ; BX := 2*(a-2*b^2)
    imul BX     ; AX := AX*BX
    push AX

    mov AL, e   ; AL := e
    cbw         ; AX := e
    mov BX, AX  ; BX := AX
    imul e      ; AX := e^2
    mov BL, a   ; BL := a
    cbw         ; BX := a
    adc AX, BX  ; AX := a+e^2
    mov BL, 4   ; BL := 4
    imul BX     ; AX := AX*4

    pop BX
    idiv BX     ; AX := AX/BX

    mov AX, 4c00h
    int 21h
end