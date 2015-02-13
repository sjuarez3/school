		AREA concatenation,	CODE,	READONLY
		
		ENTRY
		
start	ADR r0, STRING1			;use r0 as a pointer to STRING1
		MOV r4, #0				;use r4 as a counter
Loop	LDRB r2, [r0], #1		;load first digit of STRING1 and post-increment to get next character
		ADD r4, #1				;increment counter by 1
		SUB r2, #48				;subtract 48 from character to convert it from ascii to decimal
		CMP r2, #0x00			;check to see if character is null
		BEQ Done
		STR r2, STRING3
		B Loop					;loop through string of characters    		
Done	B	Done							
		
STRING1 DCB "This is a test string1" ;String1 
EoS 	DCB 0x00 					 ;end of string1 
STRING2 DCB "This is a test string2" ;String 
EoS 	DCB 0x00   					 ;end of string2 
STRING3 space 0xFF 
	
		END