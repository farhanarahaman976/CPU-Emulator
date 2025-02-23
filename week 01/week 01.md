# Week 1: Project Planning & Setup

## The Features of the Virtual CPU

### Instruction Set Features:
- **Arithmetic Operations:**
 - **ADD:** Adds values from two registers.
 - **SUB:** Subtracts the value of one register from another.
 - **MUL:** Multiplies values from two registers.
 - **DIV:** Divides the value of one register by another.
  
### Logical Operations:

AND: Performs a bitwise AND operation.
OR: Performs a bitwise OR operation.
XOR: Performs a bitwise XOR operation.
NOT: Performs a bitwise NOT operation.
Data Transfer Operations:

LOAD: Loads a value from memory into a register.
STORE: Stores the value from a register into memory.
MOVE: Moves data from one register to another.
Control Flow Instructions:

JMP: Jumps to a specified memory address.
JZ: Jumps if the zero flag is set.
JNZ: Jumps if the zero flag is not set.
CALL: Calls a subroutine.
RET: Returns from a subroutine.
Comparison Operations:

CMP: Compares the values of two registers.
TEST: Performs a logical comparison between two values.
Architectural Features:
Registers:

General-purpose registers (R0, R1, R2, ...)
Special-purpose registers (Program Counter, Status Register, Stack Pointer)
Memory:

Main memory to store instructions and data.
Support for memory addressing modes (direct, indirect, indexed).
Flags and Status Register:

Zero flag, Carry flag, Overflow flag, Sign flag.
Interrupt Handling:

Basic interrupt system to handle hardware interrupts and exceptions.
Execution Environment:
Pipeline:

Implement basic pipelining stages (Fetch, Decode, Execute, Memory Access, Write-back).
Cache:

Implement a simple cache mechanism to speed up memory access.
I/O Operations:

Input and output operations to simulate interaction with peripherals.
Development and Testing:
Assembler:

A program to convert assembly language instructions into machine code.
Debugger:

Basic debugging tools to step through instructions, inspect register values, and set breakpoints.
Simulator/Emulator:

An environment to simulate the execution of programs on the vCPU.
Documentation:

Comprehensive documentation of the ISA, instruction formats, and operational behavior.
Additional Considerations:
Performance Metrics:

Tools to measure execution time, memory usage, and other performance metrics.
User Interface:

A simple CLI to interact with the vCPU, load programs, and visualize execution.
Programming Language: C++
Why C++:
Performance: C++ offers high performance, which is crucial for CPU emulation.
Control: Greater control over system resources and memory management.
Extensive Libraries: Access to numerous libraries for various functionalities.
Tools and Frameworks:
Boost: For a wide range of utility libraries.
Google Test: For unit testing.
CMake: For build automation. <<<<<<< HEAD
GitHub/GitLab: For version control. =======
GitHub/GitLab: For version control.
c70d70303a5d72c4a39d48491cf8e55b7bd81225
