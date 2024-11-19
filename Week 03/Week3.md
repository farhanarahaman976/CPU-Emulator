# Week 3: Basic CPU Components
## Objective
A CPU (Central Processing Unit) consists of several core components that work together to execute instructions and perform computations. 
The goal of this week is to implement the core components of a CPU. This includes building the Arithmetic Logic Unit (ALU), implementing general-purpose registers, and creating the program counter and instruction register.
## Program Counter and Instruction Register
### Overview
The Program Counter (PC) and Instruction Register (IR) are critical components of the CPU's control flow, enabling it to fetch and execute instructions systematically.

### Program Counter (PC):
The Program Counter holds the memory address of the next instruction to be executed in the program sequence.

### Instruction Register (IR):  
The Instruction Register holds the instruction currently being executed by the CPU.
## Program Structure:  
https://github.com/farhanarahaman976/CPU-Emulator/blob/main/Week%2003/Week3.cpp
## Explanation:

### Program Counter (PC)
-	**Initialization**: The PC is initialized to 0 in the CPU class constructor.
- **Fetching**: In the `fetchInstruction` method, the PC points to the memory address of the next instruction.
-	**Incrementing**: After fetching an instruction, the PC is incremented to point to the next instruction.

### Instruction Register (IR)
-	**Holding Instructions**: The IR holds the instruction fetched from memory.
-	**Fetching**: In the `fetchInstruction` method, the IR is set to the value of the memory at the address pointed to by the PC.
-	**Decoding and Executing**: The fetched instruction can then be decoded and executed by the CPU.

### Simulated CPU Execution
-	**Memory Representation**: A vector `memory` is used to represent the instruction memory.
-	**Fetching and Storing**: The CPU fetches instructions from this memory, stores them in the IR, and increments the PC.
-	**Execution**: The ALU performs operations based on the fetched instructions, demonstrating how arithmetic and logical operations would be executed.

## Arithmetic Logic Unit (ALU)
The Arithmetic Logic Unit (ALU) is a fundamental part of the CPU, responsible for performing arithmetic and logical operations.

### Key Functions of the ALU

#### Arithmetic Operations:
-	**Addition**: Adds two numbers and returns the result. Updates carry and overflow flags as necessary.
-	**Subtraction**: Subtracts one number from another. Updates borrow or carry flags for unsigned operations.
-	**Multiplication (optional in basic ALUs)**: Computes the product of two numbers.
-	**Division (optional in basic ALUs)**: Performs integer division of two numbers.

#### Logical Operations
- **AND**: Sets each bit in the result to 1 if the corresponding bits in both operands are 1.
- **OR**: Sets each bit in the result to 1 if at least one of the corresponding bits in the operands is 1.
- **XOR (Exclusive OR)**: Sets each bit in the result to 1 if only one of the corresponding bits is 1.
- **NOT**: Inverts each bit in the operand (1 becomes 0, and 0 becomes 1).

#### Comparison Operations
-	**Equality Check**: Checks if two numbers are equal.
-	**Greater Than or Less Than**: Compares two numbers to determine their relative magnitude.
-	**Unsigned and Signed Comparisons**: Handles signed and unsigned integers correctly.

#### Shift Operations
- **Left Shift**: Shifts bits to the left, filling with zeros.
- **Right Shift**: Shifts bits to the right, with the option of filling with zeros (logical shift) or preserving the sign bit (arithmetic shift).

### ALU Structure
An ALU is typically composed of:
- **Input Registers**: These hold the operands (the numbers to be operated on).
- **Operation Decoder**: This decodes the operation to be performed (e.g., add, subtract).
- **Arithmetic Circuitry**: Performs arithmetic operations.
- **Logic Circuitry**: Performs logic operations.
- **Output Register**: Holds the result of the operation.
  
## Conclusion: 
The Program Counter (PC) is a fundamental component of the CPU, critical for managing the flow of program execution. Its primary role is to ensure instructions are fetched in sequence or as directed by control flow instructions like jumps or branches. By holding the memory address of the next instruction, the PC serves as the CPU's guide, advancing through programs efficiently.

## Implement general-purpose registers:

General-purpose registers (GPRs) are essential components of a CPU, providing temporary storage for data and instructions during execution. Below is a step-by-step implementation of a general-purpose register file in C++.

### Functions of General-Purpose Registers:
-	**Data Manipulation**: Store input values for arithmetic and logical operations.
   - Hold intermediate results between instructions.
- **Memory Addressing**: Store memory addresses for load and store operations.
- **Temporary Storage**: Act as scratchpads for temporary data during computations.
  
### Organization of General-Purpose Registers
- **Register Bank**:  GPRs are organized into a register file, often implemented as an array or matrix.  Each register has a unique identifier or index (e.g., R0, R1, R2).
- **Access Mechanisms**: Single-Ported: Supports one read/write operation at a time.
   - Multi-Ported: Allows simultaneous access, useful in superscalar or parallel CPUs.
- **Number of Registers**:
   - Depends on the CPU architecture:
       	Small-scale systems may have 8–16 registers.
       	Modern architectures like x86-64 may have 16–32.
       	RISC architectures may support 32 or more registers.

### Advantages of General-Purpose Registers
- **Speed**: Faster access compared to memory, enhancing overall CPU performance.
- **Flexibility**: Can store any type of data required during computation, making them versatile.
- **Reduced Memory Access**: Frequent use of registers reduces the need to fetch data from slower main memory.
    
## Conclusion: 
General-purpose registers are a cornerstone of CPU design, providing a balance between performance and resource constraints. Their efficient use is key to maximizing computational speed and reducing memory dependency. 





