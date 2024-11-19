# Week 2: Instruction Set Architecture (ISA)

## Assembler Program Description:
The assembler program translates human-readable assembly code into machine-readable binary instructions for a virtual CPU. It takes a simple set of instructions written in assembly language, parses each instruction, and generates corresponding machine code based on predefined opcodes and formats.

### ADD (Addition)
-**Opcode**: `0001`
-**Description**: Adds the values in two source registers and stores the result in the destination register.
-**Format**: ADD Rdest, Rsrc1, Rsrc2
-**Behavior**:
`Rdest = Rsrc1 + Rsrc2`
-**Example**:
-**Assembly**: `ADD R1, R2, R3`
-**Machine Code**: `0001 0001 0010 0011`

### SUB (Subtraction)
-**Opcode**: `0010`
-**Description**: Subtracts the value of the second source register from the first source register and stores the result in the destination register.
-**Format**: `SUB Rdest, Rsrc1, Rsrc2`
-**Behavior**:
`Rdest = Rsrc1 - Rsrc2`
-**Example**:
-**Assembly**: `SUB R1, R2, R3`
-**Machine Code**: `0010 0001 0010 0011`

### LOAD (Load Immediate Value)
-**Opcode**: `0011`
-**Description**: Loads an immediate value into the specified register.
-**Format**: `LOAD Rdest, IMM`
-**Behavior**:
`Rdest = IMM`
-**Example**:
-**Assembly**: `LOAD R1, 5`
-**Machine Code**: `0011 0001 0101 0000`

### STORE (Store Register to Memory)
-**Opcode**: `0100`
-**Description**: Stores the value from a register into a specified memory address.
-**Format**: `STORE Rsrc, MEM`
-**Behavior**:
`MEM[ADDR] = Rsrc`
-**Example**:
-**Assembly**: `STORE R1, 10`
-**Machine Code**: `0100 0001 1010 0000`

### MUL (Multiplication)
-**Opcode**: `0101`
-**Description**: Multiplies the values in two source registers and stores the result in the destination register.
-**Format**: `MUL Rdest, Rsrc1, Rsrc2`
-**Behavior**:
`Rdest = Rsrc1 * Rsrc2`
-**Example**:
-**Assembly**: `MUL R1, R2, R3`
-**Machine Code**: `0101 0001 0010 0011`

### DIV (Division)
-**Opcode**: `0110`
-**Description**: Divides the value in the first source register by the value in the second source register and stores the result in the destination register.
-**Format**: `DIV Rdest, Rsrc1, Rsrc2`
-**Behavior**:
`Rdest = Rsrc1 / Rsrc2`
-**Example**:
-**Assembly**: `DIV R1, R2, R3`
-**Machine Code**: `0110 0001 0010 0011`

### AND (Bitwise AND)
-**Opcode**: `0111`
-**Description**: Performs a bitwise AND operation on two registers and stores the result in the destination register.
-**Format**: `AND Rdest, Rsrc1, Rsrc2`
-**Behavior**:
`Rdest = Rsrc1 & Rsrc2`
-**Example**:
-**Assembly**: `AND R1, R2, R3`
-**Machine Code**: `0111 0001 0010 0011`

### OR (Bitwise OR)
-**Opcode**: `1000`
-**Description**: Performs a bitwise OR operation on two registers and stores the result in the destination register.
-**Format**: `OR Rdest, Rsrc1, Rsrc2`
-**Behavior**:
`Rdest = Rsrc1 | Rsrc2`
-**Example**:
-**Assembly**: `OR R1, R2, R3`
-**Machine Code**: `1000 0001 0010 0011`

### XOR (Bitwise XOR)
-**Opcode**: `1001`
-**Description**: Performs a bitwise XOR operation on two registers and stores the result in the destination register.
-**Format**: `XOR Rdest, Rsrc1, Rsrc2`
-**Behavior**:
`Rdest = Rsrc1 ^ Rsrc2`
-**Example**:
-**Assembly**: `XOR R1, R2, R3`
-**Machine Code**: `1001 0001 0010 0011`

### NOT (Bitwise NOT)
-**Opcode**: `1010`
-**Description**: Performs a bitwise NOT operation on a register and stores the result in the destination register.
-**Format**: `NOT Rdest, Rsrc`
-**Behavior**:
`Rdest = ~Rsrc`
-**Example**:
-**Assembly**: `NOT R1, R2`
-**Machine Code**: `1010 0001 0010 0000`

### JUMP (Unconditional Jump)
-**Opcode**: `1011`
-**Description**: Jumps to a specified memory address unconditionally.
-**Format**: `JUMP MEM`
-**Behavior**:
`PC = MEM`
-**Example**:
-**Assembly**: `JUMP 34`
-**Machine Code**: `1011 0000 0010 0010`

## Document the Instruction Formats:
Each instruction can have a specific format, often including the opcode and operands. Here’s a simple example.

| Instruction | Opcode | Format                    | Behavior                     |
|-------------|--------|---------------------------|------------------------------|
| ADD         | 0001   | ADD Rdest, Rsrc1, Rsrc2   | Rdest = Rsrc1 + Rsrc2        |
| SUB         | 0010   | SUB Rdest, Rsrc1, Rsrc2   | Rdest = Rsrc1 - Rsrc2        |
| LOAD        | 0011   | LOAD Rdest, IMM           | Rdest = IMM                  |
| STORE       | 0100   | STORE Rsrc, MEM           | MEM[ADDR] = Rsrc             |
| MUL         | 0101   | MUL Rdest, Rsrc1, Rsrc2   | Rdest = Rsrc1 * Rsrc2        |
| DIV         | 0110   | DIV Rdest, Rsrc1, Rsrc2   | Rdest = Rsrc1 / Rsrc2        |
| AND         | 0111   | AND Rdest, Rsrc1, Rsrc2   | Rdest = Rsrc1 & Rsrc2        |
| OR          | 1000   | OR Rdest, Rsrc1, Rsrc2    | `Rdest = Rsrc1               |
| XOR         | 1001   | XOR Rdest, Rsrc1, Rsrc2   | Rdest = Rsrc1 ^ Rsrc2        |
| NOT         | 1010   | NOT Rdest, Rsrc           | Rdest = ~Rsrc                |
| JMP         | 1011   | JUMP MEM                  | PC = MEM                     |

#### Create a Simple Assembler:
-**Parser**: Read assembly code and parse each line to identify the instruction and operands.
-**Opcode Mapping**: Create a mapping from instruction names to their corresponding opcode values.
-**Code Generation**: Convert parsed instructions into machine code by replacing instruction names with opcodes and resolving operand addresses.
