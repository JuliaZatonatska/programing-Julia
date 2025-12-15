#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

int get_precision(double num) {
    stringstream ss;
    ss << fixed << setprecision(15) << num;
    string s = ss.str();

    size_t decimal_pos = s.find('.');

    if (decimal_pos == string::npos) {
        return 0;
    }

    size_t trailing_zeros = 0;
    for (int i = s.length() - 1; i > (int)decimal_pos; --i) {
        if (s[i] == '0') {
            trailing_zeros++;
        } else {
            break;
        }
    }

    if (decimal_pos + 1 == s.length() - trailing_zeros) {
        return 0;
    }

    return s.length() - decimal_pos - 1 - trailing_zeros;
}

int main() {
    string input_path;
    string output_path;

    cout << "Enter the full path to the INPUT file (e.g., C:\\Data\\input.txt):" << endl;
    getline(cin, input_path);

    cout << "Enter the full path for CREATING the OUTPUT file (e.g., C:\\Data\\output.txt):" << endl;
    getline(cin, output_path);

    ifstream inputFile(input_path);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the input file at path: " << input_path << endl;
        cerr << "Ensure the file exists and the path is correct." << endl;
        return 1;
    }

    cout << "File successfully opened for reading." << endl;

    string file_content((istreambuf_iterator<char>(inputFile)),
                            istreambuf_iterator<char>());

    inputFile.close();

    replace(file_content.begin(), file_content.end(), ';', ' ');

    stringstream ss(file_content);

    vector<double> numbers;
    double current_number;

    while (ss >> current_number) {
        numbers.push_back(current_number);
    }

    if (numbers.empty()) {
        cout << "The file is empty or does not contain valid numbers." << endl;
        return 0;
    }

    cout << "Read " << numbers.size() << " numbers." << endl;

    int max_precision = 0;

    for (double num : numbers) {
        int current_precision = get_precision(num);
        if (current_precision > max_precision) {
            max_precision = current_precision;
        }
    }

    cout << "Found maximum precision: " << max_precision << " decimal places." << endl;

    ofstream outputFile(output_path);

    if (!outputFile.is_open()) {
        cerr << "Error: Could not open the output file for writing: " << output_path << endl;
        cerr << "Check folder access permissions." << endl;
        return 2;
    }

    outputFile << fixed << setprecision(max_precision);

    for (double num : numbers) {
        double result_num;

        if (num < 0) {
            result_num = abs(num);
        } else {
            result_num = num;
        }

        outputFile << result_num << "\n";
    }

    outputFile.close();

    cout << "\n✅ Data successfully written to file: " << output_path << endl;
    cout << "Each number is written on a new line with a precision of " << max_precision << "." << endl;

    return 0;
}