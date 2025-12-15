#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

class WordCounter {
private:
    std::string text_;

public:
    WordCounter(const std::string& inputLine) : text_(inputLine) {}

    int countWordsWithChar(char searchChar) const {
        int count = 0;

        std::stringstream ss(text_);
        std::string word;

        while (ss >> word) {
            if (word.find(searchChar) != std::string::npos) {
                count++;
            }
        }

        return count;
    }
};

int main() {
    std::cout << "Enter a line of words from the Latin alphabet, separated by spaces: \n> ";
    std::string inputLine;
    std::getline(std::cin, inputLine);

    char searchChar;
    std::cout << "Enter the character (Latin letter) to search for: \n> ";
    std::cin >> searchChar;

    WordCounter counter(inputLine);

    int result = counter.countWordsWithChar(searchChar);

    std::cout << "\n---------------------------------------------\n";
    std::cout << "Search character: '" << searchChar << "'\n";
    std::cout << "Number of words containing the character: " << result << std::endl;
    std::cout << "---------------------------------------------\n";

    return 0;
}