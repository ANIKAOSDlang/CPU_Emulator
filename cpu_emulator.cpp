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
string bitwiseOr(string bin1, string bin2) {
    int n1 = bin1.length();
    int n2 = bin2.length();

    if (n1 < n2) {
        bin1.insert(0, n2 - n1, '0');
    } else if (n2 < n1) {
        bin2.insert(0, n1 - n2, '0');
    }

    int n = max(n1, n2);
    string result = "";

    for (int i = 0; i < n; i++) {
        if (bin1[i] == '1' || bin2[i] == '1') {
            result += '1';
        } else {
            result += '0';
        }
    }

    return result;
}
string binarySubtract(string bin1, string bin2) {
    int n1 = bin1.length();
    int n2 = bin2.length();

    if (n1 < n2) {
        bin1.insert(0, n2 - n1, '0');
    } else if (n2 < n1) {
        bin2.insert(0, n1 - n2, '0');
    }

    int n = max(n1, n2); 
    string result = "";
    int borrow = 0;

    for (int i = n - 1; i >= 0; i--) {
        int bit1 = bin1[i] - '0';
        int bit2 = bin2[i] - '0';

        int diff = bit1 - bit2 - borrow;

        if (diff >= 0) {
            result += to_string(diff);
            borrow = 0;
        } else {
            result += to_string(diff + 2); 
            borrow = 1;
        }
    }

    reverse(result.begin(), result.end()); 

    int firstOne = result.find_first_not_of('0');
    if (firstOne == string::npos) {
        return "0"; 
    }
    return result.substr(firstOne);
}
string addBinary(string a, string b) {
    string result = "";
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int bitA = (i >= 0) ? (a[i] - '0') : 0;
        int bitB = (j >= 0) ? (b[j] - '0') : 0;

        int sum = bitA + bitB + carry;

        result += (sum % 2) + '0'; 
        carry = sum / 2;

        i--;
        j--;
    }

    reverse(result.begin(), result.end());
    return result;
}
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

void executeInstruction(Instruction &inst, vector<string> &regs, Memory &memory, int &pc)
{
    string *reg;
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

    regs[1] = inst.operand2; // Value always stores to R1 register

    if (inst.opcode == "00") // load
    {

        cout << binaryToDecimal(memory.write("0001", inst.operand2)) << endl;
    }
    else if (inst.opcode == "01") // add
    {

        *reg =addBinary(*reg, regs[1]);
    }
    else if (inst.opcode == "10") // store
    {
        memory.write(reg_name, *reg);
    }
    else if (inst.opcode == "11") // sub
    {

        *reg =binarySubtract(*reg, regs[1]);
    }
    else if (inst.opcode == "000") // and
    {

        *reg = bitwiseOr(*reg,reg[1]);
    }
    else if (inst.opcode == "001") // or
    {

        //*reg |= regs[1];
    }
    else if (inst.opcode == "010") // xor
    {

        //*reg ^= regs[1];
    }
    else if (inst.opcode == "100") // integer input
    {
        cout << "Enter an integer: ";
        int input;
        cin>>input;
        decToBinary(input,reg[1]);
        cout << reg[1] << endl;

        memory.write(reg_name, reg[1]);
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
        pc++;
        pc = binaryToDecimal((inst.operand2));
    }
    else if (inst.opcode == "111") // JR
    {
        pc = binaryToDecimal(*reg);
    }
    else if (inst.opcode == "1000")//MOV
    {
        string val = memory.read(inst.operand2);
        if (val != "")
        {
            *reg = val;
            memory.write(reg_name, *reg);
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
        cout << binaryToDecimal(*reg) << endl;
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

    vector<string> regs(8, "");
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
