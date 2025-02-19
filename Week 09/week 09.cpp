#include <iostream>
#include <vector>
#include <bitset>
#include <map>
#include <fstream>
#include <chrono>
using namespace std;

class CPU {
private:
    vector<bitset<8>> registers;
    map<int, vector<string>> memory;
    int pc;
    bool running;
    ofstream logFile;

public:
    CPU() : registers(8), pc(0), running(true) {
        logFile.open("cpu_log.txt");
    }

    ~CPU() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void loadProgram(const vector<vector<string>>& program) {
        for (size_t i = 0; i < program.size(); i++) {
            memory[i] = program[i];
        }
    }

    void execute() {
        auto start_time = chrono::high_resolution_clock::now();
        while (running && memory.find(pc) != memory.end()) {
            vector<string> instruction = memory[pc++];
            processInstruction(instruction);
        }
        auto end_time = chrono::high_resolution_clock::now();
        chrono::duration<double> execution_time = end_time - start_time;
        logFile << "Execution Time: " << execution_time.count() << " seconds" << endl;
        cout << "Execution Time: " << execution_time.count() << " seconds" << endl;
    }

    void processInstruction(const vector<string>& instr) {
        string opcode = instr[0];

        if (opcode == "INPUT") {
            int reg = stoi(instr[1]);
            string binary_value;
            cout << "Enter binary value (8-bit): ";
            cin >> binary_value;
            registers[reg] = bitset<8>(binary_value); 
            displayBinary("INPUT", reg);
        }
        else if (opcode == "OUTPUT") {
            int reg = stoi(instr[1]);
            cout << "OUTPUT R" << reg << " = " << registers[reg] << endl;
            logFile << "OUTPUT R" << reg << " = " << registers[reg] << endl;
        }
        else if (opcode == "ADD") {
            int r1 = stoi(instr[1]), r2 = stoi(instr[2]), r3 = stoi(instr[3]);
            registers[r1] = bitset<8>(registers[r2].to_ulong() + registers[r3].to_ulong()); 
            displayBinary("ADD", r1);
        }
        else if (opcode == "SUB") {
            int r1 = stoi(instr[1]), r2 = stoi(instr[2]), r3 = stoi(instr[3]);
            registers[r1] = bitset<8>(registers[r2].to_ulong() - registers[r3].to_ulong()); 
            displayBinary("SUB", r1);
        }
        else if (opcode == "MUL") {
            int r1 = stoi(instr[1]), r2 = stoi(instr[2]), r3 = stoi(instr[3]);
            registers[r1] = bitset<8>(registers[r2].to_ulong() * registers[r3].to_ulong()); 
            displayBinary("MUL", r1);
        }
        else if (opcode == "JUMP") {
            int address = stoi(instr[1]);
            pc = address;
        }
        else if (opcode == "BEQ") {
            int r1 = stoi(instr[1]), r2 = stoi(instr[2]), address = stoi(instr[3]);
            if (registers[r1] == registers[r2]) {
                pc = address;
            }
        }
        else if (opcode == "LOAD") {
            int r1 = stoi(instr[1]), address = stoi(instr[2]);
            registers[r1] = bitset<8>(memory[address][0]); 
            displayBinary("LOAD", r1);
        }
        else if (opcode == "STORE") {
            int r1 = stoi(instr[1]), address = stoi(instr[2]);
            memory[address] = {registers[r1].to_string()};
        }
        else if (opcode == "HALT") {
            running = false;
            cout << "CPU HALTED\n";
            logFile << "CPU HALTED\n";
        }
        else {
            cout << "Unknown instruction: " << opcode << endl;
            logFile << "Unknown instruction: " << opcode << endl;
        }
    }

    void displayBinary(string op, int reg) {
        cout << op << " R" << reg << " = " << registers[reg] << endl;
        logFile << op << " R" << reg << " = " << registers[reg] << endl;
    }
};

int main() {
    CPU cpu;
    vector<vector<string>> program = {
        {"INPUT", "0"},
        {"INPUT", "1"},
        {"ADD", "2", "0", "1"},
        {"OUTPUT", "2"},
        {"MUL", "3", "0", "1"},
        {"OUTPUT", "3"},
        {"SUB", "4", "0", "1"},
        {"OUTPUT", "4"},
        {"STORE", "2", "10"},
        {"LOAD", "5", "10"},
        {"OUTPUT", "5"},
        {"JUMP", "14"},
        {"INPUT", "6"},
        {"BEQ", "6", "0", "16"},
        {"HALT"}
    };

    cpu.loadProgram(program);
    cpu.execute();
    return 0;
}
