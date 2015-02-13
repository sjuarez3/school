		AREA linked_list,	CODE,	READWRITE
		
		ENTRY
start   MOV r1, #0x10
		ADR r0, List
loop	LDR r4, [r0], #4
		CMP r4, r1
		BEQ equal
		B  	loop
		
equal	MOV r2, #0xFFFFFFFF

Done	B	Done

List 	DCD Item5, 0xAB 
Item2 	DCD Item3, 0xCD 
Item3 	DCD Item4, 0xEF 
Item4 	DCD Item6, 0x10 
Item5 	DCD Item2, 0x11 
Item6 	DCD Item7, 0x12 
Item7 	DCD 0x00, 0x13 ;terminator 

		END