# Memory Management for Virtual CPU
- **Objective**: Implement a robust memory management system for the virtual CPU.

## Tasks Breakdown
### 1. Set Up a Simulated Memory Space
- **Description**: Create an abstraction for memory that can be accessed and manipulated by the virtual CPU.
- **Subtasks**:
- Define the size of the memory (e.g., 64KB, 128KB, or configurable).
- Represent the memory as an array, vector, or another suitable data structure in C++.
- Initialize the memory with default values (e.g., all zeros).
- Ensure memory space can be dynamically resized if needed.
  
### 2. Implement Memory Read/Write Operations
- **Description**: Enable the virtual CPU to interact with memory for loading and storing data.
- **Subtasks**:
- **Read Operation**: Create a method to retrieve data from a specified memory address.
```cpp
uint8_t readMemory(uint16_t address);
```
- **Write Operation**: Create a method to write data to a specified memory address.
```cpp
void writeMemory(uint16_t address, uint8_t value);
```
Add error handling for invalid memory accesses (e.g., accessing addresses outside the defined memory range).

### 3. Handle Address Mapping and Memory Segmentation
- **Description**: Design a system to map logical addresses to physical addresses and divide memory into segments (e.g., code, data, stack).
- **Subtasks**:
  - Implement address translation logic:
   - Logical-to-Physical Address Mapping.
   - Base and limit register mechanism for segmentation.
  - Divide the memory space into segments:
   - Code Segment: Stores program instructions.
   - Data Segment: Stores global and static variables.
   - Stack Segment: For function calls and local variables.
  - Add support for memory protection:
   - Restrict write access to the code segment.
   - Prevent stack overflow into other segments.


