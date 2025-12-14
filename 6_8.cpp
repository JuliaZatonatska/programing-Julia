#include <stdio.h>
#include <stdint.h>

void print_binary(uint32_t n) {
    for (int i = 31; i >= 0; i--) {
        int bit = (n >> i) & 1;
        printf("%d", bit);
        if (i % 8 == 0 && i != 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    uint32_t m;
    int j;

    printf("Enter a 32-bit natural number m: ");
    if (scanf("%u", &m) != 1) {
        printf("Error reading number m.\n");
        return 1;
    }

    printf("Enter the bit number j to reset (from 0 to 31): ");
    if (scanf("%d", &j) != 1 || j < 0 || j > 31) {
        printf("Error: bit number j must be in the range 0 to 31.\n");
        return 1;
    }

    printf("\n--- Initial number ---\n");
    printf("Decimal: %u\n", m);
    printf("Hexadecimal: 0x%X\n", m);
    printf("Binary (31..0): ");
    print_binary(m);

    uint32_t mask = ~(1U << j);
    m = m & mask;

    printf("\n--- Result (j=%d bit reset) ---\n", j);
    printf("Decimal: %u\n", m);
    printf("Hexadecimal: 0x%X\n", m);
    printf("Binary (31..0): ");
    print_binary(m);

    return 0;
}
