#include <iostream>
#include <vector>
#include <string>

class ALU {
public:
    int performOperation(const std::string& operation, int operand1, int operand2) {
        if (operation == "ADD") return operand1 + operand2;
        if (operation == "SUB") return operand1 - operand2;
        if (operation == "AND") return operand1 & operand2;
        if (operation == "OR") return operand1 | operand2;

        std::cerr << "Unknown operation: " << operation << std::endl;
        return 0;
    }
};

class CPU {
    int programCounter;
    int instructionRegister;
public:
    CPU() : programCounter(0), instructionRegister(0) {}

    int getPC() const { return programCounter; }
    void setPC(int value) { programCounter = value; }

    int getIR() const { return instructionRegister; }
    void setIR(int value) { instructionRegister = value; }

    void fetchInstruction(const std::vector<int>& memory) {
        if (programCounter < memory.size()) {
            instructionRegister = memory[programCounter];
            programCounter++;
        } else {
            std::cerr << "Program Counter out of bounds!" << std::endl;
        }
    }
};

class Registers {
    int reg[4];
public:
    Registers() {
        for (int& r : reg) r = 0;
    }

    int getRegister(int index) const {
        if (index >= 0 && index < 4) return reg[index];
        std::cerr << "Invalid register index!" << std::endl;
        return 0;
    }

    void setRegister(int index, int value) {
        if (index >= 0 && index < 4) reg[index] = value;
        else std::cerr << "Invalid register index!" << std::endl;
    }
};

int main() {
    ALU alu;
    Registers regs;
    CPU cpu;

    std::vector<int> memory = {0x020301, 0x050602};

    while (cpu.getPC() < memory.size()) {
        cpu.fetchInstruction(memory);
        int instruction = cpu.getIR();

        int operand1 = (instruction & 0xFF0000) >> 16;
        int operand2 = (instruction & 0x00FF00) >> 8;
        int operationCode = instruction & 0x0000FF;


        std::string operation;
        if (operationCode == 0x01) operation = "ADD";
        else if (operationCode == 0x02) operation = "SUB";
        else {
            std::cerr << "Unknown operation code: " << operationCode << std::endl;
            continue;
        }

        int result = alu.performOperation(operation, operand1, operand2);


        std::cout << "Instruction: 0x" << std::hex << instruction
                  << " [" << operation << " " << operand1 << ", " << operand2 << "] "
                  << "Result: " << std::dec << result << std::endl;
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <bitset>
#include <string>

class ALU {
public:
    int performOperation(const std::string& operation, int operand1, int operand2) {
        if (operation == "ADD") return operand1 + operand2;
        if (operation == "SUB") return operand1 - operand2;
        if (operation == "AND") return operand1 & operand2;
        if (operation == "OR") return operand1 | operand2;

        std::cerr << "Unknown operation: " << operation << std::endl;
        return 0;
    }
};

class CPU {
    int programCounter;
    int instructionRegister;
public:
    CPU() : programCounter(0), instructionRegister(0) {}

    int getPC() const { return programCounter; }
    void setPC(int value) { programCounter = value; }

    int getIR() const { return instructionRegister; }
    void setIR(int value) { instructionRegister = value; }

    void fetchInstruction(const std::vector<int>& memory) {
        if (programCounter < memory.size()) {
            instructionRegister = memory[programCounter];
            programCounter++;
        } else {
            std::cerr << "Program Counter out of bounds!" << std::endl;
        }
    }
};

class Registers {
    int reg[4];
public:
    Registers() {
        for (int& r : reg) r = 0;
    }

    int getRegister(int index) const {
        if (index >= 0 && index < 4) return reg[index];
        std::cerr << "Invalid register index!" << std::endl;
        return 0;
    }

    void setRegister(int index, int value) {
        if (index >= 0 && index < 4) reg[index] = value;
        else std::cerr << "Invalid register index!" << std::endl;
    }
};

int main() {
    ALU alu;
    Registers regs;
    CPU cpu;

    std::vector<int> memory = {0b00000010'00000011'00000001, 0b00000101'00000110'00000010};

    while (cpu.getPC() < memory.size()) {
        cpu.fetchInstruction(memory);
        int instruction = cpu.getIR();

        int operand1 = (instruction & 0xFF0000) >> 16;
        int operand2 = (instruction & 0x00FF00) >> 8;
        int operationCode = instruction & 0x0000FF;

        std::string operation;
        if (operationCode == 0x01) operation = "ADD";
        else if (operationCode == 0x02) operation = "SUB";
        else {
            std::cerr << "Unknown operation code: " << operationCode << std::endl;
            continue;
        }

        int result = alu.performOperation(operation, operand1, operand2);

        std::cout << "Instruction: " << std::bitset<8>((instruction & 0xFF0000) >> 16) << " "
                  << std::bitset<8>((instruction & 0x00FF00) >> 8) << " "
                  << std::bitset<8>(instruction & 0x0000FF) << " "
                  << " [" << operation << " " << std::bitset<8>(operand1) << ", "
                  << std::bitset<8>(operand2) << "] "
                  << "Result: " << std::bitset<8>(result) << std::endl;
    }

    return 0;
}
