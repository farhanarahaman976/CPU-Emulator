#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <bitset>
#include <vector>

using namespace std;

const unordered_map<string, string> OPCODES = {
    {"ADD", "0001"},
    {"SUB", "0010"},
    {"LOAD", "0011"},
    {"STORE", "0100"}
};

const unordered_map<string, string> REGISTERS = {
    {"R0", "0000"},
    {"R1", "0001"},
    {"R2", "0010"},
    {"R3", "0011"}
};

string assembleInstruction(const string &instruction) {
    stringstream ss(instruction);
    string opcode, reg1, reg2_or_imm;
    ss >> opcode >> reg1 >> reg2_or_imm;

    string binaryInstruction;

    if (OPCODES.find(opcode) == OPCODES.end()) {
        cerr << "Error: Unknown opcode " << opcode << endl;
        return "";
    }
    binaryInstruction += OPCODES.at(opcode);

    if (REGISTERS.find(reg1) == REGISTERS.end()) {
        cerr << "Error: Unknown register " << reg1 << endl;
        return "";
    }
    binaryInstruction += REGISTERS.at(reg1);

    if (REGISTERS.find(reg2_or_imm) != REGISTERS.end()) {
        binaryInstruction += REGISTERS.at(reg2_or_imm);
    } else {
        int immediateValue = stoi(reg2_or_imm);
        if (immediateValue < 0 || immediateValue > 15) {
            cerr << "Error: Immediate value out of range: " << reg2_or_imm << endl;
            return "";
        }
        binaryInstruction += bitset<4>(immediateValue).to_string();
    }

    while (binaryInstruction.size() < 16) {
        binaryInstruction += "0";
    }

    return binaryInstruction;
}

int main() {
    vector<string> assemblyCode = {
        "LOAD R1 5",
        "ADD R1 R2",
        "SUB R2 R3",
        "STORE R1 10"
    };

    ofstream outFile("machine_code.txt");
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }

    cout << "Machine Code Output (8-bit format):" << endl;

    for (const string &instruction : assemblyCode) {
        string machineCode = assembleInstruction(instruction);
        if (!machineCode.empty()) {
            cout << instruction << " -> " << machineCode.substr(0, 8) << " " << machineCode.substr(8, 8) << endl;
            outFile << machineCode.substr(0, 8) << " " << machineCode.substr(8, 8) << endl;
        }
    }

    outFile.close();
    cout << "Machine code written to machine_code.txt" << endl;

    return 0;
}
