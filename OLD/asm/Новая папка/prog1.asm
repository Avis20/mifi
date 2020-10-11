.model small
.stack 100h
.data
    a db 127
    b db 3
    c db 127
    d db 2
    e db 3
.code
    mov AX, @data
    mov DS, AX

    mov AL, b   ; AL := b
    cbw         ; AX := b
    mov BX, AX  ; BX := AX
    imul b      ; AX := b^2
    mov BL, 4   ; BL := 4
    mov BH, 0
    imul BX     ; AX := 4*b^2
    mov DX, AX
    mov AL, a   ; BX := a
    cbw         ; BX := a
    mov CL, 2
    mov CH, 0
    imul CX
    sbb AX, DX  ; BX := a - 2*b^2
    mov DX, AX

    mov AL, c   ; AL := c
    cbw         ; AX := c
    mov BX, AX  ; BX := AX
    imul c      ; AX := c^2
    mov BL, 2   ; BL := 2
    mov BH, 0
    imul BX     ; AX := (c^2)*2
    mov BL, d   ; BX := d
    sbb AX, BX  ; AX := AX - d
    ; pop  BX     ; BX := 2*(a-2*b^2)
    cwd
    imul DX     ; AX := AX*DX
    ; push AX

    mov AL, e   ; AL := e
    cbw         ; AX := e
    mov BX, AX  ; BX := AX
    imul e      ; AX := e^2
    mov BL, a   ; BL := a
    cbw         ; BX := a
    adc AX, BX  ; AX := a+e^2
    mov BL, 4   ; BL := 4
    mov BH, 0
    imul BX     ; AX := AX*4

    pop BX
    idiv BX     ; AX := AX/BX

    mov AX, 4c00h
    int 21h
end
