#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void loadAlpToMemory(const string& filePath) {
    vector<string> mainMemory;
    ifstream file(filePath);

    if (!file) {
        cout << "Error: Input file not found." << endl;
        return;
    }

    string line;
    while (getline(file, line) && mainMemory.size() < 100) {
        mainMemory.push_back(line);
    }
    file.close();

    cout << "ALP Program loaded into main memory:" << endl;
    for (int i = 0; i < mainMemory.size(); i++) {
        cout << "Address " << i << ": " << mainMemory[i] << endl;
    }
}

int main() {
    loadAlpToMemory("alp_program.txt");
    return 0;
}
