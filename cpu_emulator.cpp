#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
int binaryToDecimal(string binary)
{
    int decimal = 0;
    int power = 0;

    for (int i = binary.size() - 1; i >= 0; i--)
    {
        if (binary[i] == '1')
        {
            decimal += pow(2, power);
        }
        power++;
    }

    return decimal;
}
void decToBinary(int n, vector<int> &binaryNum)
{

    while (n > 0)
    {
        binaryNum.push_back(n % 2);
        n /= 2;
    }
    reverse(binaryNum.begin(), binaryNum.end());
}
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

    regs[1] = binaryToDecimal(to_string(inst.operand1));

    if (inst.opcode == "00")
    {

        regs[0] = memory.read(regs[1]);
    }
    else if (inst.opcode == "01")
    {

        regs[0] += regs[1];
    }
    else if (inst.opcode == "10")
    {
        memory.write(regs[1], regs[0]);
    }
    else if (inst.opcode == "11")
    {

        regs[0] -= regs[1];
    }
    else if (inst.opcode == "000")
    {

        regs[0] &= regs[1];
    }
    else if (inst.opcode == "001")
    {

        regs[0] |= regs[1];
    }
    else if (inst.opcode == "010")
    {

        regs[0] ^= regs[1];
    }
    else if (inst.opcode == "100")
    {
        cout << "Enter an integer: ";
        cin >> regs[1];
        vector<int> binaryNum;
        string binary_num = "";
        decToBinary(regs[1], binaryNum);
        for (int num : binaryNum)
        {
            binary_num += to_string(num);
        }

        cout << binary_num << endl;

        regs[0] = memory.read(regs[1]);
    }
    else if (inst.opcode == "110")
    {
        string value;
        cout << "Enter a string: ";
        cin >> value;
        cout << value;
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
    {"INPUT_INT", "100"},
    {"INPUT_STRING", "110"},
    {"HALT", "1111"},
};

void assemble(string filename)
{
    fstream inputFile(filename);
    fstream outputFile("machine_code.txt");

    string line;
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        vector<int> binaryNum;

        string opcode, operand1 = "", operand2 = "";
        iss >> opcode >> operand1 >> operand2;
        if (operand1 != "")
        {
            int num;
            stringstream ss(operand1);
            ss >> num;
            decToBinary(num, binaryNum);
            operand1 = "";
            for (int num : binaryNum)
            {
                operand1 += to_string(num);
            }
        }
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
    };

    return 0;
}
