		AREA linked_list,	CODE,	READWRITE
		
		ENTRY
start  	ADR r0, List			;pointer to head of linked list
		ADR r1, Item6			;pointer to desired node
loop	CMP r0, #0x00			;is current node equal to terminator node?
		BEQ	exit				;if yes, node not found in list, program is done
		CMP r0, r1				;is current node equal to desired node?
		BEQ equal				;if yes, then loop is finished, search was successful
		LDR r0, [r0]			;if not, set pointer to next link and
		B  	loop				;continue loop
		
equal	MOV r2, #0xFFFFFFFF		;if node found set register to this number
		MOV r3, r1				;set r3 with address of desired node
		B 	Done

exit	MOV r2, #0xF0			;node not found, register set to this number

Done	B	Done				;infinite loop, program done

List 	DCD Item5, 0x12341111 	;linked list of data
Item2 	DCD Item3, 0x12342222 
Item3 	DCD Item4, 0x12343333 
Item4 	DCD Item6, 0x12344444 
Item5 	DCD Item2, 0x12345555 
Item6 	DCD Item7, 0x12346666 
Item7 	DCD 0x00, 0x12347777 	;terminator 

		END