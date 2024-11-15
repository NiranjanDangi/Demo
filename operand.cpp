#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void checkOperandErrors(const vector<string>& mainMemory) {
    for (size_t i = 0; i < mainMemory.size(); i++) {
        int operandCount = 0;
        stringstream ss(mainMemory[i]);
        string token;

        // Count tokens after the opcode as operands
        while (getline(ss, token, ' ')) {
            if (!token.empty()) {
                operandCount++;
            }
        }

        if (operandCount < 3) {  // Opcode + 2 operands
            cout << "Operand error at address " << i << ": Missing operand(s) in instruction '" << mainMemory[i] << "'" << endl;
        }
    }
}

int main() {
    vector<string> mainMemory = {
        "LOAD R1, 100",
        "STORE R2",  // Missing operand for testing
        "ADD R1, R2",
        "SUB R3"  // Missing operand for testing
    };

    checkOperandErrors(mainMemory);
    return 0;
}
