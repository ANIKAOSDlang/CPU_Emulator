#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

struct Instruction
{
    string opcode;
    int operand1, operand2;
};
class Memory
{
public:
    Memory(int size) : memory(size, 0) {}

    int read(int address)
    {
        return address;
    }

    void write(int address, int value)
    {
        memory[address] = value;
        cout << memory[address] << endl;
    }

private:
    vector<int> memory;
};
vector<Instruction> readInstructions(string filename)
{
    vector<Instruction> instructions;
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        Instruction inst;
        istringstream iss(line);
        iss >> inst.opcode >> inst.operand1 >> inst.operand2;
        instructions.push_back(inst);
    }

    return instructions;
}

void executeInstruction(Instruction &inst, vector<int> &regs, Memory &memory)
{
    int reg_num = 0;
    regs[1] = inst.operand1;

    if (inst.opcode == "00")
    {

        regs[reg_num] = memory.read(regs[1] );
    }
    else if (inst.opcode == "01")
    {

        regs[reg_num] += regs[1] ;
    }
    else if (inst.opcode == "10")
    {
        memory.write(regs[1] , regs[reg_num]);
    }
    else if (inst.opcode == "11")
    {

        regs[reg_num] -= regs[1] ;
    }
    else if (inst.opcode == "000")
    {

        regs[reg_num] &= regs[1] ;
    }
    else if (inst.opcode == "001")
    {

        regs[reg_num] |= regs[1] ;
    }
    else if (inst.opcode == "010")
    {

        regs[reg_num] ^= regs[1] ;
    }
    else if (inst.opcode == "1111")
    {

        exit(0);
    }
}

map<string, string> opcodeMap = {
    {"LOAD", "00"},
    {"ADD", "01"},
    {"STORE", "10"},
    {"SUB", "11"},
    {"AND", "000"},
    {"OR", "001"},
    {"XOR", "010"},
    {"HALT", "1111"}};

void assemble(string filename)
{
    fstream inputFile(filename);
    fstream outputFile("machine_code.txt");

    string line;
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        string opcode, operand1, operand2;
        iss >> opcode >> operand1 >> operand2;
        string machineCode = opcodeMap[opcode] + " " + operand1 + " " + operand2;
        outputFile << machineCode << endl;
    }

    inputFile.close();
    outputFile.close();
}

int main()
{
    assemble("instructions.txt");
    vector<Instruction> instructions = readInstructions("machine_code.txt");

    vector<int> regs(8, 0);
    int pc = 0;
    Instruction ir;
    Memory memory(1024);
    while (pc < instructions.size())
    {
        ir = instructions[pc];
        executeInstruction(ir, regs, memory);
        pc++;
    }
     cout<<pc;
    return 0;
}
