#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Instruction {
    string opcode;
    int operand1,operand2;
};

vector<Instruction> readInstructions(string filename) {
    vector<Instruction> instructions;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        Instruction inst;
        istringstream iss(line);
        iss >> inst.opcode >> inst.operand1 >> inst.operand2;
        instructions.push_back(inst);
    }

    return instructions;
}

void executeInstruction(Instruction& inst, int& reg) {
    if (inst.opcode == "LOAD") {
        reg = inst.operand1;
    } else if (inst.opcode == "ADD") {
        reg += inst.operand1;
    } else if (inst.opcode == "STORE") {
        cout << reg << endl;
    } else if (inst.opcode == "SUB") {
        reg -= inst.operand1;
    } else if (inst.opcode == "HALT") {
        exit(0);
    }
}

int main() {
    int reg = 0;
    vector<Instruction> instructions = readInstructions("instructions.txt");

    for (Instruction& inst : instructions) {
        executeInstruction(inst, reg);
    }

    return 0;
}
