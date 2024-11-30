#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
using namespace std;

class ALU {
public:
    int execute(const string& operation, int operand1, int operand2 = 0) {
        if (operation == "ADD") {
            return operand1 + operand2;
        } else if (operation == "SUB") {
            return operand1 - operand2;
        } else if (operation == "LOAD") {
            return operand1;
        } else if (operation == "HALT") {
            return 0;
        } else {
            throw invalid_argument("Unknown operation: " + operation);
        }
    }
};

class CPU {
private:
    int PC;
    vector<string> memory;
    string IR;
    vector<int> registers;
    ALU alu;

public:
    CPU(const vector<string>& program)
        : PC(0), memory(program), registers(8, 0) {}

    void fetch() {
        if (PC < memory.size()) {
            IR = memory[PC];
            cout << "Fetched instruction: " << IR << " from address " << PC << endl;
            PC++;
        } else {
            IR = "";
        }
    }

    bool decodeAndExecute() {
        if (IR.empty()) return false;

        stringstream ss(IR);
        string op;
        ss >> op;

        if (op == "HALT") {
            cout << "HALT encountered. Stopping execution." << endl;
            return false;
        }

        string reg;
        ss >> reg;
        int regIndex = reg[1] - '0';

        if (op == "ADD" || op == "SUB") {
            string reg1, reg2;
            ss >> reg1 >> reg2;
            int src1 = reg1[1] - '0';
            int src2 = reg2[1] - '0';
            registers[regIndex] = alu.execute(op, registers[src1], registers[src2]);
        } else if (op == "LOAD") {
            int value;
            ss >> value;
            registers[regIndex] = alu.execute(op, value);
        } else if (op == "STORE") {
            cout << "Stored value: " << registers[regIndex] << endl;
        } else {
            cout << "Unknown instruction: " << IR << endl;
        }

        return true;
    }
};

int main() {
    vector<string> program = {
        "LOAD R1 17",
        "LOAD R2 23",
        "ADD R3 R1 R2",
        "STORE R3",
        "HALT"
    };

    CPU cpu(program);

    while (true) {
        cpu.fetch();
        if (!cpu.decodeAndExecute()) {
            break;
        }
    }

    return 0;
}

