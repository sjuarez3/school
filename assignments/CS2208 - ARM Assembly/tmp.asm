		AREA upc,	CODE,	READONLY
		
		ENTRY
		
start	ADR r1, UPC				;use r1 as a pointer to string UPC
		MOV r4, #0				;use r4 as a counter
		ADD r6, #0				;even register
		ADD r7, #1				;odd register
Loop	LDRB r2, [r1], #1		;load first digit of upc and post-increment to get next character
		ADD r4, #1				;increment counter by 1
		SUB r2, #48				;subtract 48 from character to convert it from ascii to decimal
		CMP r7, r6
		BNE oddtot
		B   eventot
oddtot	ADD r3, r2				;r3 will contain the sum of all odd characters
		ADD r6, #1
eventot ADD r8, r2				;r4 will contain sum of all even characters
		ADD r7, #1
		CMP r4, #12				;if counter is not equal to 12 then we're not done, continue loop
		BNE Loop				;if counter is equal to 12 then we're done, stop loop
		ADD r5, r3, r3, LSL#1	;multiply sum of odd characters by 3 and put in r5
		ADD r5, r8
Loop2   SUB r5, #10				;subtract 16 from r5 until the the digit left is less than or equal to 9
		CMP r5, #9				;this division method will leave us with the remainder
		BLS	Next
		BPL Loop2
Next	
		CMP r5, #0				;compare the remainder to 0. If zero than it's valid, if not 0 then it's invalid
		BEQ valid
		B	final				;r0 stays 0 to signal its's 
valid   MOV r0, #1				;1 is put into r0 to signal it's valid
final							
		
UPC		DCB "013800150738" 		;UPC string 
EoS 	DCB 0x00 				;end of string
		END