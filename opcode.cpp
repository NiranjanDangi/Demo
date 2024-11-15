#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

const vector<string> validOpcodes = {"LOAD", "STORE", "ADD", "SUB", "JMP", "HALT"};

bool isValidOpcode(const string& opcode) {
    for (const auto& validOpcode : validOpcodes) {
        if (opcode == validOpcode) {
            return true;
        }
    }
    return false;
}

void checkOpcodeErrors(const vector<string>& mainMemory) {
    for (size_t i = 0; i < mainMemory.size(); i++) {
        string opcode;
        stringstream ss(mainMemory[i]);
        ss >> opcode;  // Extract the first word as opcode
        if (!isValidOpcode(opcode)) {
            cout << "Opcode error at address " << i << ": Invalid opcode '" << opcode << "'" << endl;
        }
    }
}

int main() {
    vector<string> mainMemory = {
        "LOAD R1, 100",
        "STOREE R2, 200",  // Invalid opcode for testing
        "ADD R1, R2",
        "INVALID_OP R3, 300"  // Invalid opcode for testing
    };

    checkOpcodeErrors(mainMemory);
    return 0;
}
