#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <bitset>
using namespace std;

unordered_map<string, int> opcodes = { {"ADD", 1}, {"SUB", 2}, {"LOAD", 3}, {"STORE", 4}, {"HALT", 5} };
unordered_map<string, int> registers = { {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3}, {"R4", 4}, {"R5", 5}, {"R6", 6}, {"R7", 7} };

int assembleInstruction(const string &inst) {
    istringstream iss(inst);
    string op, reg, operandStr;
    iss >> op >> reg >> operandStr;

    int opcode = opcodes[op];
    int regNum = registers[reg];
    int operand = (registers.find(operandStr) != registers.end()) ? registers[operandStr] : stoi(operandStr);

    return (regNum << 16) | ((operand & 0xFF) << 8) | (opcode & 0xFF);
}

class ALU {
public:
    int execute(const string& operation, int operand1, int operand2 = 0) {
        if (operation == "ADD") return operand1 + operand2;
        if (operation == "SUB") return operand1 - operand2;
        if (operation == "LOAD") return operand1;
        if (operation == "HALT") return 0;
        throw invalid_argument("Unknown operation: " + operation);
    }
};

class CPU {
private:
    int PC;
    vector<int> memory;
    int IR;
    vector<int> registers;
    ALU alu;

public:
    CPU(const vector<int>& program) : PC(0), memory(program), registers(8, 0) {}

    void fetch() {
        if (PC < memory.size()) {
            IR = memory[PC];
            cout << "Fetched instruction: " << bitset<24>(IR) << " from address " << PC << endl;
            PC++;
        } else {
            IR = 0;
        }
    }

    bool decodeAndExecute() {
        if (IR == 0) return false;

        int regNum = (IR >> 16) & 0xFF;
        int operand = (IR >> 8) & 0xFF;
        int opcode = IR & 0xFF;

        string op;
        if (opcode == 1) op = "ADD";
        else if (opcode == 2) op = "SUB";
        else if (opcode == 3) op = "LOAD";
        else if (opcode == 4) op = "STORE";
        else if (opcode == 5) op = "HALT";
        else {
            cout << "Unknown instruction encountered!" << endl;
            return false;
        }

        if (op == "LOAD") {
            registers[regNum] = alu.execute(op, operand);
            cout << "Executed LOAD: R" << regNum << " = " << bitset<8>(registers[regNum]) << endl;
        }
        else if (op == "STORE") {
            cout << "Executed STORE: R" << regNum << " value (" << bitset<8>(registers[regNum]) << ") stored." << endl;
        }
        else if (op == "ADD" || op == "SUB") {
            registers[regNum] = alu.execute(op, registers[regNum], registers[operand]);
            cout << "Executed " << op << ": R" << regNum << " = " << bitset<8>(registers[regNum]) << endl;
        }
        else if (op == "HALT") {
            cout << "Execution Halted." << endl;
            return false;
        }

        return true;
    }
};

int main() {
    vector<string> assembly = {
        "LOAD R1 17",
        "LOAD R2 23",
        "ADD R3 R1 R2",
        "STORE R3 30",
        "HALT"
    };

    vector<int> machineCode;
    cout << "Assembled Machine Code (24-bit in 8-bit groups):" << endl;
    for (const auto &line : assembly) {
        int code = assembleInstruction(line);
        machineCode.push_back(code);
        bitset<24> bs(code);
        cout << line << " -> " << bs.to_string().substr(0, 8) << " " << bs.to_string().substr(8, 8) << " " << bs.to_string().substr(16, 8) << endl;
    }
    cout << endl;

    CPU cpu(machineCode);
    while (true) {
        cpu.fetch();
        if (!cpu.decodeAndExecute()) break;
    }

    return 0;
}

    return 0;
}

