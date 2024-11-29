# Week 4: Instruction Execution
## Objective: 
The Instruction Fetch-Decode-Execute Cycle is the fundamental operational process of a CPU, and implementing it involves multiple steps. Here’s a detailed breakdown for each task in Week 4:
### Instruction Fetching Mechanism
This step retrieves instructions from memory based on the program counter (PC).

#### Steps:
**Access Memory**: Use the value in the program counter (PC) as an address to fetch the next instruction from memory.
**Example**: `instruction = memory[PC];`
**Increment the Program Counter**: After fetching, increment the PC to point to the next instruction.
**Example**: `PC += instruction_size;`
**Handle Memory Limits**: Ensure that the PC does not go beyond the allocated memory bounds.
