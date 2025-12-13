//
// Created by User on 23.09.2025.
//
#include <stdio.h>
#include <math.h>

void task3() {
    int n_max = 1000;
    int max_steps = 0;
    int number_with_max_steps = 0;

    printf("--- Task 3: Collatz Sequence (N up to %d) ---\n", n_max);

    for (int n = 1; n < n_max; n++) {
        long long current_a = n;
        int steps = 0;

        while (current_a != 1) {
            steps++;

            if (current_a % 2 == 0) {
                current_a = current_a / 2;
            } else {
                current_a = 3 * current_a + 1;
            }
        }

        if (steps > max_steps) {
            max_steps = steps;
            number_with_max_steps = n;
        }
    }

    printf("Maximum number of steps for N < %d is: %d\n", n_max, max_steps);
    printf("Achieved by the starting number n = %d\n", number_with_max_steps);
}


void task5() {
    long long x_n_minus_3 = -99;
    long long x_n_minus_2 = -99;
    long long x_n_minus_1 = -99;

    long long current_x;
    int n = 4;

    printf("--- Task 5: Recurrence Sequence x_n (x1=x2=x3=-99) ---\n");
    printf("Searching for the smallest positive term...\n");

    while (1) {
        current_x = x_n_minus_1 + x_n_minus_3 + 100;

        if (current_x > 0) {
            printf("The smallest positive term is: x_%d = %lld\n", n, current_x);
            return;
        }

        x_n_minus_3 = x_n_minus_2;
        x_n_minus_2 = x_n_minus_1;
        x_n_minus_1 = current_x;

        n++;

        if (n > 1000000) {
            printf("Sequence limit reached without finding a positive term within 1,000,000 steps.\n");
            return;
        }
    }
}


void task9() {
    const double v0 = 1.0;
    const double v1 = 0.3;
    int i_target;

    printf("--- Task 9a: Recurrence Sequence v_i (v0=1, v1=0.3) ---\n");
    printf("Enter the index 'i' (i >= 0) of the element you want to calculate: ");

    if (scanf("%d", &i_target) != 1 || i_target < 0) {
        printf("Invalid input. Please enter a non-negative integer.\n");
        while (getchar() != '\n');
        return;
    }

    if (i_target == 0) {
        printf("v_0 = %.15lf\n", v0);
        return;
    }
    if (i_target == 1) {
        printf("v_1 = %.15lf\n", v1);
        return;
    }

    double v_even = v0;
    double v_odd = v1;
    double current_v = 0.0;

    for (int i = 2; i <= i_target; i++) {
        if (i % 2 == 0) {
            current_v = (i + 2.0) * v_even;
            v_even = current_v;
        } else {
            current_v = (i + 2.0) * v_odd;
            v_odd = current_v;
        }
    }

    printf("v_%d = %.15lf\n", i_target, current_v);
}


int main() {
    int choice;

    while (1) {
        printf("\n============================================\n");
        printf("Available tasks: 3, 5, 9\n");
        printf("Choose task (3, 5, 9) or (0 to exit): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Clearing input buffer.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 0) break;

        switch(choice) {
            case 3: task3(); break;
            case 5: task5(); break;
            case 9: task9(); break;
            default: printf("No such task: %d\n", choice);
        }
    }
    printf("Exiting program. Goodbye!\n");
    return 0;
}