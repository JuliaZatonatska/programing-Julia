#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double** create_and_fill_array(int N, int M) {
    double** arr = (double**)malloc(N * sizeof(double*));
    if (arr == NULL) {
        perror("Memory allocation error for row pointer array");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        arr[i] = (double*)malloc(M * sizeof(double));
        if (arr[i] == NULL) {
            perror("Memory allocation error for a row");
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < M; j++) {
            arr[i][j] = (double)rand() / RAND_MAX * 100.0;
        }
    }
    return arr;
}

void print_array(double** arr, int N, int M) {
    if (N <= 0 || M <= 0) {
        printf("\nThe array is empty or has invalid dimensions.\n");
        return;
    }
    printf("\n--- Array (%d x %d) ---\n", N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%8.2lf ", arr[i][j]);
        }
        printf("\n");
    }
    printf("------------------------\n");
}

double** delete_rows(double** arr, int* N, int M, int k1, int k2) {
    if (*N <= 0) {
        printf("The array is already empty. Nothing to delete.\n");
        return arr;
    }

    int start_index = k1 - 1;
    int end_index = k2 - 1;

    if (start_index < 0 || end_index >= *N || start_index > end_index) {
        printf(
            "Error: Invalid row range [%d, %d] for an array with %d rows.\n",
            k1, k2, *N
        );
        return arr;
    }

    int rows_to_delete = end_index - start_index + 1;
    int new_N = *N - rows_to_delete;

    for (int i = start_index; i <= end_index; i++) {
        free(arr[i]);
        arr[i] = NULL;
    }

    int shift_distance = rows_to_delete;
    for (int i = end_index + 1; i < *N; i++) {
        arr[i - shift_distance] = arr[i];
    }

    if (new_N > 0) {
        double** temp = (double**)realloc(arr, new_N * sizeof(double*));
        if (temp != NULL) {
            arr = temp;
        } else {
            perror("Memory reallocation error. Old array preserved.");
        }
    } else {
        free(arr);
        arr = NULL;
    }

    *N = new_N;

    printf(
        "\nOperation completed: %d rows deleted. New size: %d x %d\n",
        rows_to_delete, *N, M
    );

    return arr;
}

void free_array(double** arr, int N) {
    if (arr != NULL) {
        for (int i = 0; i < N; i++) {
            free(arr[i]);
        }
        free(arr);
    }
}

int main() {
    srand((unsigned int)time(NULL));

    int N = 5;
    int M = 4;

    printf("Initial dimensions: N=%d, M=%d\n", N, M);
    double** array = create_and_fill_array(N, M);
    print_array(array, N, M);

    int k1, k2;
    printf("\nEnter the starting row number k1 (1st row is 1): ");
    if (scanf("%d", &k1) != 1) {
        printf("Error reading k1.\n");
        free_array(array, N);
        return 1;
    }

    printf("Enter the ending row number k2: ");
    if (scanf("%d", &k2) != 1) {
        printf("Error reading k2.\n");
        free_array(array, N);
        return 1;
    }

    array = delete_rows(array, &N, M, k1, k2);
    print_array(array, N, M);
    free_array(array, N);

    return 0;
}
