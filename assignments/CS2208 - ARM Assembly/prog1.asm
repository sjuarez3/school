		AREA string_concatenation,	CODE,	READONLY
		
		ENTRY
		
start	ADR r0, STRING1			;use r0 as pointer to STRING1
		ADR r1, STRING3			;use r1 as pointer to STRING3
Loop1	LDRB r2, [r0], #1		;load first character of STRING1 and post-increment to get next character
		CMP r2, #0x00			;check to see if character is null
		BEQ Next				;if character is null, string is done copying
		STRB r2, [r1], #1		;if character not null, copy it to STRING3 and increment to next byte in memory
		B Loop1					;continues to loop through characters of STRING1
Next
		ADR r3, STRING2			;use r3 as pointer to STRING2
Loop2	LDRB r2, [r3], #1		;load first character of STRING2 and post-increment to get next character
		STRB r2, [r1], #1		;if character not null, copy it to STRING3 and increment to next byte in memory
		CMP r2, #0x00			;check to see if character is null
		BEQ Done				;if character is null, string is done copying
		B Loop2					;continues to loop through characters of STRING2
		
Done	B	Done				;infinite loop			

STRING1 DCB "This is a test string1" ;String1 
EoS 	DCB 0x00 					 ;end of string1 
STRING2 DCB "This is a test string2" ;String 
EoS2 	DCB 0x00   					 ;end of string2 
STRING3 space 0xFF 
	
		END