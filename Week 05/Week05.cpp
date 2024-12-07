#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

enum InstructionType { ADD, SUB, MUL, DIV, LOAD, STORE, UNKNOWN };

class ALU {
public:
    int performOperation(const string& opcode, int operand1, int operand2) {
        if (opcode == "ADD") return operand1 + operand2;
        if (opcode == "SUB") return operand1 - operand2;
        if (opcode == "MUL") return operand1 * operand2;
        if (opcode == "DIV") {
            if (operand2 == 0) {
                throw runtime_error("Division by zero error.");
            }
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

    void display() const {
        cout << "Registers:" << endl;
        for (const auto& reg : regs) {
            cout << setw(3) << reg.first << ": " << setw(5) << reg.second << " ";
        }
        cout << endl;
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

    void display() const {
        cout << "Memory State (non-zero values):" << endl;
        for (size_t i = 0; i < memorySpace.size(); ++i) {
            if (memorySpace[i] != 0) {
                cout << "Address " << setw(3) << i << ": " << memorySpace[i] << endl;
            }
        }
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

    void loadProgram(const vector<int>& program) {
        instructionMemory = program;
    }

    void executeProgram() {
        while (programCounter < instructionMemory.size()) {
            int instruction = instructionMemory[programCounter];
            programCounter++;
            decodeAndExecute(instruction);
        }
    }

private:
    void decodeAndExecute(int instruction) {
        int opcode = (instruction >> 8) & 0x07;
        int reg1 = (instruction >> 4) & 0x0F;
        int reg2 = instruction & 0x0F;

        string opcodeStr = getOpcodeString(opcode);
        int operand1 = registers.get("R" + to_string(reg1));
        int operand2 = (opcodeStr == "LOAD" || opcodeStr == "STORE") ? reg2 : registers.get("R" + to_string(reg2));

        if (opcodeStr == "LOAD") {
            int value = memory.read(operand2);
            registers.set("R" + to_string(reg1), value);
        } else if (opcodeStr == "STORE") {
            memory.write(operand2, operand1);
        } else {
            int result = alu.performOperation(opcodeStr, operand1, operand2);
            registers.set("R" + to_string(reg1), result);
        }

        cout << "Executed: " << opcodeStr << " R" << reg1 << ", R" << reg2 << endl;
        registers.display();
        memory.display();
        cout << endl;
    }

    string getOpcodeString(int opcode) const {
        switch (opcode) {
            case 0: return "ADD";
            case 1: return "SUB";
            case 2: return "MUL";
            case 3: return "DIV";
            case 4: return "LOAD";
            case 5: return "STORE";
            default: return "UNKNOWN";
        }
    }
};

vector<int> assemble(const string& assemblyCode) {
    map<string, int> opcodes = {{"ADD", 0}, {"SUB", 1}, {"MUL", 2}, {"DIV", 3}, {"LOAD", 4}, {"STORE", 5}};
    map<string, int> registers = {{"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3}};
    istringstream iss(assemblyCode);
    string line;
    vector<int> machineCode;

    while (getline(iss, line)) {
        istringstream linestream(line);
        string opcode, reg1, reg2;
        linestream >> opcode >> reg1 >> reg2;
        int machineInstruction = (opcodes[opcode] << 8) | (registers[reg1] << 4) | registers[reg2];
        machineCode.push_back(machineInstruction);
    }
    return machineCode;
}

int main() {
    CPU cpu;

    string assemblyCode =
        "LOAD R1 10\n"
        "ADD R2 R1\n"
        "MUL R3 R2\n"
        "STORE R3 20\n";

    vector<int> machineCode = assemble(assemblyCode);
    cpu.loadProgram(machineCode);

    cpu.memory.write(10, 5);

    cout << "Executing Program..." << endl;
    cpu.executeProgram();

    return 0;
}

