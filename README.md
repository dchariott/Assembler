# Assembler
This is a class Project to encode assembly language for an old dlx processor, it follows the encoding scheme of register type instructions, immediate type instructions and jump instructions.
Register-Type encoding: 6 bits for the opcode, 5 bits for rs1 then rs2 and then the destination register, followed by 10 bits for the function code (the opcode is 0)
Immediate-Type encoding: 6 bits for the opcode, 5 bits for rs1 and then rs2, followed by 16 bits for the immediate.
Jump encoding: 6 bits for the opcode and 26 bits for the PC offset.
