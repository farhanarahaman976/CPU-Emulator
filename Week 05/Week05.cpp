#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <bitset>
#include <map>
#include <iomanip>

using namespace std;

unordered_map<string, int> opcodes = {
    {"ADD", 0}, {"SUB", 1}, {"MUL", 2}, {"DIV", 3}, {"LOAD", 4}, {"STORE", 5}, {"HALT", 6}
};
unordered_map<string, int> registers = {
    {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3}, {"R4", 4}, {"R5", 5}, {"R6", 6}, {"R7", 7}
};

int assembleInstruction(const string &inst) {
    istringstream iss(inst);
    string op, reg1, reg2;
    iss >> op >> reg1 >> reg2;
    
    int opcode = opcodes[op];
    int regNum1 = registers[reg1];
    int regNum2 = registers[reg2];
    
    return (opcode << 8) | (regNum1 << 4) | regNum2;
}

class ALU {
public:
    int performOperation(const string& opcode, int operand1, int operand2) {
        if (opcode == "ADD") return operand1 + operand2;
        if (opcode == "SUB") return operand1 - operand2;
        if (opcode == "MUL") return operand1 * operand2;
        if (opcode == "DIV") {
            if (operand2 == 0) throw runtime_error("Division by zero error.");
            return operand1 / operand2;
        }
        return 0;
    }
};

class Registers {
public:
    map<string, int> regs;
    Registers() {
        regs["R0"] = 0; regs["R1"] = 0; regs["R2"] = 0; regs["R3"] = 0;
    }
    int get(const string& reg) { return regs[reg]; }
    void set(const string& reg, int value) { regs[reg] = value; }
    void display() const {
        cout << "Registers: ";
        for (const auto& reg : regs) {
            cout << reg.first << "=" << reg.second << " ";
        }
        cout << endl;
    }
};

class Memory {
public:
    vector<int> memorySpace;
    Memory(int size) : memorySpace(size, 0) {}
    int read(int address) { return memorySpace[address]; }
    void write(int address, int value) { memorySpace[address] = value; }
    void display() const {
        cout << "Memory: ";
        for (size_t i = 0; i < memorySpace.size(); ++i) {
            if (memorySpace[i] != 0) cout << "[" << i << "]=" << memorySpace[i] << " ";
        }
        cout << endl;
    }
};

class CPU {
public:
    int programCounter;
    vector<int> instructionMemory;
    Registers registers;
    ALU alu;
    Memory memory;
    CPU() : programCounter(0), memory(256) {}
    void loadProgram(const vector<int>& program) { instructionMemory = program; }
    void executeProgram() {
        while (programCounter < instructionMemory.size()) {
            int instruction = instructionMemory[programCounter++];
            decodeAndExecute(instruction);
        }
    }
private:
    void decodeAndExecute(int instruction) {
        int opcode = (instruction >> 8) & 0x07;
        int reg1 = (instruction >> 4) & 0x0F;
        int reg2 = instruction & 0x0F;
        
        string opcodeStr;
        for (const auto& pair : opcodes) {
            if (pair.second == opcode) {
                opcodeStr = pair.first;
                break;
            }
        }
        
        int operand1 = registers.get("R" + to_string(reg1));
        int operand2 = registers.get("R" + to_string(reg2));
        
        if (opcodeStr == "LOAD") {
            registers.set("R" + to_string(reg1), memory.read(operand2));
        } else if (opcodeStr == "STORE") {
            memory.write(operand2, operand1);
        } else {
            registers.set("R" + to_string(reg1), alu.performOperation(opcodeStr, operand1, operand2));
        }
        
        cout << "Executed: " << opcodeStr << " R" << reg1 << ", R" << reg2 << endl;
        registers.display();
        memory.display();
        cout << endl;
    }
};

vector<int> assemble(const vector<string>& assemblyCode) {
    vector<int> machineCode;
    for (const auto& line : assemblyCode) {
        machineCode.push_back(assembleInstruction(line));
    }
    return machineCode;
}

int main() {
    CPU cpu;
    
    vector<string> assemblyCode = {
        "LOAD R1 R0",
        "ADD R2 R1",
        "MUL R3 R2",
        "STORE R3 R0",
        "HALT R0 R0"
    };
    
    vector<int> machineCode = assemble(assemblyCode);
    
    cout << "Assembled Machine Code (Binary Representation):\n";
    for (const auto &code : machineCode) {
        cout << bitset<16>(code) << endl;
    }
    cout << endl;
    
    cpu.loadProgram(machineCode);
    cpu.memory.write(0, 5);
    cout << "Executing Program...\n";
    cpu.executeProgram();
    
    return 0;
}
