.model small
.stack 100h
.data
    x dw 03F01h ; 127^2
    a dw 0Ah   ; 1010
    ;b dw ‭1111111‬b ; 127^2
.code
    mov AX, @data
    mov DS, AX


    mov AX, a
    sar AX, 1       ; C = 1 byte
    xor BX, BX
    jc met_1        ; 1 byte = 1
    jnc met_2
    jmp end_p

met_1:
    mov BX, 1
    ; sal AX, 1
    jmp end_p

met_2:
    sar AX, 1         ; C = 2 byte
    sal AX, 1

    ; xor BX, BX      ; BX = null
    ; mov BX, CX      ; BX = 1 byte

    ; mov AX, a
    ; sar AX, 1       ; CX = 2 byte

end_p:

    mov AX, 4c00h
    int 21h
end