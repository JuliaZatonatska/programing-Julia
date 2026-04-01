#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

const string INPUT_FILENAME_TASK7 = "input_data.txt";
const string OUTPUT_FILENAME_TASK7 = "output_results.txt";
using NaturalNumber = unsigned long long;

void inputRealNumbersTask1(double &x, double &y) {
    cout << "TASK 1: Power Calculation\n";
    cout << "Enter a real number x (base): ";
    cin >> x;
    cout << "Enter a real number y (exponent): ";
    cin >> y;
}

double calculatePowerTask1(double base, double exponent) {
    return pow(base, exponent);
}

void outputResultTask1(double result) {
    cout << "\nResult x^y (Decimal): ";
    cout << fixed << setprecision(10) << result << endl;
    cout << "Result x^y (Scientific): ";
    cout << scientific << setprecision(4) << result << endl;
}

void runTask1() {
    double x = 0.0;
    double y = 0.0;

    inputRealNumbersTask1(x, y);
    double powerResult = calculatePowerTask1(x, y);
    outputResultTask1(powerResult);
}

int inputNTask2() {
    int n = 0;
    cout << "TASK 2: Sum of Large Numbers\n";
    cout << "Enter the count of numbers (n): ";
    cin >> n;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return n;
}

void inputNumbersTask2(vector<NaturalNumber> &numbers, int n) {
    string fullInput;

    cout << "Enter " << 10 * n << " digits sequentially (10 for each number):\n";
    if (!getline(cin, fullInput)) {
        cerr << "Error reading input.\n";
        return;
    }

    for (int i = 0; i < n; ++i) {
        size_t startIndex = i * 10;

        if (startIndex + 10 > fullInput.length()) {
            cout << "Warning: insufficient digits for number " << i + 1 << ". Skipping.\n";
            break;
        }

        string digitsBlock = fullInput.substr(startIndex, 10);

        try {
            numbers[i] = stoull(digitsBlock);
        } catch (const out_of_range& oor) {
            cerr << "Error converting number (" << digitsBlock << "). Set to 0.\n";
            numbers[i] = 0;
        }
    }
}

NaturalNumber calculateSumTask2(const vector<NaturalNumber> &numbers) {
    NaturalNumber sum = 0;
    for (size_t i = 0; i < numbers.size(); ++i) {
        sum += numbers[i];
    }
    return sum;
}

void outputSumTask2(NaturalNumber sum) {
    cout << "\nTotal sum of the entered numbers: " << sum << endl;
}

void runTask2() {
    int n = inputNTask2();
    if (n <= 0) return;

    vector<NaturalNumber> numbers(n);
    inputNumbersTask2(numbers, n);
    NaturalNumber totalSum = calculateSumTask2(numbers);
    outputSumTask2(totalSum);
}

string inputCommaSeparatedNumbersTask6() {
    string rawData;
    cout << "TASK 6: log() Calculation\n";
    cout << "Enter real numbers separated by commas (e.g., 1.5,0.01,10.0,-5):\n";
    if (cin.peek() == '\n') cin.ignore(numeric_limits<streamsize>::max(), '\n');

    getline(cin, rawData);
    return rawData;
}

vector<double> parseNumbersTask6(const string &data) {
    vector<double> numbers;
    stringstream ss(data);
    string segment;

    while (getline(ss, segment, ',')) {
        stringstream ss_segment(segment);
        double num = 0.0;

        if (ss_segment >> num) {
            numbers.push_back(num);
        }
    }
    return numbers;
}

void processAndOutputLogarithmsTask6(const vector<double> &numbers) {
    cout << "\n--- log() Results ---" << endl;

    for (size_t i = 0; i < numbers.size(); ++i) {
        double x = numbers[i];

        cout << "log(" << x << ")";

        if (x > 0.0) {
            double logValue = log(x);

            cout << " (Scientific): ";
            cout << scientific << setprecision(2) << setw(5) << logValue << " | ";

            cout << "(Decimal): ";
            cout << fixed << setprecision(2) << setw(5) << logValue << endl;

        } else {
            cout << " -> None (Domain error)" << endl;
        }
    }
}

void runTask6() {
    string rawInput = inputCommaSeparatedNumbersTask6();
    vector<double> numbers = parseNumbersTask6(rawInput);
    processAndOutputLogarithmsTask6(numbers);
}

vector<double> readAndParseFileTask7(const string &filename) {
    vector<double> numbers;
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error: Failed to open input file " << filename << ". Make sure it exists.\n";
        return numbers;
    }

    string fileContent;
    getline(inputFile, fileContent);
    inputFile.close();

    stringstream ss(fileContent);
    string segment;

    while (getline(ss, segment, ';')) {
        stringstream ss_segment(segment);
        double num = 0.0;

        if (ss_segment >> num) {
            numbers.push_back(num);
        }
    }

    return numbers;
}

vector<double> calculateArcsinTask7(const vector<double> &inputNumbers) {
    vector<double> results;

    for (size_t i = 0; i < inputNumbers.size(); ++i) {
        double x = inputNumbers[i];

        if (x >= -1.0 && x <= 1.0) {
            double arcsinValue = asin(x);
            results.push_back(arcsinValue);
        }
    }

    return results;
}

void writeResultsToFileTask7(const string &filename, const vector<double> &results) {
    ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        cerr << "Error: Failed to open output file " << filename << endl;
        return;
    }

    outputFile << scientific << setprecision(10);

    for (size_t i = 0; i < results.size(); ++i) {
        outputFile << results[i] << endl;
    }

    outputFile.close();
}

void runTask7() {
    cout << "TASK 7: arcsin() Calculation from File\n";
    cout << "Attempting to read from file: " << INPUT_FILENAME_TASK7 << endl;

    vector<double> numbers = readAndParseFileTask7(INPUT_FILENAME_TASK7);

    if (numbers.empty()) {
        return;
    }

    vector<double> arcsinResults = calculateArcsinTask7(numbers);
    writeResultsToFileTask7(OUTPUT_FILENAME_TASK7, arcsinResults);

    cout << "Processing finished. Results (arcsin) written to file: " << OUTPUT_FILENAME_TASK7 << endl;
}

int main() {
    runTask1();
    cout << "\n" << string(40, '-') << "\n\n";

    runTask2();
    cout << "\n" << string(40, '-') << "\n\n";

    runTask6();
    cout << "\n" << string(40, '-') << "\n\n";

    runTask7();
    cout << "\n" << string(40, '=') << "\n";
    cout << "Program finished.\n";

    return 0;
}