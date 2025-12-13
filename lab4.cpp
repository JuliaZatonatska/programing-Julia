#include <stdio.h>
#include <math.h>
#include <float.h>

double calculate_nested_sin(double x, int n) {
    double result = x;
    int i;
    if (n <= 0) {
        return x;
    }
    for (i = 0; i < n; i++) {
        result = sin(result);
    }
    return result;
}

void task1() {
    double x;
    int n;
    printf("Enter a real number x: ");
    if (scanf("%lf", &x) != 1) { while (getchar() != '\n'); return; }
    printf("Enter a natural number n (number of repetitions): ");
    if (scanf("%d", &n) != 1 || n <= 0) { printf("Invalid input. n must be a positive integer.\n"); while (getchar() != '\n'); return; }

    double y = calculate_nested_sin(x, n);

    printf("\n--- Task 1 Results ---\n");
    printf("y = sin(sin(...sin(%.4lf)...)) (%d times) = %.8lf\n", x, n, y);
}

void task2() {
    int n;
    int i;
    printf("Enter a natural number n (max 12 for int type): ");
    if (scanf("%d", &n) != 1 || n <= 0) { printf("Invalid input. n must be a positive integer.\n"); while (getchar() != '\n'); return; }

    printf("\n--- Task 2 Results (n = %d) ---\n", n);
    long long factorial = 1;

    printf("n! = ");
    for (i = 1; i <= n; i++) {
        factorial *= i;
        printf("%d", i);
        if (i < n) { printf("*"); }
    }
    printf(" = %lld (Ascending loop)\n", factorial);

    factorial = 1;
    printf("n! = ");
    for (i = n; i >= 1; i--) {
        factorial *= i;
        printf("%d", i);
        if (i > 1) { printf("*"); }
    }
    printf(" = %lld (Descending loop)\n", factorial);
}

double polynomial_a(double x, int n) {
    double sum = 1.0;
    int i;
    for (i = 1; i <= n; i++) { sum += pow(x, i); }
    return sum;
}
double polynomial_b(double x, double y_val, int n) {
    double sum = 1.0;
    int i;
    for (i = 1; i <= n; i++) { sum += pow(x, i) * pow(y_val, i); }
    return sum;
}

void task3() {
    double x_a = 2.0; int n_a = 3;
    double x_b = 1.0; double y_b = 2.0; int n_b = 4;

    double result_a = polynomial_a(x_a, n_a);
    double result_b = polynomial_b(x_b, y_b, n_b);

    printf("\n--- Task 3 Results ---\n");
    printf("a) y = x^3 + x^2 + x + 1 (x=2): %.0lf\n", result_a);
    printf("б) y = 1 + xy + (xy)^2 + ... + (xy)^4 (x=1, y=2): %.0lf\n", result_b);
}

void task4() {
    int n;
    double x;
    printf("Enter a natural number n: ");
    if (scanf("%d", &n) != 1 || n <= 0) { printf("Invalid input for n.\n"); while (getchar() != '\n'); return; }
    printf("Enter a real number x: ");
    if (scanf("%lf", &x) != 1) { printf("Invalid input for x.\n"); while (getchar() != '\n'); return; }

    double sum = 0.0;
    int i;

    for (i = 1; i <= n; i++) {
        double term = i * pow(x, i);
        sum += term;
    }

    printf("\n--- Task 4 Results ---\n");
    printf("Sum of x + 2x^2 + ... + %dx^%d (x=%.2lf): %.4lf\n", n, n, x, sum);
}

void task14() {
    int current_num;
    int prev_num = 0;
    int sign_changes_count = 0;

    printf("Enter a sequence of non-zero integers (0 to finish):\n");

    if (scanf("%d", &current_num) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    if (current_num == 0) {
        printf("Sequence is empty.\n");
        return;
    }

    prev_num = current_num;

    while (1) {
        if (scanf("%d", &current_num) != 1) {
            printf("Invalid input detected. Stopping.\n");
            break;
        }

        if (current_num == 0) {
            break;
        }

        if ((prev_num > 0) != (current_num > 0)) {
            sign_changes_count++;
        }

        prev_num = current_num;
    }

    printf("\n--- Task 14 Results ---\n");
    printf("Number of sign changes in the sequence: %d\n", sign_changes_count);
}

void task15() {
    int current_num;
    int min_num = -1;
    int min_index = 0;
    int current_index = 0;

    printf("Enter a sequence of non-zero natural numbers (0 to finish):\n");

    while (1) {
        if (scanf("%d", &current_num) != 1) {
            printf("Invalid input detected. Stopping.\n");
            break;
        }

        if (current_num == 0) {
            break;
        }

        if (current_num < 0) {
            printf("Warning: Non-natural number entered (%d). Skipping.\n", current_num);
            continue;
        }

        current_index++;

        if (current_index == 1 || current_num < min_num) {
            min_num = current_num;
            min_index = current_index;
        }
    }

    printf("\n--- Task 15 Results ---\n");
    if (min_index == 0) {
        printf("Sequence is empty.\n");
    } else {
        printf("Smallest number is %d, found at index: %d\n", min_num, min_index);
    }
}

void task16() {
    double current_num;

    double max_negative = -DBL_MAX;
    int negative_found = 0;

    double min_positive = DBL_MAX;
    int positive_found = 0;

    printf("Enter a sequence of non-zero real numbers (0 to finish):\n");

    while (1) {
        if (scanf("%lf", &current_num) != 1) {
            printf("Invalid input detected. Stopping.\n");
            break;
        }

        if (current_num == 0.0) {
            break;
        }

        if (current_num < 0.0) {
            negative_found = 1;
            if (current_num > max_negative) {
                max_negative = current_num;
            }
        } else {
            positive_found = 1;
            if (current_num < min_positive) {
                min_positive = current_num;
            }
        }
    }

    printf("\n--- Task 16 Results ---\n");

    if (negative_found) {
        printf("Largest among negative numbers: %.4lf\n", max_negative);
    } else {
        if (positive_found) {
            printf("No negative numbers found. Smallest among positive numbers: %.4lf\n", min_positive);
        } else {
            printf("Sequence is empty or contains only zeros.\n");
        }
    }
}


void task17() {
    double rate_A;
    double addition_B;
    double principal_D;
    double target_P;
    int years = 0;

    printf("Enter annual interest rate A (%%): ");
    if (scanf("%lf", &rate_A) != 1 || rate_A < 0) { printf("Invalid input for A.\n"); while (getchar() != '\n'); return; }

    printf("Enter fixed annual addition B (UAH): ");
    if (scanf("%lf", &addition_B) != 1 || addition_B < 0) { printf("Invalid input for B.\n"); while (getchar() != '\n'); return; }

    printf("Enter initial principal D (UAH): ");
    if (scanf("%lf", &principal_D) != 1 || principal_D <= 0) { printf("Invalid input for D.\n"); while (getchar() != '\n'); return; }

    printf("Enter target amount P (UAH): ");
    if (scanf("%lf", &target_P) != 1 || target_P <= principal_D) { printf("Invalid input. P must be greater than D.\n"); while (getchar() != '\n'); return; }

    double current_amount = principal_D;
    double interest_rate_multiplier = 1.0 + (rate_A / 100.0);

    while (current_amount < target_P) {
        years++;

        current_amount = current_amount * interest_rate_multiplier;

        current_amount = current_amount + addition_B;

        if (years > 1000) {
            printf("Warning: Calculation stopped after 1000 years to prevent infinite loop.\n");
            break;
        }
    }

    printf("\n--- Task 17 Results ---\n");
    printf("Initial amount (D): %.2lf UAH\n", principal_D);
    printf("Target amount (P): %.2lf UAH\n", target_P);
    printf("Years required to reach target amount: %d\n", years);
    printf("Final amount: %.2lf UAH\n", current_amount);
}

int main() {
    int choice;
    printf("Welcome to the C Beginner Task Solver (Extended Version)!\n");

    while (1) {
        printf("\n------------------------------------------------\n");
        printf("Choose task (1-4, 14-17, 0 to exit): ");

        if (scanf("%d", &choice) != 1) {
             printf("Invalid input. Please enter a number.\n");
             while (getchar() != '\n');
             continue;
        }

        while (getchar() != '\n');

        if (choice == 0) break;

        switch(choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 14: task14(); break;
            case 15: task15(); break;
            case 16: task16(); break;
            case 17: task17(); break;
            default: printf("No such task implemented (1-4, 14-17 only).\n");
        }
    }
    printf("\nExiting program. Goodbye!\n");
    return 0;
}