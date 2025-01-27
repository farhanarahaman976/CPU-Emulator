#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>
#include <string>
#include <bitset>
#include <map>
#include <iomanip>

using namespace std;


class Registers {
public:
    map<string, int> regs;

    Registers() {
        regs["R0"] = 0; regs["R1"] = 0; regs["R2"] = 0; regs["R3"] = 0;
    }

    int get(const string& reg) {
        if (regs.find(reg) != regs.end()) {
            return regs[reg];
        } else {
            throw invalid_argument("Invalid register: " + reg);
        }
    }

    void set(const string& reg, int value) {
        if (regs.find(reg) != regs.end()) {
            regs[reg] = value;
        } else {
            throw invalid_argument("Invalid register: " + reg);
        }
    }

    void displayBinary() const {
        cout << "Registers (Binary):" << endl;
        for (const auto& reg : regs) {
            cout << reg.first << ": " << bitset<16>(reg.second) << endl;
        }
    }
};


class Memory {
public:
    vector<int> memorySpace;

    Memory(int size) : memorySpace(size, 0) {}

    int read(int address) {
        if (address < 0 || address >= memorySpace.size()) {
            throw out_of_range("Memory read error: Address out of bounds.");
        }
        return memorySpace[address];
    }

    void write(int address, int value) {
        if (address < 0 || address >= memorySpace.size()) {
            throw out_of_range("Memory write error: Address out of bounds.");
        }
        memorySpace[address] = value;
    }

    void displayBinary() const {
        cout << "Memory State (Binary):" << endl;
        for (size_t i = 0; i < memorySpace.size(); ++i) {
            if (memorySpace[i] != 0) {
                cout << "Address " << i << ": " << bitset<16>(memorySpace[i]) << endl;
            }
        }
    }
};


class CPU {
private:
    int ACC;
    int programCounter;
    vector<uint32_t> instructionMemory;  
    stack<int> callStack;
    bool interruptFlag;
    Registers registers;
    Memory memory;

public:
    CPU() : ACC(0), programCounter(0), interruptFlag(false), memory(256) {}

    void loadProgram(const vector<uint32_t>& program) {
        instructionMemory = program;
    }

    void executeProgram() {
        while (programCounter < instructionMemory.size()) {
            if (interruptFlag) {
                handleInterrupt();
            }
            uint32_t instruction = fetch();
            if (!decodeAndExecute(instruction)) {
                break;
            }
        }
    }

    void displayState() const {
        registers.displayBinary();
        memory.displayBinary();
    }

private:
    uint32_t fetch() {
        return instructionMemory[programCounter++];
    }

    bool decodeAndExecute(uint32_t instruction) {
        uint8_t opcode = (instruction >> 24) & 0xFF;  // Extract opcode
        uint8_t reg1 = (instruction >> 16) & 0xFF;    // Extract reg1
        uint8_t reg2 = (instruction >> 8) & 0xFF;     // Extract reg2
        uint16_t immediate = instruction & 0xFFFF;   // Extract immediate

        cout << "\nExecuting Instruction (Binary): " << bitset<32>(instruction) << endl;

        if (opcode == 0x01) {  // LOAD
            string reg = "R" + to_string(reg1);
            registers.set(reg, immediate);
        } else if (opcode == 0x02) {  // ADD
            string reg1Name = "R" + to_string(reg1);
            string reg2Name = "R" + to_string(reg2);
            int result = registers.get(reg1Name) + registers.get(reg2Name);
            registers.set("R0", result);
        } else if (opcode == 0x03) {  // CALL
            callStack.push(programCounter);
            programCounter = immediate - 1;
        } else if (opcode == 0x04) {  // RET
            if (!callStack.empty()) {
                programCounter = callStack.top();
                callStack.pop();
            }
        } else if (opcode == 0xFF) {  // HLT
            return false;
        } else {
            cerr << "Unknown opcode: " << opcode << endl;
        }
        return true;
    }

    void handleInterrupt() {
        cout << "Interrupt triggered! Saving CPU state...\n";
        interruptFlag = false;
    }
};


uint32_t encodeInstruction(uint8_t opcode, uint8_t reg1, uint8_t reg2, uint16_t immediate) {
    uint32_t instruction = 0;
    instruction |= (opcode << 24);    
    instruction |= (reg1 << 16);          
    instruction |= (reg2 << 8);           
    instruction |= immediate;           
    return instruction;
}

int main() {
    
    vector<uint32_t> program = {
        encodeInstruction(0x01, 1, 0, 5),  
        encodeInstruction(0x01, 2, 0, 10), 
        encodeInstruction(0x02, 1, 2, 0),  
        encodeInstruction(0x03, 0, 0, 6),  
        encodeInstruction(0xFF, 0, 0, 0),  
        encodeInstruction(0x01, 3, 0, 20), 
        encodeInstruction(0x04, 0, 0, 0)   
    };

    
    CPU cpu;
    cpu.loadProgram(program);
    cpu.executeProgram();
    cpu.displayState();

    return 0;
}
