#include <stdio.h>
#include <stdint.h>
#include <limits.h>

void print_binary(int num) {
    int i;
    int bits = sizeof(int) * CHAR_BIT;
    for (i = bits - 1; i >= 0; i--) {
        printf("%c", (num & (1 << i)) ? '1' : '0');
        if (i % 8 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

void task1() {
    uint8_t n;
    printf("\n--- Task 1: Compute 2^n ---\n");
    printf("Enter a natural number n (0 <= n < 32): ");
    if (scanf("%hhu", &n) != 1) {
        printf("Input error.\n");
        while (getchar() != '\n');
        return;
    }
    if (n >= 32) {
        printf("Error: n is too large for unsigned int.\n");
        return;
    }
    unsigned int result = 1U << n;
    printf("2^%u = %u (0x%X)\n", n, result, result);
}

void task2() {
    int n, k;
    printf("\n--- Task 2: Set the k-th bit to 1 ---\n");
    printf("Enter an integer n: ");
    if (scanf("%d", &n) != 1) {
        printf("Input error for n.\n");
        while (getchar() != '\n');
        return;
    }
    printf("Enter bit number k (starting from 0): ");
    if (scanf("%d", &k) != 1) {
        printf("Input error for k.\n");
        while (getchar() != '\n');
        return;
    }
    if (k < 0 || k >= (sizeof(int) * 8)) {
        printf("Invalid bit number k.\n");
        return;
    }
    int mask = 1 << k;
    int result = n | mask;
    printf("Original number n = %d\n", n);
    printf("Binary (n): ");
    print_binary(n);
    printf("Mask (1<<k): ");
    print_binary(mask);
    printf("Result = %d (binary: ", result);
    print_binary(result);
    printf(")\n");
}

void task3() {
    uint64_t m;
    int j;
    printf("\n--- Task 3: Reset the j-th bit to 0 ---\n");
    printf("Enter a natural 64-bit number m (e.g., 1000000000): ");
    if (scanf("%llu", &m) != 1) {
        printf("Input error for m.\n");
        while (getchar() != '\n');
        return;
    }
    printf("Enter bit number j (0-63) to reset to 0: ");
    if (scanf("%d", &j) != 1) {
        printf("Input error for j.\n");
        while (getchar() != '\n');
        return;
    }
    if (j < 0 || j >= 64) {
        printf("Invalid bit number j.\n");
        return;
    }
    uint64_t mask_reset = ~(1ULL << j);
    uint64_t result = m & mask_reset;
    printf("Original number m (Decimal): %llu\n", m);
    printf("Result (Decimal): %llu\n", result);
    printf("Result (Hexadecimal): 0x%llX\n", result);
}

void task4() {
    uint32_t num;
    printf("\n--- Task 4: Swap first 8 and last 8 bits of a 32-bit number ---\n");
    printf("Enter a 32-bit number (Hex/Dec): ");
    if (scanf("%u", &num) != 1) {
        printf("Input error.\n");
        while (getchar() != '\n');
        return;
    }
    uint32_t lower_to_upper = (num & 0xFF) << 24;
    uint32_t upper_to_lower = (num >> 24) & 0xFF;
    uint32_t middle_bytes = num & 0x00FFFF00;
    uint32_t new_num = lower_to_upper | middle_bytes | upper_to_lower;
    printf("Original number (Decimal): %u\n", num);
    printf("Original number (Hexadecimal): 0x%X\n", num);
    printf("Result (Decimal): %u\n", new_num);
    printf("Result (Hexadecimal): 0x%X\n", new_num);
}

void task5() {
    unsigned int num;
    printf("\n--- Task 5: Longest sequence of consecutive ones ---\n");
    printf("Enter a natural number (up to 32 bits): ");
    if (scanf("%u", &num) != 1) {
        printf("Input error.\n");
        while (getchar() != '\n');
        return;
    }
    int max_count = 0;
    int current_count = 0;
    printf("Number %u in binary: ", num);
    print_binary(num);
    for (int i = 0; i < sizeof(unsigned int) * CHAR_BIT; ++i) {
        if ((num >> i) & 1) {
            current_count++;
        } else {
            if (current_count > max_count) {
                max_count = current_count;
            }
            current_count = 0;
        }
    }
    if (current_count > max_count) {
        max_count = current_count;
    }
    printf("Longest sequence of consecutive ones: %d\n", max_count);
}

void task6_verification() {
    printf("\n--- Task 6: Programmatic verification of bitwise expressions ---\n");
    int test_values[] = {0, 1, 4, 10, 12, 15, -4, -1};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    printf("\n>> 6.1: y = ((x & (x-1)) > 0) \n");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < num_tests; i++) {
        int x = test_values[i];
        int y1 = ((x & (x - 1)) > 0);
        printf("x = %3d (Binary: ", x);
        print_binary(x);
        printf(") -> (x & (x-1)) = %4d -> y = %d\n", (x & (x - 1)), y1);
    }
    printf("\n>> 6.2: y = x & (-x) \n");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < num_tests; i++) {
        int x = test_values[i];
        int y2 = x & (-x);
        printf("x = %3d (Binary: ", x);
        print_binary(x);
        printf(") -> y = x & (-x) = %4d\n", y2);
        printf("   Binary result: ");
        print_binary(y2);
    }
}

void task7() {
    printf("\n--- Task 7: Determine Endianness ---\n");
    uint32_t i = 0x12345678;
    unsigned char *byte_ptr = (unsigned char *)&i;
    printf("Checking 32-bit number 0x%X.\n", i);
    printf("First byte in memory (lowest address): 0x%X\n", (unsigned int)*byte_ptr);
    if (*byte_ptr == 0x78) {
        printf("This system is **Little-Endian**.\n");
    } else if (*byte_ptr == 0x12) {
        printf("This system is **Big-Endian**.\n");
    } else {
        printf("Unable to determine.\n");
    }
}

int main() {
    printf("Welcome to C Bitwise Operation Tasks!\n");
    while (getchar() != '\n' && !feof(stdin));
    task1();
    printf("\n=================================================\n");
    while (getchar() != '\n' && !feof(stdin));
    task2();
    printf("\n=================================================\n");
    while (getchar() != '\n' && !feof(stdin));
    task3();
    printf("\n=================================================\n");
    while (getchar() != '\n' && !feof(stdin));
    task4();
    printf("\n=================================================\n");
    while (getchar() != '\n' && !feof(stdin));
    task5();
    printf("\n=================================================\n");
    task6_verification();
    printf("\n=================================================\n");
    task7();
    printf("\n=================================================\n");
    printf("All tasks completed.\n");
    return 0;
}
