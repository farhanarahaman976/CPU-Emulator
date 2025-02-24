#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <functional>

using namespace std;
enum InstructionType { ADD, SUB, MUL, DIV, LOAD, STORE, IN, OUT, HLT, UNKNOWN };

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
    int ACC;
    int programCounter;
    vector<string> instructionMemory;
    Registers registers;
    ALU alu;
    Memory memory;

    CPU() : ACC(0), programCounter(0), memory(256) {}

    void loadProgram(const vector<string>& program) {
        instructionMemory = program;
    }

    void executeProgram() {
        while (programCounter < instructionMemory.size()) {
            string instruction = fetch();
            if (!decodeAndExecute(instruction)) {
                break;
            }
        }
    }

private:
    string fetch() {
        if (programCounter < instructionMemory.size()) {
            return instructionMemory[programCounter++];
        }
        return "";
    }

    bool decodeAndExecute(const string& instruction) {
        if (instruction.empty()) {
            return false;
        }

        istringstream iss(instruction);
        string opcode;
        iss >> opcode;

        if (opcode == "IN") {
            ACC = simulateKeyboardInput();
        } else if (opcode == "OUT") {
            simulateDisplayOutput(ACC);
        } else if (opcode == "ADD") {
            int operand;
            iss >> operand;
            ACC += operand;
        } else if (opcode == "SUB") {
            int operand;
            iss >> operand;
            ACC -= operand;
        } else if (opcode == "HLT") {
            return false;
        } else {
            cerr << "Unknown instruction: " << opcode << endl;
        }

        return true;
    }

    int simulateKeyboardInput() {
        cout << "Enter a number: ";
        int input;
        cin >> input;
        return input;
    }

    void simulateDisplayOutput(int value) {
        cout << "Display: " << value << endl;
    }
};

int main() {
    vector<string> program = {
        "IN",
        "ADD 10",
        "OUT",
        "SUB 5",
        "OUT",
        "HLT"
    };

    CPU cpu;
    cpu.loadProgram(program);
    cpu.executeProgram();

    return 0;
}

