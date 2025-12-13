#include <stdio.h>
#include <stdint.h>

void task1() {
    uint8_t n;
    uint64_t result;

    printf("--- Task 1: Calculate 2^n ---\n");
    printf("Enter a natural number n (0 <= n < 64): ");

    if (scanf("%hhu", &n) != 1) {
        printf("Input error. Try again.\n");
        while (getchar() != '\n');
        return;
    }

    if (n >= 64) {
        printf("Error: n must be less than 64.\n");
        return;
    }

    result = (uint64_t)1 << n;

    printf("Result 2^%hhu: %llu\n", n, result);
}

void task2() {
    unsigned int n;
    unsigned int k;
    unsigned int result;

    printf("--- Task 2: Set k-th bit to 1 ---\n");
    printf("Enter an integer n: ");
    if (scanf("%u", &n) != 1) return;

    printf("Enter the bit index k (starting from 0): ");
    if (scanf("%u", &k) != 1) return;

    unsigned int mask = 1U << k;

    result = n | mask;

    printf("Original number n (decimal): %u\n", n);
    printf("New number with %u-th bit set: %u\n", k, result);
}

void task3() {
    uint64_t m;
    unsigned int j;
    uint64_t result;

    printf("--- Task 3: Clear j-th bit to 0 (64-bit) ---\n");
    printf("Enter a 64-bit natural number m: ");
    if (scanf("%llu", &m) != 1) return;

    printf("Enter the bit index j to clear (0-63): ");
    if (scanf("%u", &j) != 1) return;

    if (j >= 64) {
        printf("Error: Bit index j must be in the range 0-63.\n");
        return;
    }

    uint64_t mask = ~(1ULL << j);

    result = m & mask;

    printf("Original number (dec): %llu\n", m);
    printf("Result after clearing %u-th bit:\n", j);
    printf("  Decimal: %llu\n", result);
    printf("  Hexadecimal: 0x%llX\n", result);
}

void task4() {
    uint32_t m;
    uint32_t first_byte;
    uint32_t last_byte;
    uint32_t middle_part;
    uint32_t result;

    printf("--- Task 4: Swap first and last 8 bits (32-bit) ---\n");
    printf("Enter a 32-bit number m: ");
    if (scanf("%u", &m) != 1) return;

    last_byte = m & 0xFF;

    first_byte = m & 0xFF000000;

    middle_part = m & 0x00FFFF00;

    uint32_t new_first_byte = last_byte << 24;

    uint32_t new_last_byte = first_byte >> 24;

    result = new_first_byte | middle_part | new_last_byte;

    printf("Original number (dec): %u\n", m);
    printf("Result after swapping bytes:\n");
    printf("  Decimal: %u\n", result);
    printf("  Hexadecimal: 0x%X\n", result);
}


void task8() {
    uint32_t m;
    unsigned int j;
    uint32_t result;

    printf("--- Task 8: Clear j-th bit to 0 (32-bit) ---\n");
    printf("Enter a 32-bit natural number m: ");
    if (scanf("%u", &m) != 1) return;

    printf("Enter the bit index j to clear (0-31): ");
    if (scanf("%u", &j) != 1) return;

    if (j >= 32) {
        printf("Error: Bit index j must be in the range 0-31.\n");
        return;
    }

    uint32_t mask = ~(1U << j);

    result = m & mask;

    printf("Original number (dec): %u\n", m);
    printf("Result after clearing %u-th bit:\n", j);
    printf("  Decimal: %u\n", result);
    printf("  Hexadecimal: 0x%X\n", result);
}

void task9() {
    uint64_t m;
    int msb_index = -1;
    int next_zero_index = -1;

    printf("--- Task 9: Find MSB and subsequent zero (64-bit) ---\n");
    printf("Enter a natural number m: ");
    if (scanf("%llu", &m) != 1) return;

    if (m == 0) {
        printf("Number m = 0. No non-zero MSB.\n");
        return;
    }

    for (int i = 63; i >= 0; i--) {
        if ((m >> i) & 1) {
            msb_index = i;
            break;
        }
    }

    if (msb_index > 0) {
        if (!((m >> (msb_index - 1)) & 1)) {
            next_zero_index = msb_index - 1;
        } else {
            for (int i = msb_index - 1; i >= 0; i--) {
                 if (!((m >> i) & 1)) {
                    next_zero_index = i;
                    break;
                }
            }
        }
    }

    printf("Original number (dec): %llu\n", m);
    printf("Index of the Most Significant Bit (MSB): %d\n", msb_index);
    printf("Index of the next zero bit after MSB: %d\n", next_zero_index);
}

void task10() {
    uint64_t m;
    const int BYTE_SIZE = 8;
    const int TOTAL_BITS = sizeof(uint64_t) * 8;

    const int LSB_SHIFT = 0;
    const int MSB_SHIFT = TOTAL_BITS - BYTE_SIZE;

    uint64_t result;

    printf("--- Task 10: Swap first and last 8 bits (64-bit) ---\n");
    printf("Enter a natural number m: ");
    if (scanf("%llu", &m) != 1) return;

    uint64_t last_byte = m & 0xFFULL;

    uint64_t first_byte = m & (0xFFULL << MSB_SHIFT);

    uint64_t swap_mask = (0xFFULL << LSB_SHIFT) | (0xFFULL << MSB_SHIFT);
    uint64_t middle_part = m & ~swap_mask;

    uint64_t new_last_byte = first_byte >> MSB_SHIFT;

    uint64_t new_first_byte = last_byte << MSB_SHIFT;

    result = middle_part | new_last_byte | new_first_byte;

    printf("Original number (dec): %llu\n", m);
    printf("Result after swapping bytes:\n");
    printf("  Decimal: %llu\n", result);
    printf("  Hexadecimal: 0x%llX\n", result);
}

int main() {
    int choice;
    printf("==========================================\n");
    printf("=== C Bitwise Operations Suite ===\n");
    printf("==========================================\n");

    while (1) {
        printf("\n------------------------------------------\n");
        printf("Select a task to run:\n");
        printf(" 1) Calculate 2^n using bit shift\n");
        printf(" 2) Set k-th bit to 1\n");
        printf(" 3) Clear j-th bit to 0 (64-bit)\n");
        printf(" 4) Swap first/last 8 bits (32-bit)\n");
        printf(" 8) Clear j-th bit to 0 (32-bit)\n");
        printf(" 9) Find MSB and next zero bit\n");
        printf("10) Swap first/last 8 bits (64-bit)\n");
        printf(" 0) Exit\n");
        printf("------------------------------------------\n");

        printf("Your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInput error. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 0) break;

        switch(choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 8: task8(); break;
            case 9: task9(); break;
            case 10: task10(); break;
            default: printf("Unknown task. Try again.\n");
        }
    }

    printf("\nProgram terminated.\n");
    return 0;
}