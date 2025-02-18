
#include <iostream>
#include <vector>
#include <bitset>
#include <map>
#include <fstream>
#include <chrono>
using namespace std;

class CPU {
private:
    vector<int> registers;
    map<int, vector<string>> memory;
    int pc;
    bool running;
    ofstream logFile;

public:
    CPU() : registers(8, 0), pc(0), running(true) {
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
            int value;
            cout << "Enter value: ";
            cin >> value;
            registers[reg] = value;
            displayBinary("INPUT", reg);
        } else if (opcode == "OUTPUT") {
            int reg = stoi(instr[1]);
            cout << "OUTPUT R" << reg << " = " << registers[reg] << " (" << bitset<8>(registers[reg]) << ")\n";
            logFile << "OUTPUT R" << reg << " = " << registers[reg] << " (" << bitset<8>(registers[reg]) << ")\n";
        } else if (opcode == "ADD") {
            int r1 = stoi(instr[1]), r2 = stoi(instr[2]), r3 = stoi(instr[3]);
            registers[r1] = registers[r2] + registers[r3];
            displayBinary("ADD", r1);
        } else if (opcode == "SUB") {
            int r1 = stoi(instr[1]), r2 = stoi(instr[2]), r3 = stoi(instr[3]);
            registers[r1] = registers[r2] - registers[r3];
            displayBinary("SUB", r1);
        } else if (opcode == "MUL") {
            int r1 = stoi(instr[1]), r2 = stoi(instr[2]), r3 = stoi(instr[3]);
            registers[r1] = registers[r2] * registers[r3];
            displayBinary("MUL", r1);
        } else if (opcode == "JUMP") {
            int address = stoi(instr[1]);
            pc = address;
        } else if (opcode == "BEQ") {
            int r1 = stoi(instr[1]), r2 = stoi(instr[2]), address = stoi(instr[3]);
            if (registers[r1] == registers[r2]) {
                pc = address;
            }
        } else if (opcode == "LOAD") {
            int r1 = stoi(instr[1]), address = stoi(instr[2]);
            registers[r1] = stoi(memory[address][0]);
            displayBinary("LOAD", r1);
        } else if (opcode == "STORE") {
            int r1 = stoi(instr[1]), address = stoi(instr[2]);
            memory[address] = {to_string(registers[r1])};
        } else if (opcode == "HALT") {
            running = false;
            cout << "CPU HALTED\n";
            logFile << "CPU HALTED\n";
        } else {
            cout << "Unknown instruction: " << opcode << endl;
            logFile << "Unknown instruction: " << opcode << endl;
        }
    }

    void displayBinary(string op, int reg) {
        cout << op << " R" << reg << " = " << registers[reg] << " (" << bitset<8>(registers[reg]) << ")\n";
        logFile << op << " R" << reg << " = " << registers[reg] << " (" << bitset<8>(registers[reg]) << ")\n";
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
