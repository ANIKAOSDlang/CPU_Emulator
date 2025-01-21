#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
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
    {"BEQ", "011"},
    {"JAL", "101"},
    {"JR", "111"},
    {"R0", "0000"},
    {"R1", "0001"},
    {"R2", "0010"},
    {"R3", "0011"},
    {"R4", "0100"},
    {"R5", "0101"},
    {"R6", "0110"},
    {"R7", "0111"},
    {"MOV", "1000"},
    {"DIS", "1001"}};

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
void decToBinary(int n, string &binary_value)
{

    vector<int> binaryNum;

    while (n > 0)
    {
        binaryNum.push_back(n % 2);
        n /= 2;
    }
    reverse(binaryNum.begin(), binaryNum.end());
    for (int num : binaryNum)
    {
        binary_value += to_string(num);
    }
}
struct Instruction
{
    string opcode, operand1, operand2;
};
class Memory
{
public:
    int num = 0;
    vector<pair<string, string>> memory;

    Memory(int size) : memory(size) {}

    string read(string address)
    {
        int val;
        val = findPairIndex(address);
        if (val != -1)
        {
            return memory[val].second;
        }
        else
        {
            return "";
        }
    }
    int findPairIndex(string searchValue)
    {
        auto it = find_if(memory.begin(), memory.end(),
                          [searchValue](const pair<string, string> &p)
                          {
                              return p.first == searchValue;
                          });

        if (it != memory.end())
        {
            return distance(memory.begin(), it);
        }
        else
        {
            return -1;
        }
    }

    string write(string address, string value)
    {
        int val;
        val = findPairIndex(address);
        if (val != -1)
        {
            memory[val].second = value;
            return memory[val].second;
        }

        else
        {
            memory.push_back({address, value});
            return memory.back().second;
        }
    }
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

void executeInstruction(Instruction &inst, vector<int> &regs, Memory &memory, int &pc)
{
    int *reg;
    string reg_name = "";
    if (inst.operand1 == "0000")
    {
        reg = &regs[0];
        reg_name = inst.operand1;
    }
    else if (inst.operand1 == "0001")
    {
        reg = &regs[1];
        reg_name = inst.operand1;
    }
    else if (inst.operand1 == "0010")
    {
        reg = &regs[2];
        reg_name = inst.operand1;
    }
    else if (inst.operand1 == "0011")
    {
        reg = &regs[3];
        reg_name = inst.operand1;
    }
    else if (inst.operand1 == "0100")
    {
        reg = &regs[4];
        reg_name = inst.operand1;
    }
    else if (inst.operand1 == "0101")
    {
        reg = &regs[5];
        reg_name = inst.operand1;
    }
    else if (inst.operand1 == "0110")
    {
        reg = &regs[6];
        reg_name = inst.operand1;
    }
    else if (inst.operand1 == "0111")
    {
        reg = &regs[7];
        reg_name = inst.operand1;
    }

    regs[1] = binaryToDecimal(inst.operand2); // Value always stores to R1 register

    if (inst.opcode == "00") // load
    {

        cout << binaryToDecimal(memory.write("0001", inst.operand2)) << endl;
    }
    else if (inst.opcode == "01") // add
    {

        *reg += regs[1];
    }
    else if (inst.opcode == "10") // store
    {
        string binary_value = "";
        decToBinary(*reg, binary_value);
        memory.write(reg_name, binary_value);
    }
    else if (inst.opcode == "11") // sub
    {

        *reg -= regs[1];
    }
    else if (inst.opcode == "000") // and
    {

        *reg &= regs[1];
    }
    else if (inst.opcode == "001") // or
    {

        *reg |= regs[1];
    }
    else if (inst.opcode == "010") // xor
    {

        *reg ^= regs[1];
    }
    else if (inst.opcode == "100") // integer input
    {
        cout << "Enter an integer: ";
        cin >> regs[1];
        string binary_value = "";
        decToBinary(regs[1], binary_value);
        cout << binary_value << endl;

        memory.write(reg_name, binary_value);
    }
    else if (inst.opcode == "110")//string input
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
    else if (inst.opcode == "011") // BEQ
    {
        if (regs[0] == *reg)
        {
            pc = binaryToDecimal((inst.operand2));
        }
    }
    else if (inst.opcode == "101") // JAL
    {
        *reg = pc + 1;
        pc = binaryToDecimal((inst.operand2));
    }
    else if (inst.opcode == "111") // JR
    {
        pc = *reg;
    }
    else if (inst.opcode == "1000")//MOV
    {
        string val = memory.read(inst.operand2);
        if (val != "")
        {
            *reg = binaryToDecimal(val);
            memory.write(reg_name, val);
        }
        else
        {
            cout << "Error! Value does not exist " << endl
            <<"Code exit with value 0"<<endl;
            exit(0);
        }
    }
    else if (inst.opcode == "1001")//display
    {
        cout << *reg << endl;
    }
    else
    {
        cout<<"Error in line: "<<pc+1<<endl
        <<"Invalid code input"<<endl;
        exit(0);
    }
}


void assemble(string filename)
{
    fstream inputFile(filename);
    fstream outputFile("machine_code.txt");

    string line;
    while (getline(inputFile, line))
    {
        istringstream iss(line);

        string opcode, operand1 = "", operand2 = "", machineCode = "";
        iss >> opcode >> operand1 >> operand2;
        try
        {
            int check = stoi(operand2);
            operand2 = "";
            decToBinary(check, operand2);
            machineCode = opcodeMap[opcode] + " " + opcodeMap[operand1] + " " + operand2;
        }
        catch (const std::exception &e)
        {
            machineCode = opcodeMap[opcode] + " " + opcodeMap[operand1] + " " + opcodeMap[operand2];
        }

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
        executeInstruction(ir, regs, memory, pc);
        pc++;
    };
    /*for(int i=0;i<memory.memory.size();i++)
       {
        cout<<memory.memory[i].first<<" "<<memory.memory[i].second<<endl;
       }
        return 0;*/
}
