# Week 4: Instruction Execution
## Objective: 
The Instruction Fetch-Decode-Execute Cycle is the fundamental operational process of a CPU, and implementing it involves multiple steps. Here’s a detailed breakdown for each task in Week 4:

## Instruction Fetching Mechanism
This step retrieves instructions from memory based on the program counter (PC).

### Steps:
- **Access Memory**: Use the value in the program counter (PC) as an address to fetch the next instruction from memory.
 - **Example**: `instruction = memory[PC];`
- **Increment the Program Counter**: After fetching, increment the PC to point to the next instruction.
 - **Example**: `PC += instruction_size;`
- **Handle Memory Limits**: Ensure that the PC does not go beyond the allocated memory bounds.
  
### Key Components to Implement:
- **Program Counter (PC)**: A register that tracks the address of the next instruction.
- **Memory Interface**: Functions or mechanisms to read from (and possibly write to) memory.

## Instruction Fetching Mechanism
This step retrieves instructions from memory based on the program counter (PC).

### Steps:

- **Access Memory**: Use the value in the program counter (PC) as an address to fetch the next instruction from memory.
  - **Example**: `instruction = memory[PC];`
- **Increment the Program Counter**: After fetching, increment the PC to point to the next instruction.
  - **Example**: `PC += instruction_size;`
- **Handle Memory Limits**: Ensure that the PC does not go beyond the allocated memory bounds.
  
### Key Components to Implement:
- **Program Counter (PC)**: A register that tracks the address of the next instruction.
- **Memory Interface**: Functions or mechanisms to read from (and possibly write to) memory.

##  Decode Instructions
This step interprets the fetched instruction into its components (operation and operands).

### Steps:
- **Extract Opcode**: Identify the operation (e.g., ADD, SUB, LOAD, STORE) from the instruction.
  - **Example**: `(opcode, operand1, operand2) = decode(instruction);`
- **Parse Operands**: Determine the type of operands (register, memory address, or immediate value).
- **Instruction Format**: Decide on a consistent instruction format during ISA design. Example formats:
- **R-type (Register)**: `Opcode | Rd | Rs | Rt`
- **I-type (Immediate)**: `Opcode | Rd | Rs | Imm`
 
### Key Considerations:
Use bit masking and shifting to extract instruction fields.
Maintain a mapping of opcodes to specific operations.


##  Execute Instructions
The CPU executes the decoded instruction using its components like the ALU, registers, or memory.

### Steps:
- **ALU Operations**: Perform arithmetic or logical operations for instructions like ADD, SUB, AND, etc.
  - **Example**: `if (opcode == ADD) Rd = Rs + Rt;`
- **Memory Operations**:
   - **LOAD**: Read data from memory into a register.
   - **STORE**: Write data from a register into memory.
- **Branching/Jumping**: Modify the PC for control flow instructions.
   - **Example**: `if (opcode == JUMP) PC = target_address;`
- **Update Flags (Optional)**: Update flags (zero, carry, etc.) for conditional operations.

