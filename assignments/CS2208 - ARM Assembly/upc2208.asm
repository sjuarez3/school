		AREA upc,	CODE,	READONLY
		
		
		ENTRY
start	mov r5, #5
		
		
		NOP
		END
		
		AREA data,	DATA,	READWRITE
UPC		DCB "013800150738" 		;UPC string 
EoS 	DCB 0x00 				;end of string