.MODEL TINY
.CODE
.186

ORG 100H

MAIN:
    JMP INITIALIZATION

    CURRENT DB 0
    IS_INIT DB 'y'
    SPEED DB 01FH
    OLD_BREAKING DD ?

USER_INTERRUPTION:
    PUSHA ; сохраняет в стеке содержимое восьми 16-битных РОН
    PUSH ES
    PUSH DS

    MOV AH, 02H    
    INT 1AH

    CMP DH, CURRENT
    MOV CURRENT, DH
    JE END_LOOP

    MOV AL, 0F3H
    OUT 60H, AL ; инструкция OUT выводит данные из регистра AL или AX в порт ввода-вывода
    MOV AL, SPEED
    OUT 60H, AL

    DEC SPEED

    TEST SPEED, 01FH
    JZ RESET_SPEED
    JMP END_LOOP

    RESET_SPEED:
        MOV SPEED, 01FH

    END_LOOP:
        POP DS
        POP ES
        POPA

        JMP CS:OLD_BREAKING

INITIALIZATION:    
    MOV AX, 3508H ; AH = 35H, AL = номер прерывания
    INT 21H                           

    CMP ES:IS_INIT, 'y'
    JE EXIT

    MOV WORD PTR OLD_BREAKING, BX ; запоминаем адрес старого обработчика
    MOV WORD PTR OLD_BREAKING + 2, ES ; запоминаем адрес регистра ES

    MOV AX, 2508H                      
    MOV DX, OFFSET USER_INTERRUPTION ; устанавливаем свой обработчик 08 вместо обработчика по умолчанию
    INT 21H                             

    MOV DX, OFFSET INITIALIZATION
    INT 27H

EXIT:
    PUSHA
    PUSH ES
    PUSH DS

    MOV AX, 2508H
    MOV DX, WORD PTR ES:OLD_BREAKING
    MOV DS, WORD PTR ES:OLD_BREAKING + 2
    INT 21H

    MOV AL, 0F3H
    OUT 60H, AL
    MOV AL, 0
    OUT 60H, AL

    POP DS
    POP ES
    POPA

    MOV AH, 49H
    INT 21H

    MOV AX, 4C00H
    INT 21H

END MAIN
