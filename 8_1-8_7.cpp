#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE_3_4 25
#define MAX_SIZE_6 100
#define MAX_SIZE_5_7 10

void print_int_matrix(int rows, int cols, int matrix[MAX_SIZE_5_7][MAX_SIZE_5_7]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_double_matrix(int rows, int cols, double matrix[MAX_SIZE_6][MAX_SIZE_6]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%7.2lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

void task1() {
    printf("=== Task 1: Replace Element ===\n");
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int N, M;
    int found = 0;

    printf("Initial matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("Enter a natural number M (value to replace): ");
    if (scanf("%d", &M) != 1 || M <= 0) { while(getchar() != '\n'); return; }

    printf("Enter a natural number N (new value): ");
    if (scanf("%d", &N) != 1 || N <= 0) { while(getchar() != '\n'); return; }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == M) {
                matrix[i][j] = N;
                found = 1;
            }
        }
    }

    printf("\nResulting matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }

    if (!found) {
        printf("Element with value %d not found.\n", M);
    }
    printf("\n");
}

void task2() {
    printf("=== Task 2: Replace Element by Indices ===\n");
    double matrix[3][3] = {
        {1.0, 2.3, 3.0},
        {4.5, 6.0, 7.8},
        {9.0, 10.1, 11.2}
    };
    int i, j;
    double a;

    printf("Initial matrix:\n");
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            printf("%7.2lf ", matrix[r][c]);
        }
        printf("\n");
    }

    printf("Enter row index i (0-2): ");
    if (scanf("%d", &i) != 1) { while(getchar() != '\n'); return; }
    printf("Enter column index j (0-2): ");
    if (scanf("%d", &j) != 1) { while(getchar() != '\n'); return; }
    printf("Enter a real number a (new value): ");
    if (scanf("%lf", &a) != 1) { while(getchar() != '\n'); return; }

    if (i >= 0 && i < 3 && j >= 0 && j < 3) {
        matrix[i][j] = a;
        printf("\nElement A[%d][%d] replaced with %.2lf.\n", i, j, a);
        printf("Resulting matrix:\n");
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                printf("%7.2lf ", matrix[r][c]);
            }
            printf("\n");
        }
    } else {
        printf("Error: Invalid indices! Indices must be in range [0, 2].\n");
    }
    printf("\n");
}

void task3() {
    printf("=== Task 3: Input Double Matrix (element by element) ===\n");
    int m, n;
    double matrix[MAX_SIZE_3_4][MAX_SIZE_3_4];

    printf("Enter number of rows m (max %d): ", MAX_SIZE_3_4);
    if (scanf("%d", &m) != 1 || m <= 0 || m > MAX_SIZE_3_4) { while(getchar() != '\n'); return; }
    printf("Enter number of columns n (max %d): ", MAX_SIZE_3_4);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_SIZE_3_4) { while(getchar() != '\n'); return; }

    printf("Enter matrix elements:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter A[%d][%d]: ", i, j);
            if (scanf("%lf", &matrix[i][j]) != 1) { while(getchar() != '\n'); return; }
        }
    }

    printf("\nEntered matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%7.2lf ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void task4() {
    printf("=== Task 4: Input Integer Matrix (row by row) ===\n");
    int m, n;
    int matrix[MAX_SIZE_3_4][MAX_SIZE_3_4];

    printf("Enter number of rows m (max %d): ", MAX_SIZE_3_4);
    if (scanf("%d", &m) != 1 || m <= 0 || m > MAX_SIZE_3_4) { while(getchar() != '\n'); return; }
    printf("Enter number of columns n (max %d): ", MAX_SIZE_3_4);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_SIZE_3_4) { while(getchar() != '\n'); return; }

    printf("Enter matrix elements. For each row, enter %d numbers separated by spaces.\n", n);
    for (int i = 0; i < m; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) { while(getchar() != '\n'); return; }
        }
    }

    printf("\nEntered matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void transpose_matrix(int N, int matrix[MAX_SIZE_5_7][MAX_SIZE_5_7]) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

void task5() {
    printf("=== Task 5: Transpose Square Matrix ===\n");
    int N;
    int matrix[MAX_SIZE_5_7][MAX_SIZE_5_7];

    printf("Enter size of square matrix N (max %d): ", MAX_SIZE_5_7);
    if (scanf("%d", &N) != 1 || N <= 0 || N > MAX_SIZE_5_7) { while(getchar() != '\n'); return; }

    printf("Enter matrix elements %dx%d (row by row):\n", N, N);
    for (int i = 0; i < N; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < N; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) { while(getchar() != '\n'); return; }
        }
    }

    printf("\nInitial matrix:\n");
    print_int_matrix(N, N, matrix);

    transpose_matrix(N, matrix);

    printf("\nTransposed matrix:\n");
    print_int_matrix(N, N, matrix);
    printf("\n");
}

void task6() {
    printf("=== Task 6: Sum of A[i][j] where i - j = k ===\n");
    int N, M;
    int k;
    double sum = 0.0;
    double A[MAX_SIZE_6][MAX_SIZE_6];

    printf("Enter number of rows N (max %d): ", MAX_SIZE_6);
    if (scanf("%d", &N) != 1 || N <= 0 || N > MAX_SIZE_6) { while(getchar() != '\n'); return; }
    printf("Enter number of columns M (max %d): ", MAX_SIZE_6);
    if (scanf("%d", &M) != 1 || M <= 0 || M > MAX_SIZE_6) { while(getchar() != '\n'); return; }
    printf("Enter integer k (can be negative): ");
    if (scanf("%d", &k) != 1) { while(getchar() != '\n'); return; }

    printf("Enter matrix elements %dx%d (real numbers, row by row):\n", N, M);
    for (int i = 0; i < N; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < M; j++) {
            if (scanf("%lf", &A[i][j]) != 1) { while(getchar() != '\n'); return; }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i - j == k) {
                sum += A[i][j];
            }
        }
    }

    printf("\nSum of elements A[i][j] where i - j = %d: %.2lf\n", k, sum);
    printf("\n");
}

double determinant_3x3(double matrix[MAX_SIZE_5_7][MAX_SIZE_5_7]) {
    double det =
        matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
        matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
        matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    return det;
}

void task7() {
    printf("=== Task 7: Determinant of Square Matrix (3x3) ===\n");
    int N;
    double matrix[MAX_SIZE_5_7][MAX_SIZE_5_7];

    printf("Enter size of square matrix N (for this implementation N must be 3): ");
    if (scanf("%d", &N) != 1 || N != 3) { while(getchar() != '\n'); return; }

    printf("Enter matrix elements %dx%d (real numbers, row by row):\n", N, N);
    for (int i = 0; i < N; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < N; j++) {
            if (scanf("%lf", &matrix[i][j]) != 1) { while(getchar() != '\n'); return; }
        }
    }

    printf("\nEntered matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%7.2lf ", matrix[i][j]);
        }
        printf("\n");
    }

    double det = determinant_3x3(matrix);

    printf("\nDeterminant of the matrix: %.4lf\n", det);
    printf("\n");
}

int main() {
    printf("=== Executing tasks on 'Multidimensional Arrays' ===\n\n");

    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();

    printf("=== All tasks completed. ===\n");

    return 0;
}
