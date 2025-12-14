#include <stdio.h>
#include <stdint.h>

int countSetBits_standard(uint32_t n) {
    int count = 0;
    for (int i = 0; i < 32; i++) {
        uint32_t mask = 1U << i;
        if (n & mask) {
            count++;
        }
    }
    return count;
}

int countSetBits_kernighan(uint32_t n) {
    int count = 0;
    while (n > 0) {
        n = n & (n - 1);
        count++;
    }
    return count;
}

int main() {
    uint32_t number;
    uint32_t default_number = 0xAAAAAAAA;

    printf("Enter a natural 32-bit number (or 0 to use the example %u): ", default_number);
    if (scanf("%u", &number) != 1 || number == 0) {
        number = default_number;
    }

    printf("\n--- Analyzing number %u ---\n", number);

    int standard_result = countSetBits_standard(number);
    printf("1. Result using Standard method: %d\n", standard_result);

    int kernighan_result = countSetBits_kernighan(number);
    printf("2. Result using Kernighan's Algorithm: %d\n", kernighan_result);

    printf("\n--- How n & (n - 1) works ---\n");
    if (number != 0) {
        uint32_t temp_n = number;
        uint32_t n_minus_1 = number - 1;
        uint32_t result = temp_n & n_minus_1;
        printf("Original number n (decimal): %u\n", temp_n);
        printf("Number n - 1 (decimal):     %u\n", n_minus_1);
        printf("Result n & (n - 1) (decimal): %u\n", result);
    }

    return 0;
}
