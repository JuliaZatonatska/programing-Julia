#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

#define MAX_SIZE_5 50
#define MAX_N_6 20

void task_1() {
    printf("\n--- TASK 1: Counting elements below a threshold ---\n");
    int array[5] = {15, 8, 22, 10, 5};
    double threshold;
    int count = 0;
    printf("Initial array: {15, 8, 22, 10, 5}\n");
    printf("Enter a real number (threshold): ");
    if (scanf("%lf", &threshold) != 1) {
        printf("Input error. Using 10.0.\n");
        threshold = 10.0;
    }
    while (getchar() != '\n');
    for (int i = 0; i < 5; i++) {
        if (array[i] < threshold) {
            count++;
        }
    }
    printf("Number of elements less than %.2f: %d\n", threshold, count);
}

void task_2() {
    printf("\n--- TASK 2: Printing array in reverse ---\n");
    int array[] = {5, 112, 4, 3};
    int size = sizeof(array) / sizeof(array[0]);
    printf("Initial array: 5, 112, 4, 3\n");
    printf("Elements in reverse: ");
    for (int i = size - 1; i >= 0; i--) {
        printf("%d", array[i]);
        if (i > 0) printf(", ");
    }
    printf("\n");
}

double sum_greater_than_e(double arr[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > M_E) sum += arr[i];
    }
    return sum;
}

void task_3() {
    printf("\n--- TASK 3: Sum of elements greater than Euler's number e ---\n");
    const int N = 10;
    double array[N];
    printf("Fill the array with %d real numbers (one by one):\n", N);
    for (int i = 0; i < N; i++) {
        printf("Enter element array[%d]: ", i);
        if (scanf("%lf", &array[i]) != 1) {
             printf("Input error. Setting 0.0.\n");
             array[i] = 0.0;
             while (getchar() != '\n');
        }
    }
    while (getchar() != '\n');
    double result_sum = sum_greater_than_e(array, N);
    printf("\nEuler's number e is approximately: %.5f\n", M_E);
    printf("Sum of elements greater than e: %.5f\n", result_sum);
}

void input_array_4(int arr[], int n) {
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Enter element arr[%d]: ", i);
        if (scanf("%d", &arr[i]) != 1) {
            printf("Input error. Setting 0.\n");
            arr[i] = 0;
            while (getchar() != '\n');
        }
    }
}

int find_max_4(int arr[], int n) {
    if (n <= 0) return 0;
    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) max_val = arr[i];
    }
    return max_val;
}

void task_4() {
    printf("\n--- TASK 4: Input and find maximum ---\n");
    const int SIZE = 5;
    int array[SIZE];
    input_array_4(array, SIZE);
    while (getchar() != '\n');
    int max_value = find_max_4(array, SIZE);
    printf("Entered array: [");
    for (int i = 0; i < SIZE; i++) {
        printf("%d", array[i]);
        if (i < SIZE - 1) printf(", ");
    }
    printf("]\n");
    printf("Maximum value in the array: %d\n", max_value);
}

void count_parity_5(int *even_count, int *odd_count) {
    int number;
    int i = 0;
    *even_count = 0;
    *odd_count = 0;
    printf("Enter natural numbers (max %d elements).\n", MAX_SIZE_5);
    printf("Input stops when 0 is entered.\n");
    while (i < MAX_SIZE_5) {
        printf("Enter number #%d: ", i + 1);
        if (scanf("%d", &number) != 1) {
            while(getchar() != '\n');
            continue;
        }
        if (number == 0) break;
        if (number > 0) {
            if (number % 2 == 0) (*even_count)++;
            else (*odd_count)++;
            i++;
        }
    }
    while (getchar() != '\n');
}

void task_5() {
    printf("\n--- TASK 5: Counting even/odd until 0 ---\n");
    int even = 0, odd = 0;
    count_parity_5(&even, &odd);
    printf("\n--- Results ---\n");
    printf("Number of even elements: %d\n", even);
    printf("Number of odd elements: %d\n", odd);
}

void input_vector_6(double vec[], int n) {
    for (int i = 0; i < n; i++) {
        printf("vec[%d]: ", i + 1);
        if (scanf("%lf", &vec[i]) != 1) {
            printf("Input error. Setting 0.0.\n");
            vec[i] = 0.0;
            while (getchar() != '\n');
        }
    }
}

void print_vector_6(const char *name, double vec[], int n) {
    printf("%s = (", name);
    for (int i = 0; i < n; i++) {
        printf("%.2f", vec[i]);
        if (i < n - 1) printf(", ");
    }
    printf(")\n");
}

void vector_sum_6(double vec1[], double vec2[], double result_vec[], int n) {
    for (int i = 0; i < n; i++) result_vec[i] = vec1[i] + vec2[i];
}

double scalar_product_6(double vec1[], double vec2[], int n) {
    double product = 0.0;
    for (int i = 0; i < n; i++) product += vec1[i] * vec2[i];
    return product;
}

void task_6() {
    printf("\n--- TASK 6: Vector Operations ---\n");
    int n;
    double vector_A[MAX_N_6], vector_B[MAX_N_6], vector_Sum[MAX_N_6];
    printf("Enter vector dimension (n < %d): ", MAX_N_6);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_N_6) {
        n = 3;
    }
    while (getchar() != '\n');
    input_vector_6(vector_A, n);
    while (getchar() != '\n');
    input_vector_6(vector_B, n);
    while (getchar() != '\n');
    print_vector_6("Vector A", vector_A, n);
    print_vector_6("Vector B", vector_B, n);
    vector_sum_6(vector_A, vector_B, vector_Sum, n);
    print_vector_6("A + B", vector_Sum, n);
    double dot_product = scalar_product_6(vector_A, vector_B, n);
    printf("A * B = %.2f\n", dot_product);
}

int main() {
    task_1();
    task_2();
    task_3();
    task_4();
    task_5();
    task_6();
    return 0;
}
