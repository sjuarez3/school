		AREA factorial_calculator,	CODE,	READWRITE
		
		ENTRY
start   ADR sp, Base					;pointer to the base of the stack
		MOV r5, #1
		STR r5, [r13,#-4]!
		;BL  fact						;call factorial subroutine




		DCD 0x89ABCDEF,0,0,0,0x12345678	;stack area
Base    DCD 0xAAAAAAAA 					;stack base
		END