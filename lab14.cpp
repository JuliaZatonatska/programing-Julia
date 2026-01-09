#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <type_traits>

const std::string FILE_1 = "expression.txt";
const std::string FILE_2_IN = "input_text2.txt";
const std::string FILE_2_OUT = "output_text2.txt";
const std::string FILE_3_IN = "encrypted_message.txt";
const std::string FILE_3_OUT = "decoded_message.txt";
const std::string FILE_5 = "lines_to_count.txt";
const std::string FILE_6 = "students_data.txt";

class FileUtility {
protected:
    void createTestFile(const std::string& filename, const std::string& content) {
        std::ifstream checkFile(filename);
        if (!checkFile) {
            std::cout << "  [INFO] Creating test file: " << filename << std::endl;
            std::ofstream outFile(filename);
            if (outFile.is_open()) {
                outFile << content;
                outFile.close();
            } else {
                std::cerr << "  [ERROR] Failed to create file: " << filename << std::endl;
            }
        }
    }
};

class Task1_ExpressionCalculator : public FileUtility {
private:
    std::string filename;
    std::string expressionStr;
    double result;

public:
    Task1_ExpressionCalculator(const std::string& fname = FILE_1) : filename(fname), result(0.0) {
        createTestFile(filename, "15 + 7.5 - 2 =");
    }

    bool inputData() {
        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            std::cerr << "  [ERROR] File '" << filename << "' not found or cannot be opened." << std::endl;
            return false;
        }

        std::stringstream buffer;
        buffer << inFile.rdbuf();
        expressionStr = buffer.str();
        inFile.close();

        if (!expressionStr.empty() && expressionStr.back() == '=') expressionStr.pop_back();
        size_t last = expressionStr.find_last_not_of(" \n\r\t");
        if (last != std::string::npos) expressionStr = expressionStr.substr(0, last + 1);

        if (expressionStr.empty()) {
            std::cout << "  [WARNING] File is empty." << std::endl;
            return false;
        }

        return true;
    }

    void calculateResult() {
        if (expressionStr.empty()) return;

        std::stringstream ss(expressionStr);
        double currentNumber;
        char op = '+';
        result = 0.0;

        if (!(ss >> currentNumber)) {
            std::cerr << "  [ERROR] Expression does not start with a number." << std::endl;
            return;
        }
        result = currentNumber;

        while (ss >> op) {
            if (!(ss >> currentNumber)) {
                std::cerr << "  [ERROR] Expression ends with an operator or no number after operator." << std::endl;
                return;
            }

            if (op == '+') result += currentNumber;
            else if (op == '-') result -= currentNumber;
            else {
                std::cerr << "  [ERROR] Unsupported operator: " << op << std::endl;
                return;
            }
        }
    }

    void printResult() {
        std::cout << "  Read expression: " << expressionStr << " =" << std::endl;
        std::cout << "  Calculation result: " << result << std::endl;
    }
};

class Task2_ArticleWordChanger : public FileUtility {
private:
    std::string inputFilename;
    std::string outputFilename;
    std::string initialText;
    std::string processedText;

    std::string toLower(const std::string& str) {
        std::string lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        return lowerStr;
    }

public:
    Task2_ArticleWordChanger(const std::string& inName = FILE_2_IN, const std::string& outName = FILE_2_OUT)
        : inputFilename(inName), outputFilename(outName) {
        createTestFile(inputFilename, "Hier ist der hund, die katze und das auto. Die sonne scheint.");
    }

    bool inputData() {
        std::ifstream inFile(inputFilename);
        if (!inFile.is_open()) {
            std::cerr << "  [ERROR] File '" << inputFilename << "' not found or cannot be opened." << std::endl;
            return false;
        }

        std::stringstream buffer;
        buffer << inFile.rdbuf();
        initialText = buffer.str();
        inFile.close();

        size_t last = initialText.find_last_not_of(" \n\r\t");
        if (last != std::string::npos) initialText = initialText.substr(0, last + 1);

        return !initialText.empty();
    }

    void processText() {
        if (initialText.empty()) return;

        std::stringstream ss(initialText);
        std::string currentWord;
        std::string tempText = "";
        const std::vector<std::string> articles = {"die", "der", "das"};

        while (ss >> currentWord) {
            std::string cleanWord = currentWord;
            std::string trailingPunctuation = "";

            if (!cleanWord.empty() && (cleanWord.back() == ',' || cleanWord.back() == '.' || cleanWord.back() == '!' || cleanWord.back() == '?')) {
                trailingPunctuation = cleanWord.back();
                cleanWord.pop_back();
            }

            std::string currentWordLower = toLower(cleanWord);
            bool isArticle = std::find(articles.begin(), articles.end(), currentWordLower) != articles.end();

            tempText += currentWord + " ";

            if (isArticle) {
                std::string nextWord;
                if (ss >> nextWord) {
                    if (!nextWord.empty()) nextWord[0] = std::toupper(nextWord[0]);
                    tempText += nextWord + " ";
                }
            }
        }

        if (!tempText.empty() && tempText.back() == ' ') tempText.pop_back();
        processedText = tempText;
    }

    void printResult() {
        if (processedText.empty()) return;

        std::cout << "  Original text: " << initialText << std::endl;
        std::cout << "  Processed text: " << processedText << std::endl;

        std::ofstream outFile(outputFilename);
        if (outFile.is_open()) {
            outFile << processedText;
            outFile.close();
            std::cout << "  [INFO] Result written to file: '" << outputFilename << "'" << std::endl;
        } else {
            std::cerr << "  [ERROR] Failed to write file " << outputFilename << std::endl;
        }
    }
};

class Task3_CipherDecoder : public FileUtility {
private:
    std::string inputFilename;
    std::string outputFilename;
    std::string encryptedText;
    std::string decodedText;

    std::string reverseString(const std::string& str) {
        std::string reversed = str;
        std::reverse(reversed.begin(), reversed.end());
        return reversed;
    }

    bool isSeparator(char c) {
        return c == ' ' || c == ',' || c == '.' || c == '!' || c == '?';
    }

public:
    Task3_CipherDecoder(const std::string& inName = FILE_3_IN, const std::string& outName = FILE_3_OUT)
        : inputFilename(inName), outputFilename(outName) {
        createTestFile(inputFilename, "droW teewS, oT ot a! emaN, ?kooB.");
    }

    bool inputData() {
        std::ifstream inFile(inputFilename);
        if (!inFile.is_open()) {
            std::cerr << "  [ERROR] File '" << inputFilename << "' not found or cannot be opened." << std::endl;
            return false;
        }

        std::stringstream buffer;
        buffer << inFile.rdbuf();
        encryptedText = buffer.str();
        inFile.close();

        size_t last = encryptedText.find_last_not_of(" \n\r\t");
        if (last != std::string::npos) encryptedText = encryptedText.substr(0, last + 1);

        return !encryptedText.empty();
    }

    void decodeMessage() {
        if (encryptedText.empty()) return;

        decodedText = "";
        std::string currentWord = "";

        for (size_t i = 0; i < encryptedText.length(); ++i) {
            char c = encryptedText[i];

            if (isSeparator(c)) {
                if (!currentWord.empty()) {
                    decodedText += reverseString(currentWord);
                    currentWord = "";
                }
                decodedText += c;
            } else {
                currentWord += c;
            }
        }

        if (!currentWord.empty()) decodedText += reverseString(currentWord);
    }

    void printResult() {
        if (decodedText.empty()) return;

        std::cout << "  Encrypted text: " << encryptedText << std::endl;
        std::cout << "  Decoded text: " << decodedText << std::endl;

        std::ofstream outFile(outputFilename);
        if (outFile.is_open()) {
            outFile << decodedText;
            outFile.close();
            std::cout << "  [INFO] Result written to file: '" << outputFilename << "'" << std::endl;
        } else {
            std::cerr << "  [ERROR] Failed to write file " << outputFilename << std::endl;
        }
    }
};

class Task5_LineCounter : public FileUtility {
private:
    std::string filename;
    std::vector<std::string> lines;
    char startChar;
    char endChar;

    int countStart;
    int countEnd;
    int countSameStartEnd;
    int countIdenticalChars;

    bool checkIdentical(const std::string& line) {
        if (line.length() <= 1) return true;
        char firstChar = line[0];
        for (size_t i = 1; i < line.length(); ++i)
            if (line[i] != firstChar) return false;
        return true;
    }

public:
    Task5_LineCounter(const std::string& fname = FILE_5, char sChar = 'A', char eChar = 't')
        : filename(fname), startChar(sChar), endChar(eChar),
          countStart(0), countEnd(0), countSameStartEnd(0), countIdenticalChars(0) {
        createTestFile(filename, "Apple\nBanana\nTest\nTreat\nQWERTY\nABA\nAAAAA\nt\n");
    }

    bool inputData() {
        lines.clear();
        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            std::cerr << "  [ERROR] File '" << filename << "' not found or cannot be opened." << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(inFile, line)) {
            size_t last = line.find_last_not_of(" \n\r\t");
            if (last != std::string::npos) line = line.substr(0, last + 1);
            else line = "";
            if (!line.empty()) lines.push_back(line);
        }
        inFile.close();
        return !lines.empty();
    }

    void calculateCounts() {
        countStart = 0; countEnd = 0; countSameStartEnd = 0; countIdenticalChars = 0;

        for (const std::string& line : lines) {
            if (line.empty()) continue;

            if (line[0] == startChar) countStart++;
            if (line.back() == endChar) countEnd++;
            if (std::tolower(line[0]) == std::tolower(line.back())) countSameStartEnd++;
            if (checkIdentical(line)) countIdenticalChars++;
        }
    }

    void printResult() {
        std::cout << "  Lines read: " << lines.size() << std::endl;
        std::cout << "  Start char: '" << startChar << "', End char: '" << endChar << "'" << std::endl;
        std::cout << "  1. Lines starting with '" << startChar << "': " << countStart << std::endl;
        std::cout << "  2. Lines ending with '" << endChar << "': " << countEnd << std::endl;
        std::cout << "  3. Lines starting and ending with the same char: " << countSameStartEnd << std::endl;
        std::cout << "  4. Lines consisting of identical chars: " << countIdenticalChars << std::endl;
    }
};

class Task6_StudentGrades : public FileUtility {
private:
    std::string filename;
    std::string targetGroup;
    std::vector<double> groupGrades;
    int groupStudentsCount;
    double averageGrade;

public:
    Task6_StudentGrades(const std::string& fname = FILE_6, const std::string& tGroup = "KPI-31")
        : filename(fname), targetGroup(tGroup), groupStudentsCount(0), averageGrade(0.0) {
        std::string content =
            "Ivanov Ivan KPI-31 4.5 5.0 4.0\n"
            "Petrov Petr KPI-32 3.0 3.5 4.0 4.5\n"
            "Sidorova Anna KPI-31 5.0 5.0 5.0 5.0\n"
            "Kovalenko Oleg KPI-31 3.5 4.0\n";
        createTestFile(filename, content);
    }

    bool processData() {
        groupGrades.clear();
        groupStudentsCount = 0;

        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            std::cerr << "  [ERROR] File '" << filename << "' not found or cannot be opened." << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string token;
            std::string studentGroup;

            if (!(ss >> token)) continue;
            if (!(ss >> token)) continue;
            if (!(ss >> studentGroup)) continue;

            if (studentGroup == targetGroup) {
                groupStudentsCount++;
                double grade;
                while (ss >> grade) groupGrades.push_back(grade);
            }
        }
        inFile.close();
        return true;
    }

    void calculateAverage() {
        if (groupGrades.empty()) { averageGrade = 0.0; return; }

        double totalSum = 0.0;
        for (double grade : groupGrades) totalSum += grade;
        averageGrade = totalSum / groupGrades.size();
    }

    void printResult() {
        std::cout << "  Target group: " << targetGroup << std::endl;
        std::cout << "  Number of students in group: " << groupStudentsCount << std::endl;
        std::cout << "  Number of grades considered: " << groupGrades.size() << std::endl;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "  Average grade for group: " << averageGrade << std::endl;
    }
};

template<typename T>
void runTask(int taskNumber, T& taskInstance) {
    std::cout << "\n############################################################" << std::endl;
    std::cout << "## TASK " << taskNumber << ": " << typeid(taskInstance).name() << std::endl;
    std::cout << "############################################################" << std::endl;

    bool dataProcessed = false;

    if constexpr (std::is_same_v<T, Task6_StudentGrades>) {
        dataProcessed = taskInstance.processData();
    } else {
        dataProcessed = taskInstance.inputData();
    }

    if (dataProcessed) {
        if constexpr (std::is_same_v<T, Task1_ExpressionCalculator>) taskInstance.calculateResult();
        else if constexpr (std::is_same_v<T, Task2_ArticleWordChanger>) taskInstance.processText();
        else if constexpr (std::is_same_v<T, Task3_CipherDecoder>) taskInstance.decodeMessage();
        else if constexpr (std::is_same_v<T, Task5_LineCounter>) taskInstance.calculateCounts();
        else if constexpr (std::is_same_v<T, Task6_StudentGrades>) taskInstance.calculateAverage();

        taskInstance.printResult();
    } else {
        std::cout << "  [WARNING] Data processing/input failed. Skipping computation." << std::endl;
    }
    std::cout << "------------------------------------------------------------" << std::endl;
}

int main() {
    Task1_ExpressionCalculator calculator;
    runTask(1, calculator);

    Task2_ArticleWordChanger changer;
    runTask(2, changer);

    Task3_CipherDecoder decoder;
    runTask(3, decoder);

    Task5_LineCounter counter;
    runTask(5, counter);

    Task6_StudentGrades studentProcessor;
    runTask(6, studentProcessor);

    std::cout << "\n[COMPLETION] All tasks finished." << std::endl;
    return 0;
}
