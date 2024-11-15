#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void copyFileCharacterByCharacter(const string& sourceFile, const string& destFile) {
    ifstream src(sourceFile);
    ofstream dest(destFile);
    if (!src || !dest) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    char ch;
    while (src.get(ch)) dest.put(ch);
    cout << "File copied character by character successfully." << endl;
}

void copyFileLineByLine(const string& sourceFile, const string& destFile) {
    ifstream src(sourceFile);
    ofstream dest(destFile);
    if (!src || !dest) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    string line;
    while (getline(src, line)) dest << line << '\n';
    cout << "File copied line by line successfully." << endl;
}

int main() {
    // Hardcoded file names
    string sourceFile = "source.txt";
    string destFileChar = "dest_char_copy.txt";
    string destFileLine = "dest_line_copy.txt";

    cout << "\nCopying file character by character...\n";
    copyFileCharacterByCharacter(sourceFile, destFileChar);

    cout << "\nCopying file line by line...\n";
    copyFileLineByLine(sourceFile, destFileLine);

    return 0;
}
