.global writeGdtToRegisters

writeGdtToRegisters:
	MOV AX, [esp + 4]
	LGDT [eax]
	
	MOV AX, 0x10
	MOV DS, AX
	MOV ES, AX
	MOV FS, AX
	MOV GS, AX
	MOV SS, AX
	JMP 0x08:.setCs
.setCs:
	RET
