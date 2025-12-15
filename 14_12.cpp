#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

const string FILENAME = "input_file.txt";

string trimAndSquashSpaces(const string& line) {
    size_t first = line.find_first_not_of(' ');
    if (string::npos == first) {
        return "";
    }
    size_t last = line.find_last_not_of(' ');
    string trimmed = line.substr(first, (last - first + 1));

    stringstream ss(trimmed);
    string word;
    string result = "";

    while (ss >> word) {
        if (!result.empty()) {
            result += " ";
        }
        result += word;
    }

    return result;
}

bool createFile(int N, const string& filename) {
    ofstream outFile(filename, ios::out);

    if (!outFile.is_open()) {
        cerr << "Error! Failed to open file for writing: " << filename << endl;
        return false;
    }

    for (int i = 1; i <= N; ++i) {
        string content;
        switch (i % 3) {
            case 1:
                content = "  This is line " + to_string(i) + " with extra spaces.  ";
                break;
            case 2:
                content = "  Start and End  ";
                break;
            default:
                content = "  Only spaces between words.  ";
                break;
        }
        outFile << content << endl;
    }

    outFile.close();
    cout << "File '" << filename << "' successfully created with " << N << " lines." << endl;
    return true;
}

bool processFile(const string& filename) {
    const string TEMP_FILENAME = filename + ".tmp";

    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error! Failed to open input file: " << filename << endl;
        return false;
    }

    ofstream outFile(TEMP_FILENAME);
    if (!outFile.is_open()) {
        cerr << "Error! Failed to create temporary file: " << TEMP_FILENAME << endl;
        inFile.close();
        return false;
    }

    string line;
    int lineCount = 0;

    while (getline(inFile, line)) {
        lineCount++;
        string cleanedLine = trimAndSquashSpaces(line);
        outFile << cleanedLine << endl;
    }

    inFile.close();
    outFile.close();

    if (remove(filename.c_str()) != 0) {
        cerr << "Error! Failed to delete original file: " << filename << endl;
        return false;
    }
    if (rename(TEMP_FILENAME.c_str(), filename.c_str()) != 0) {
        cerr << "Error! Failed to rename temporary file to: " << filename << endl;
        return false;
    }

    cout << "File '" << filename << "' successfully processed (" << lineCount << " lines cleaned)." << endl;
    return true;
}

void printFileContent(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Failed to open file for content output." << endl;
        return;
    }
    cout << "\n--- Content of file '" << filename << "' ---\n";
    string line;
    while (getline(file, line)) {
        cout << "[" << line << "]" << endl;
    }
    cout << "--------------------------------------\n";
    file.close();
}

int main() {
    int N = 5;

    cout << "--- Starting File Processing Program ---\n";

    if (!createFile(N, FILENAME)) {
        return 1;
    }

    printFileContent(FILENAME);

    if (!processFile(FILENAME)) {
        return 1;
    }

    printFileContent(FILENAME);

    cout << "--- Program finished ---\n";
    return 0;
}