EXTRN INCOMMAND: NEAR
EXTRN INDECUNSGN: NEAR
EXTRN OUTUHEX: NEAR
EXTRN OUTSBIN: NEAR
EXTRN CRLF: NEAR
;
STACKSEG SEGMENT PARA STACK 'STACK'
    DB 200H DUP(0)
STACKSEG ENDS
;
DATASEG SEGMENT PARA PUBLIC 'DATA'
    MENU DB 'Menu:', 13, 10
        DB '1. Input unsigned octal number.', 13, 10
        DB '2. Convert to unsigned hexadecimal number.', 13, 10
        DB '3. Convert to signed binary number.', 13, 10
        DB '0. Exit program.', 13, 10
        DB 'Choose option: $'
    ACTIONS DW EXIT, INDECUNSGN, OUTUHEX, OUTSBIN
DATASEG ENDS
;
CODESEG SEGMENT PARA PUBLIC 'CODE'
    ASSUME CS:CODESEG, DS:DATASEG, SS:STACKSEG

    OUTMENU PROC NEAR
        MOV AH, 9
        MOV DX, OFFSET MENU
        INT 21H
        RET
        OUTMENU ENDP

    EXIT PROC NEAR
        MOV AX, 4C00H
        INT 21H
        EXIT ENDP

    MAIN:
        MOV AX, DATASEG
        MOV DS, AX

        MAINLOOP:
            CALL CRLF
            CALL OUTMENU
            CALL INCOMMAND
            CALL CRLF
            CALL ACTIONS[SI]
            JMP MAINLOOP
CODESEG ENDS
END MAIN
