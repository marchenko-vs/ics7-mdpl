StackSegment SEGMENT PARA STACK 'STACK'
    DB 100 DUP(0)
StackSegment ENDS

DataSegment SEGMENT PARA 'DATA'
    RowsMsg DB 'Enter the number of rows: $'
    ColumnsMsg DB 'Enter the number of columns: $'
    ElementsMsg DB 'Enter the elements of the matrix:$'
    ResultMsg DB 'Result:$'

	DECR DB 0
    Rows DB 0
    Columns DB 0

    Matrix DB 9 * 9 DUP(0)

DataSegment ENDS

CodeSegment SEGMENT PARA 'CODE'
    ASSUME CS:CodeSegment, DS:DataSegment, ES:DataSegment, SS:StackSegment

	PrintCRLF:
		MOV AH, 2
		MOV DL, 13
		INT 21H
		MOV DL, 10
		INT 21H
		RET

	PrintSpace:
		MOV AH, 2
		MOV DL, ' '
		INT 21H
		RET

	MAIN:
		MOV AX, DataSegment 
		MOV DS, AX

		MOV AH, 9
		MOV DX, OFFSET RowsMsg
		INT 21H

		MOV AH, 1 ; считывание количества строк
		INT 21H
		MOV Rows, AL
		SUB Rows, '0'
		CALL PrintCRLF

		MOV AH, 9
		MOV DX, OFFSET ColumnsMsg
		INT 21H

		MOV AH, 1 ; считывание количества столбцов
		INT 21H
		MOV Columns, AL
		SUB Columns, '0'
		CALL PrintCRLF

		MOV AH, 9
		MOV DX, OFFSET ElementsMsg
		INT 21H
		CALL PrintCRLF

		; ввод элементов матрицы

		MOV SI, 0 ; SI - регистр, который отвечает за строки
		MOV CL, Rows ; CL - регистр, отвечающий за цикл, сейчас количество строк

		InRowLoop:
			MOV DECR, CL ; сохранение регистра CL, который отвечает за проход по строкам
			MOV BX, 0 ; BX - регистр, который отвечает за столбцы
			MOV CL, Columns ; установка регистра для прохода по строкам

			InColumLoop:
				MOV AH, 1
				INT 21H

				MOV Matrix[SI][BX], AL ; раскроется в SI + BX (номер строки + номер столбца)
				INC BX ; увеличение номера столбца на 1

				CALL PrintSpace

				LOOP InColumLoop	


			CALL PrintCRLF
	
			MOV CL, DECR ; восстановление значения регистра
			ADD SI, 9 ; так как столбцов выделено 9, то надо увеличить значение SI на этот сдвиг
			
			LOOP InRowLoop
		
		MOV BX, 1 
		MOV CL, Columns

		ProcedureColumnLoop:
			MOV DECR, CL 
		
			MOV SI, 0 
			MOV CL, Rows 

			ProcedureRowLoop:
				CMP Matrix[SI][BX], '0'
				JE Exchange
				JNE Save
				
				Exchange: 
					MOV DI, 0
					MOV CL, Rows
					ExchangeLoop:
						MOV AL, Matrix[DI][BX - 1]
						MOV Matrix[DI][BX], AL
						
						ADD DI, 9
					
					LOOP ExchangeLoop
					
					MOV CL, 1
					
				Save:
					ADD SI, 9 
				
				LOOP ProcedureRowLoop
	
			MOV CL, DECR 
			INC BX 
			
			LOOP ProcedureColumnLoop
		
		
		CALL PrintCRLF
		MOV AH, 9 
		MOV DX, OFFSET ResultMsg
		INT 21H
		CALL PrintCRLF
	
		MOV SI, 0
		MOV CL, Rows 

		OutputRowLoop:
			MOV DECR, CL 
		
			MOV BX, 0 
			MOV CL, Columns 

			OutputColumnLoop:

				MOV DL, Matrix[SI][BX]
				INC BX 
				
				MOV AH, 2
				INT 21H
				
				CALL PrintSpace
				
				LOOP OutputColumnLoop	

			CALL PrintCRLF
	
			MOV CL, DECR 
			ADD SI, 9
			
			LOOP OutputRowLoop
		 
		MOV AX, 4C00h
		INT 21h
CodeSegment ENDS
END MAIN
