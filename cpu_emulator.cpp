#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <vector>
#include<map>
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
    if (inst.opcode == "00") {
        reg = inst.operand1;
    } else if (inst.opcode == "01") {
        reg += inst.operand1;
    } else if (inst.opcode == "10") {
        cout << reg << endl;
    } else if (inst.opcode == "11") {
        reg -= inst.operand1;
    } else if (inst.opcode == "1111") {
        exit(0);
    }
}
map<string, string> opcodeMap = {
    {"LOAD", "00"},
    {"ADD", "01"},
    {"STORE", "10"},
    {"SUB", "11"},
    {"HALT", "1111"}
};

void assemble(string filename) {
    fstream inputFile(filename);
    fstream outputFile("machine_code.txt");

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string opcode, operand1, operand2;
        iss >> opcode >> operand1 >> operand2;
        string machineCode = opcodeMap[opcode] + " " + operand1 + " " + operand2;
        outputFile << machineCode << endl;
    }

    inputFile.close();
    outputFile.close();
}
int main() {
   
    assemble("instructions.txt"); 
    vector<Instruction> instructions = readInstructions("machine_code.txt");
    int reg = 0;  
    int pc = 0;   
    Instruction ir; 
    
    while (pc < instructions.size()) {
        ir = instructions[pc];  
        executeInstruction(ir, reg); 
        pc++;
    }
    return 0;
}
