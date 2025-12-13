#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>

class InvalidDigitException : public std::runtime_error {
public:
    InvalidDigitException(char invalidChar, int base)
        : std::runtime_error(
            "Error: character '" + std::string(1, invalidChar) +
            "' is not a valid digit for base " + std::to_string(base)
        ) {}
};

int digitToValue(char digit, int base) {
    int value = -1;

    if (digit >= '0' && digit <= '9') {
        value = digit - '0';
    } else if (digit >= 'A' && digit <= 'F') {
        value = 10 + (digit - 'A');
    } else if (digit >= 'a' && digit <= 'f') {
        value = 10 + (digit - 'a');
    }

    assert(value != -1 && "Character is not a digit");

    if (value >= base) {
        throw InvalidDigitException(digit, base);
    }

    return value;
}

long long calculateNumberValue(const std::string& numberString, int base) {
    if (base < 2 || base > 16) {
        throw std::invalid_argument("Error: base must be in range [2..16].");
    }

    if (numberString.empty()) {
        return 0;
    }

    long long result = 0;

    for (char digitChar : numberString) {
        int digitValue = digitToValue(digitChar, base);
        result = result * base + digitValue;
    }

    return result;
}

int main() {
    std::string number;
    int base;

    std::cout << "Enter number: ";
    std::cin >> number;

    std::cout << "Enter base (2..16): ";
    std::cin >> base;

    try {
        long long value = calculateNumberValue(number, base);
        std::cout << "Decimal value: " << value << std::endl;
    }
    catch (const InvalidDigitException& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
