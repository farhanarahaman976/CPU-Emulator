#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <bitset>
using namespace std;

unordered_map<string, int> opcodes = { {"ADD", 1}, {"SUB", 2}, {"LOAD", 3}, {"STORE", 4} };
unordered_map<string, int> registers = { {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3} };

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
    int perform(const string &op, int a, int b) {
        if(op == "ADD") return a + b;
        if(op == "SUB") return a - b;
        return 0;
    }
};

class CPU {
public:
    int PC, IR;
    CPU() : PC(0), IR(0) {}
    void fetch(const vector<int>& mem) {
        if(PC < mem.size()) { IR = mem[PC]; PC++; }
        else { cerr << "PC out of bounds!" << endl; }
    }
};

class Registers {
public:
    int reg[4];
    Registers() { for (int i = 0; i < 4; i++) reg[i] = 0; }
};

int main(){
    vector<string> assembly = {
        "LOAD R1 5",   
        "LOAD R2 10", 
        "ADD R1 R2",   
        "SUB R2 R1",    
        "STORE R1 20"   
    };

    vector<int> memory;
    cout << "Assembled Machine Code (24-bit in 8-bit groups):" << endl;
    for(auto &line : assembly) {
        int code = assembleInstruction(line);
        memory.push_back(code);
        bitset<24> bs(code);
        string s = bs.to_string();
        cout << line << " -> " << s.substr(0,8) << " " << s.substr(8,8) << " " << s.substr(16,8) << endl;
    }
    cout << endl;

    ALU alu;
    CPU cpu;
    Registers regs;

    while(cpu.PC < memory.size()){
        cpu.fetch(memory);
        int instr = cpu.IR;
        int regNum = (instr >> 16) & 0xFF;      
        int operand = (instr >> 8) & 0xFF;      
        int opcode = instr & 0xFF;                

        string op;
        if(opcode == 1) op = "ADD";
        else if(opcode == 2) op = "SUB";
        else if(opcode == 3) op = "LOAD";
        else if(opcode == 4) op = "STORE";
        else {
            cerr << "Unknown opcode: " << opcode << endl;
            continue;
        }

        if(op == "LOAD"){
            regs.reg[regNum] = operand;
            cout << "Executed LOAD: R" << regNum << " = " << bitset<8>(operand) << endl;
        }
        else if(op == "STORE"){
            cout << "Executed STORE: R" << regNum << " value ("
                 << bitset<8>(regs.reg[regNum]) << ") stored at address "
                 << bitset<8>(operand) << endl;
        }
        else if(op == "ADD"){
            int result = alu.perform(op, regs.reg[regNum], regs.reg[operand]);
            regs.reg[regNum] = result;
            cout << "Executed ADD: R" << regNum << " = " << bitset<8>(result) << endl;
        }
        else if(op == "SUB"){
            int result = alu.perform(op, regs.reg[regNum], regs.reg[operand]);
            regs.reg[regNum] = result;
            cout << "Executed SUB: R" << regNum << " = " << bitset<8>(result) << endl;
        }
    }

    return 0;
}
