#include <iostream>
#include <string>
#include <sstream>

std::string inputString() {
    std::string line;
    std::cout << "Enter the string to process: ";
    std::getline(std::cin, line);
    return line;
}

void outputResult(const std::string& result, int taskNumber) {
    std::cout << "\n--- Result of Task " << taskNumber << " ---" << std::endl;
    std::cout << "Obtained string: " << result << std::endl;
}

class Task1 {
private:
    std::string data;

public:
    Task1(const std::string& input) : data(input) {}

    std::string process() const {
        size_t colonPos = data.find(':');
        if (colonPos == std::string::npos) {
            return data;
        }
        size_t commaPos = data.find(',', colonPos + 1);
        if (commaPos != std::string::npos) {
            size_t start = colonPos + 1;
            size_t length = commaPos - start;
            return data.substr(start, length);
        } else {
            return data.substr(colonPos + 1);
        }
    }
};

class Task2 {
private:
    std::string data;

public:
    Task2(const std::string& input) : data(input) {}

    std::string process() const {
        size_t firstDot = data.find('.');
        size_t lastDot = data.rfind('.');
        std::string result = data;

        if (firstDot == std::string::npos) {
            size_t firstNonSpace = result.find_first_not_of(' ');
            if (firstNonSpace != std::string::npos) {
                result.erase(0, firstNonSpace);
            } else {
                return "";
            }
            return result;
        }

        if (firstDot == lastDot) {
            return result.substr(firstDot + 1);
        }

        size_t start = firstDot + 1;
        size_t length = lastDot - start;
        result.erase(start, length);
        return result;
    }
};

class Task3 {
private:
    std::string data;

public:
    Task3(const std::string& input) : data(input) {}

    std::string process() const {
        std::string output = "";
        std::string currentWord = "";
        bool inWord = false;

        for (size_t i = 0; i < data.length(); ++i) {
            if (data[i] != ' ') {
                currentWord += data[i];
                inWord = true;
            } else {
                if (inWord) {
                    if (currentWord.length() > 0) {
                        currentWord.pop_back();
                    }
                    output += currentWord;
                    currentWord = "";
                    inWord = false;
                }
                output += ' ';
            }
        }

        if (inWord) {
            if (currentWord.length() > 0) {
                currentWord.pop_back();
            }
            output += currentWord;
        }

        return output;
    }
};

class Task7 {
private:
    std::string data;

public:
    Task7(const std::string& input) : data(input) {}

    std::string process() const {
        std::string output = "";
        std::string word;
        std::stringstream ss(data);
        bool firstWord = true;

        while (ss >> word) {
            if (!firstWord) {
                output += ",";
            }
            output += word;
            firstWord = false;
        }

        output += ".";
        return output;
    }
};

class Task8 {
private:
    std::string data;

    std::string removeLastCharOccurrences(const std::string& word) const {
        if (word.empty()) {
            return "";
        }
        char lastChar = word.back();
        std::string newWord = "";
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] != lastChar) {
                newWord += word[i];
            }
        }
        return newWord;
    }

public:
    Task8(const std::string& input) : data(input) {}

    std::string process() const {
        std::string output = "";
        std::string currentWord = "";
        bool inWord = false;

        for (size_t i = 0; i < data.length(); ++i) {
            if (data[i] != ' ') {
                currentWord += data[i];
                inWord = true;
            } else {
                if (inWord) {
                    output += removeLastCharOccurrences(currentWord);
                    currentWord = "";
                    inWord = false;
                }
                output += ' ';
            }
        }

        if (inWord) {
            output += removeLastCharOccurrences(currentWord);
        }

        return output;
    }
};

int main() {
    std::string input;
    std::string result;

    std::cout << "--- Task 1: Find substring between ':' and ',' ---" << std::endl;
    input = inputString();
    Task1 proc1(input);
    result = proc1.process();
    outputResult(result, 1);

    std::cout << "\n--- Task 2: Delete substring between '.' and '.' ---" << std::endl;
    input = inputString();
    Task2 proc2(input);
    result = proc2.process();
    outputResult(result, 2);

    std::cout << "\n--- Task 3: Delete last letter of each word ---" << std::endl;
    input = inputString();
    Task3 proc3(input);
    result = proc3.process();
    outputResult(result, 3);

    std::cout << "\n--- Task 7: Change spaces to commas ---" << std::endl;
    input = inputString();
    Task7 proc7(input);
    result = proc7.process();
    outputResult(result, 7);

    std::cout << "\n--- Task 8: Delete all occurrences of the last letter ---" << std::endl;
    input = inputString();
    Task8 proc8(input);
    result = proc8.process();
    outputResult(result, 8);

    return 0;
}
