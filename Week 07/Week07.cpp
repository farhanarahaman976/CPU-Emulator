#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <stack>
#include <stdexcept>

using namespace std;

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
    stack<int> callStack;
    bool interruptFlag;

    CPU() : ACC(0), programCounter(0), memory(256), interruptFlag(false) {}

    void loadProgram(const vector<string>& program) {
        instructionMemory = program;
    }

    void executeProgram() {
        while (programCounter < instructionMemory.size()) {
            if (interruptFlag) {
                interruptHandler();
            }
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
            string reg;
            iss >> reg;
            ACC += registers.get(reg);
        } else if (opcode == "SUB") {
            string reg;
            iss >> reg;
            ACC -= registers.get(reg);
        } else if (opcode == "LOAD") {
            string reg;
            iss >> reg;
            ACC = registers.get(reg);
        } else if (opcode == "STORE") {
            string reg;
            iss >> reg;
            registers.set(reg, ACC);
        } else if (opcode == "CALL") {
            int address;
            iss >> address;
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
    vector<string> instructionMemory;
    stack<int> callStack;
    bool interruptFlag;
    Registers registers;
    Memory memory;

public:
    CPU() : ACC(0), programCounter(0), interruptFlag(false), memory(256) {}

    void loadProgram(const vector<string>& program) {
        instructionMemory = program;
    }

    void executeProgram() {
        while (programCounter < instructionMemory.size()) {
            if (interruptFlag) {
                handleInterrupt();
            }
            string instruction = fetch();
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
    string fetch() {
        return instructionMemory[programCounter++];
    }

    bool decodeAndExecute(const string& instruction) {
        if (instruction.empty()) {
            return false;
        }

        vector<string> tokens = tokenize(instruction);
        string opcode = tokens[0];

        if (opcode == "LOAD") {
            string reg = tokens[1];
            int value = stoi(tokens[2]);
            registers.set(reg, value);
        } else if (opcode == "ADD") {
            string reg1 = tokens[1], reg2 = tokens[2];
            int result = registers.get(reg1) + registers.get(reg2);
            registers.set("R0", result);
        } else if (opcode == "CALL") {
            int target = stoi(tokens[1]);
            callStack.push(programCounter);
            programCounter = target - 1;
        } else if (opcode == "RET") {
            if (!callStack.empty()) {
                programCounter = callStack.top();
                callStack.pop();
            }
        } else if (opcode == "HLT") {
            return false;
        } else {
            cerr << "Unknown instruction: " << opcode << endl;
        }
        return true;
    }

    vector<string> tokenize(const string& instruction) {
        vector<string> tokens;
        string token;
        for (char c : instruction) {
            if (c == ' ') {
                if (!token.empty()) tokens.push_back(token);
                token.clear();
            } else {
                token += c;
            }
        }
        if (!token.empty()) tokens.push_back(token);
        return tokens;
    }

    void handleInterrupt() {
        cout << "Interrupt triggered! Saving CPU state...\n";
        interruptFlag = false;
    }
};

int main() {
    vector<string> program = {
        "LOAD R1 5",
        "LOAD R2 10",
        "ADD R1 R2",
        "CALL 6",
        "HLT",
        "LOAD R3 20",
        "RET"
    };

    CPU cpu;
    cpu.loadProgram(program);
    cpu.executeProgram();
    cpu.displayState();

    return 0;
}



