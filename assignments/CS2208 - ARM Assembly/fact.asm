		AREA factorial_calculator,	CODE,	READWRITE
		
		ENTRY
start   ADR sp, Base					;pointer to the base of the stack
		MOV r1, #3						;store n in register
		MOV r0, #1						;result of n! will be stored here
		BL  fact						;call factorial subroutine
		
Done    B	Done						;infinite loop		

fact    CMP r1, #1						;is n less than or equal to one?
		MOVLE r0, r1					;if yes, put n in r0
		MOVLE pc, lr					;return
		STMFD sp!, {r1, lr}				;if n greater than 1, push n and link register on the stack
		SUB r1, r1, #1					;subtract n by one
		BL  fact						;call factorial subroutine on n-1
		LDMFD sp!, {r1, lr}				;pop n-1 from stack and return to previous frame
		MUL r0, r1, r0					;calculate factorial of n-1 and store result in r0
		MOV pc, lr						;return


		DCD 0xAAAAAAAA,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0	;stack area
Base    DCD 0xBBBBBBBB 					;base of stack
		END