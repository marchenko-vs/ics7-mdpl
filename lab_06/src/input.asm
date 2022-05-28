PUBLIC NUMBER
PUBLIC INCOMMAND
PUBLIC INDECUNSGN
;
DATASEG SEGMENT PARA PUBLIC 'DATA'
    NUMBER DW 0
    INMSG DB 'Enter unsigned octal number ([0; 177777]): $'
DATASEG ENDS
;
CODESEG SEGMENT PARA PUBLIC 'CODE'
    ASSUME CS:CODESEG, DS:DATASEG

    INCOMMAND PROC NEAR
        MOV AH, 1
        INT 21H
        SUB AL, '0'
        MOV CL, 2
        MUL CL
        MOV SI, AX
        RET
        INCOMMAND ENDP

    INDECUNSGN PROC NEAR
        MOV AH, 9
        MOV DX, OFFSET INMSG
        INT 21H

        MOV BX, 0

        INSYMB:
            MOV AH, 1
            INT 21H

            CMP AL, 13
            JE ENDINP

            MOV CL, AL
            MOV CH, 0
            SUB CL, '0'

            MOV AX, 8
            MUL BX
            MOV BX, AX

            ADD BX, CX
            JMP INSYMB

        ENDINP:
            MOV NUMBER, BX
            RET
            INDECUNSGN ENDP
CODESEG ENDS
END
