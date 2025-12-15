#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_NUMBERS 1000

void print_int_file_content(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("File '%s' not found or is empty.\n", filename);
        return;
    }
    int number;
    int first_element = 1;
    printf("Content of file %s: ", filename);
    while (fread(&number, sizeof(int), 1, file) == 1) {
        if (!first_element) {
            printf(", ");
        }
        printf("%d", number);
        first_element = 0;
    }
    printf("\n");
    fclose(file);
}

bool is_even(int n) {
    return n % 2 == 0;
}

bool is_power_of_3(int n) {
    if (n <= 0) return false;
    while (n > 1) {
        if (n % 3 != 0) return false;
        n /= 3;
    }
    return true;
}

bool is_perfect_square(int n) {
    if (n < 0) return false;
    long long root = round(sqrt(n));
    return (root * root == n);
}

bool is_prime_3(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

bool has_three_divisors(int n) {
    if (n <= 0) return false;
    int root = (int)round(sqrt(n));
    if (root * root != n) return false;
    return is_prime_3(root);
}

bool is_palindrome(int n) {
    if (n < 0) return false;
    int original = n;
    int reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + (n % 10);
        n /= 10;
    }
    return original == reversed;
}

bool is_perfect_square_long(long long n) {
    if (n < 0) return false;
    long long root = round(sqrt(n));
    return (root * root == n);
}

bool is_fibonacci(int n) {
    if (n < 0) return false;
    if (n == 0 || n == 1) return true;
    long long n_ll = n;
    long long check1 = 5 * n_ll * n_ll + 4;
    long long check2 = 5 * n_ll * n_ll - 4;
    return is_perfect_square_long(check1) || is_perfect_square_long(check2);
}

int create_file_f_task3(const char *filename_f) {
    FILE *file_f = fopen(filename_f, "wb");
    if (file_f == NULL) {
        perror("Error opening file F");
        return 0;
    }

    int n;
    int count = 0;
    printf("Enter integers (0 to finish):\n");

    while (1) {
        printf("Enter number: ");
        if (scanf("%d", &n) != 1) {
            fprintf(stderr, "Input error. Please enter an integer.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (n == 0) break;
        fwrite(&n, sizeof(int), 1, file_f);
        count++;

        if (count >= MAX_NUMBERS) {
            printf("Number limit reached (%d). Stopping input.\n", MAX_NUMBERS);
            break;
        }
    }

    fclose(file_f);
    return count;
}

void build_file_g_task3(const char *filename_f, const char *filename_g, const char *type_name, bool (*condition)(int)) {
    FILE *f_in = fopen(filename_f, "rb");
    if (f_in == NULL) {
        perror("Error opening file F");
        return;
    }

    FILE *g_out = fopen(filename_g, "wb");
    if (g_out == NULL) {
        perror("Error opening file G");
        fclose(f_in);
        return;
    }

    int number;
    int count_g = 0;

    while (fread(&number, sizeof(int), 1, f_in) == 1) {
        if (condition(number)) {
            fwrite(&number, sizeof(int), 1, g_out);
            count_g++;
        }
    }

    fclose(f_in);
    fclose(g_out);
    printf("File G (%s) successfully created. Elements: %d\n", type_name, count_g);
}

void task3_execution() {
    const char *file_f_name = "ints_f_task3.bin";

    printf("\n--- EXECUTING TASK 3: FILTERING INTEGERS ---\n");
    if (create_file_f_task3(file_f_name) == 0) {
        fprintf(stderr, "Failed to create file F or 0 elements entered.\n");
        return;
    }
    printf("File F (original): ");
    print_int_file_content(file_f_name);
    printf("----------------------------------------\n");

    build_file_g_task3(file_f_name, "ints_g_even.bin", "even numbers", is_even);
    print_int_file_content("ints_g_even.bin");

    build_file_g_task3(file_f_name, "ints_g_pow3.bin", "powers of 3", is_power_of_3);
    print_int_file_content("ints_g_pow3.bin");

    build_file_g_task3(file_f_name, "ints_g_square.bin", "perfect squares", is_perfect_square);
    print_int_file_content("ints_g_square.bin");

    build_file_g_task3(file_f_name, "ints_g_3div.bin", "3 divisors", has_three_divisors);
    print_int_file_content("ints_g_3div.bin");

    build_file_g_task3(file_f_name, "ints_g_pal.bin", "palindromes", is_palindrome);
    print_int_file_content("ints_g_pal.bin");

    build_file_g_task3(file_f_name, "ints_g_fib.bin", "Fibonacci", is_fibonacci);
    print_int_file_content("ints_g_fib.bin");
}

int main() {
    task3_execution();
    return 0;
}
