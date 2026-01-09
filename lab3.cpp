#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void task1();
void task2();
void task12();

void task1() {
    int number, units, tens, hundreds;

    printf("--- Task 1: Three-Digit Number Processing ---\n");
    printf("Enter a natural three-digit number (100-999): ");

    if (scanf("%d", &number) != 1 || number < 100 || number > 999) {
        printf("Error: Invalid or non-three-digit number entered.\n");
        while (getchar() != '\n');
        return;
    }

    hundreds = number / 100;
    tens = (number / 10) % 10;
    units = number % 10;

    printf("\na) Digits of the number %d:\n", number);
    printf("   Hundreds: %d\n", hundreds);
    printf("   Tens: %d\n", tens);
    printf("   Units: %d\n", units);

    int sum_of_digits = hundreds + tens + units;
    printf("\nb) Sum of digits: %d + %d + %d = %d\n", hundreds, tens, units, sum_of_digits);

    int reversed_number = units * 100 + tens * 10 + hundreds;
    printf("\nc) Number formed by reading right-to-left: %d\n", reversed_number);
    printf("---------------------------------------------------\n");
}

void task2() {
    int number, c1, c2, c3;

    printf("--- Task 2: Permutations of a Three-Digit Number ---\n");
    printf("Enter a natural three-digit number (100-999): ");

    if (scanf("%d", &number) != 1 || number < 100 || number > 999) {
        printf("Error: Invalid or non-three-digit number entered.\n");
        while (getchar() != '\n');
        return;
    }

    c1 = number / 100;
    c2 = (number / 10) % 10;
    c3 = number % 10;

    if (c1 != c2 && c1 != c3 && c2 != c3) {
        printf("\nDigits (%d, %d, %d) are different. All possible permutations:\n", c1, c2, c3);

        printf("1. %d%d%d\n", c1, c2, c3);
        printf("2. %d%d%d\n", c1, c3, c2);
        printf("3. %d%d%d\n", c2, c1, c3);
        printf("4. %d%d%d\n", c2, c3, c1);
        printf("5. %d%d%d\n", c3, c1, c2);
        printf("6. %d%d%d\n", c3, c2, c1);

    } else {
        printf("\nDigits of number %d ARE NOT different, so no permutations are shown.\n", number);
    }
    while (getchar() != '\n');
    printf("---------------------------------------------------\n");
}


void task12() {
    double a, b, c;

    printf("--- Task 12: Triangle Check ---\n");
    printf("Enter the length of side a (use dot for decimals): ");
    if (scanf("%lf", &a) != 1 || a <= 0) {
        printf("Error: Invalid value for side a.\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter the length of side b: ");
    if (scanf("%lf", &b) != 1 || b <= 0) {
        printf("Error: Invalid value for side b.\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter the length of side c: ");
    if (scanf("%lf", &c) != 1 || c <= 0) {
        printf("Error: Invalid value for side c.\n");
        while (getchar() != '\n');
        return;
    }

    while (getchar() != '\n');

    if (a + b <= c || a + c <= b || b + c <= a) {
        printf("\n=> A triangle with sides %.2f, %.2f, %.2f DOES NOT EXIST (triangle inequality violated).\n", a, b, c);
        return;
    }

    printf("\n=> A triangle EXISTS.\n");

    double max_side_sq;
    double sum_of_other_sq;

    double a_sq = a * a;
    double b_sq = b * b;
    double c_sq = c * c;

    if (a >= b && a >= c) {
        max_side_sq = a_sq;
        sum_of_other_sq = b_sq + c_sq;
    } else if (b >= a && b >= c) {
        max_side_sq = b_sq;
        sum_of_other_sq = a_sq + c_sq;
    } else {
        max_side_sq = c_sq;
        sum_of_other_sq = a_sq + b_sq;
    }

    const double EPSILON = 0.0000001;

    if (fabs(max_side_sq - sum_of_other_sq) < EPSILON) {
        printf("=> It is a RIGHT-ANGLED triangle.\n");
    } else if (max_side_sq < sum_of_other_sq) {
        printf("=> It is an ACUTE-ANGLED triangle.\n");
    } else {
        printf("=> It is an OBTUSE-ANGLED triangle.\n");
    }

    printf("----------------------------------\n");
}

int main() {
    int choice;
    printf("Welcome to the C tasks collection!\n");

    while (1) {
        printf("\n======================================================\n");
        printf("Select a task to run:\n");
        printf(" 1: Three-Digit Number Processing\n");
        printf(" 2: Three-Digit Number Permutations\n");
        printf(" 12: Triangle Existence and Type Check\n");
        printf(" 0: Exit the program\n");
        printf("------------------------------------------------------\n");
        printf("Enter task number (0 to exit): ");

        if (scanf("%d", &choice) != 1) {
            printf("\nError: Invalid input. Please try again.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 0) {
            printf("\nProgram finished. Goodbye!\n");
            break;
        }

        switch(choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 12: task12(); break;
            default: printf("\nNo such task (select 1, 2, 12, or 0).\n");
        }
    }

    return 0;
}