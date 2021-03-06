EXTRN NUMBER: WORD
;
PUBLIC UHEX
PUBLIC SBIN
PUBLIC SIGN
PUBLIC TOUHEX
;
DATASEG SEGMENT PARA PUBLIC 'DATA'
    MASK16 DW 15
    MASK2 DW 1
    UHEX DB 4 DUP('0'), '$'
    SBIN DB 16 DUP('0'), '$'
    SIGN DB ' '
DATASEG ENDS
;
CODESEG SEGMENT PARA PUBLIC 'CODE'
    ASSUME CS:CODESEG, DS:DATASEG

    TOUHEX PROC NEAR
        MOV AX, NUMBER
        MOV BX, 3

        GETHEX:
            MOV DX, AX
            AND DX, MASK16
            CMP DL, 10
            JB ISDIGIT
            ADD DL, 7

            ISDIGIT:
                ADD DL, '0'
                MOV UHEX[BX], DL
                MOV CL, 4
                SAR AX, CL
                DEC BX
                CMP BX, -1
                JNE GETHEX
            RET
            TOUHEX ENDP

    TOSBIN PROC NEAR
        MOV CL, ' '
        MOV SIGN, CL
        MOV AX, NUMBER
        CMP AX, 32767
        JBE NOTOVERFLOW
        SUB AX, 1
        NOT AX
        MOV CL, '-'
        MOV SIGN, CL
        NOTOVERFLOW:
        MOV BX, 15
        
        GETBIN:
            MOV DX, AX
            AND DX, MASK2
            ADD DL, '0'
            MOV SBIN[BX], DL
            MOV CL, 1
            SAR AX, CL
            DEC BX
            CMP BX, -1
            JNE GETBIN
        RET
        TOSBIN ENDP
CODESEG ENDS
END
