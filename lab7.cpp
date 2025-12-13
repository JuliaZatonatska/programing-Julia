#include <stdio.h>
#include <math.h>

#define MAX_SIZE 50
#define N_ELEMENTS 10

void task1() {
    int array[5] = {15, 8, 22, 1, 30};
    double target_number;
    int count = 0;
    int i;

    printf("--- Task 1: Comparison with a number ---\n");

    printf("Initialized array: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("Enter a real number to compare: ");
    if (scanf("%lf", &target_number) != 1) {
        printf("Number input error.\n");
        return;
    }

    for (i = 0; i < 5; i++) {
        if (array[i] < target_number) {
            count++;
        }
    }

    printf("Entered number: %.2f\n", target_number);
    printf("Number of array elements less than %.2f: %d\n", target_number, count);
}

void task2() {
    int array[] = {5, 112, 4, 3};
    int size = sizeof(array) / sizeof(array[0]);
    int i;

    printf("--- Task 2: Reverse output ---\n");
    printf("Initial array: 5, 112, 4, 3\n");
    printf("Elements in reverse order: ");

    for (i = size - 1; i >= 0; i--) {
        printf("%d", array[i]);
        if (i > 0) {
            printf(", ");
        }
    }
    printf("\n");
}

double sum_greater_than_E(double arr[], int n) {
    double sum = 0.0;
    int i;
    const double E_CONST = M_E;

    printf("Euler's number (e): %.6f\n", E_CONST);

    for (i = 0; i < n; i++) {
        if (arr[i] > E_CONST) {
            sum += arr[i];
        }
    }
    return sum;
}

void task3() {
    double array[N_ELEMENTS];
    int i;
    double result_sum;

    printf("--- Task 3: Sum of elements greater than e ---\n");
    printf("Enter %d real numbers (double) one by one:\n", N_ELEMENTS);

    for (i = 0; i < N_ELEMENTS; i++) {
        printf("Element %d/%d: ", i + 1, N_ELEMENTS);
        if (scanf("%lf", &array[i]) != 1) {
            printf("Input error. Use a dot for the decimal part.\n");
            while (getchar() != '\n');
            return;
        }
    }

    result_sum = sum_greater_than_E(array, N_ELEMENTS);

    printf("Sum of array elements greater than Euler's number e: %.2f\n", result_sum);
}

void input_array_int(int arr[], int n) {
    int i;
    printf("Enter %d integers one by one:\n", n);
    for (i = 0; i < n; i++) {
        printf("Element %d/%d: ", i + 1, n);
        if (scanf("%d", &arr[i]) != 1) {
            printf("Input error. Enter an integer.\n");
            while (getchar() != '\n');
            return;
        }
    }
}

int find_max(int arr[], int n) {
    int i;
    int max_val = arr[0];

    for (i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

void task4() {
    int array[5];
    int max_result;

    printf("--- Task 4: Finding the maximum ---\n");
    input_array_int(array, 5);
    max_result = find_max(array, 5);

    printf("Maximum value in the array: %d\n", max_result);
}

void count_parity(int arr[], int count, int *even, int *odd) {
    int i;
    *even = 0;
    *odd = 0;

    for (i = 0; i < count; i++) {
        if (arr[i] % 2 == 0) {
            (*even)++;
        } else {
            (*odd)++;
        }
    }
}

void task5() {
    int array[MAX_SIZE];
    int input_num;
    int current_count = 0;
    int even_count = 0;
    int odd_count = 0;

    printf("--- Task 5: Counting even and odd numbers ---\n");
    printf("Enter natural numbers (max %d). Enter 0 to finish input.\n", MAX_SIZE);

    while (current_count < MAX_SIZE) {
        printf("Enter a number (0 to finish): ");
        if (scanf("%d", &input_num) != 1) {
            printf("Input error. Enter an integer.\n");
            while (getchar() != '\n');
            continue;
        }

        if (input_num == 0) {
            break;
        }

        array[current_count++] = input_num;
    }

    printf("Input completed. Total number of elements: %d\n", current_count);

    count_parity(array, current_count, &even_count, &odd_count);

    printf("Number of even elements: %d\n", even_count);
    printf("Number of odd elements: %d\n", odd_count);
}

void task17() {
    int n, i;
    double a[MAX_SIZE];
    double min_val, max_val;
    double sum = 0.0;
    int min_removed = 0;
    int max_removed = 0;
    int elements_to_average;
    double final_score;

    printf("--- Task 17: Athlete score evaluation ---\n");
    printf("Enter the number of scores (n, max %d): ", MAX_SIZE);

    if (scanf("%d", &n) != 1 || n < 3 || n > MAX_SIZE) {
        printf("Invalid number of scores. At least 3 are required.\n");
        return;
    }

    printf("Enter %d real numbers (scores) one by one:\n", n);
    for (i = 0; i < n; i++) {
        printf("Score %d: ", i + 1);
        if (scanf("%lf", &a[i]) != 1) {
            printf("Score input error.\n");
            while (getchar() != '\n');
            return;
        }
    }

    min_val = a[0];
    max_val = a[0];
    for (i = 1; i < n; i++) {
        if (a[i] < min_val) min_val = a[i];
        if (a[i] > max_val) max_val = a[i];
    }

    printf("Found lowest score: %.2f and highest score: %.2f\n", min_val, max_val);

    for (i = 0; i < n; i++) {
        if (a[i] == min_val && min_removed == 0) {
            min_removed = 1;
        } else if (a[i] == max_val && max_removed == 0) {
            max_removed = 1;
        } else {
            sum += a[i];
        }
    }

    elements_to_average = n - (min_removed + max_removed);

    if (elements_to_average <= 0) {
        printf("Not enough scores to calculate average.\n");
        return;
    }

    final_score = sum / elements_to_average;

    printf("Scores removed: one lowest (%.2f) and one highest (%.2f).\n", min_val, max_val);
    printf("Number of scores counted: %d\n", elements_to_average);
    printf("Sum of counted scores: %.2f\n", sum);
    printf("Final athlete score: %.2f\n", final_score);
}

int main() {
    int choice;

    while (1) {
        printf("\n======================================================\n");
        printf(" Choose a task to execute:\n");
        printf(" 1. Task 1 (Array: less than a number)\n");
        printf(" 2. Task 2 (Array: reverse output)\n");
        printf(" 3. Task 3 (Array: sum greater than e)\n");
        printf(" 4. Task 4 (Array: find maximum)\n");
        printf(" 5. Task 5 (Array: count even/odd)\n");
        printf(" 17. Task 17 (Athlete: average score without min/max)\n");
        printf(" 0. Exit program\n");
        printf("======================================================\n");
        printf("Your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        if (choice == 0) break;

        switch (choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            case 17: task17(); break;
            default: printf("Task number %d not found.\n", choice);
        }
    }

    printf("\nProgram finished. Goodbye!\n");
    return 0;
}