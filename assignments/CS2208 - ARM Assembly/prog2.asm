		AREA the_removal,	CODE,	READONLY
		
		ENTRY
		
start	ADR r0, STRING1			;use r0 as pointer to STRING1
		ADR r1, STRING2			;use r1 as pointer to STRING2
		MOV r3, #0				;r3 is counter used to detect "the" string
Loop	LDRB r2, [r0], #1		;load first character of STRING1 and post-increment to get next character
		CMP r2, #0x20			;if space character increase counter
		ADDEQ r3, #1			;increment counter by 1
		TEQ r3, #5
		SUB r1, r1, #4			;decrement string2 by 4 bytes
		CMP r2, #0x74			;if character is 't' increment counter
		ADDEQ r3, #1
		CMP r2, #0x68			;if character is 'h' increment counter
		ADDEQ r3, #1
		CMP r2, #0x65			;if character is 'e' increment counter
		ADDEQ r3, #1
		CMP r2, #0x00			;check to see if character is null
		ADDEQ r3, #1			;increment counter
		CMP r2, #0x00
		BEQ Done				;if character is null, string is done copying
		
		STRB r2, [r1], #1		;if character not null, copy it to STRING2 and increment to next byte in memory
		B Loop					;continues to loop through characters of STRING1
Done	B	Done				;infinite loop			

STRING1 DCB "and the man said they must go" ;String1 
EoS 	DCB 0x00 							;end of string1 
STRING2 space 0xFF
	
		END