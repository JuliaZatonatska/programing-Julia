#include <stdio.h>
#include <math.h>
#include <stdbool.h>

void print_matrix_int(int rows, int cols, int *matrix) {
    printf("\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

void print_matrix_double(int rows, int cols, double *matrix) {
    printf("\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%8.2f ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

void task1() {
    printf("--- Task 1: Replace elements ---\n");
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int M, N;
    bool found = false;
    printf("Initial matrix:\n");
    print_matrix_int(3, 3, (int *)matrix);
    printf("Enter value M to replace: ");
    if (scanf("%d", &M) != 1) return;
    printf("Enter new value N: ");
    if (scanf("%d", &N) != 1) return;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == M) {
                matrix[i][j] = N;
                found = true;
            }
        }
    }
    if (!found) {
        printf("Value M (%d) was not found.\n", M);
    } else {
        printf("Value M has been replaced with N.\n");
    }
    printf("Resulting matrix:\n");
    print_matrix_int(3, 3, (int *)matrix);
}

void task2() {
    printf("--- Task 2: Change element by index ---\n");
    double matrix[3][3] = {
        {1.1, 2.2, 3.3},
        {4.4, 5.5, 6.6},
        {7.7, 8.8, 9.9}
    };
    int i, j;
    double a;
    printf("Initial matrix:\n");
    print_matrix_double(3, 3, (double *)matrix);
    printf("Enter row index (i), column index (j) [0–2], and new value: ");
    if (scanf("%d %d %lf", &i, &j, &a) != 3) return;
    if (i >= 0 && i < 3 && j >= 0 && j < 3) {
        matrix[i][j] = a;
        printf("Updated matrix:\n");
        print_matrix_double(3, 3, (double *)matrix);
    } else {
        printf("Error: Invalid indices. Indices must be in range [0, 2].\n");
    }
}

void task3() {
    printf("--- Task 3: Input and output of a double matrix (element by element) ---\n");
    int m, n;
    printf("Enter number of rows (m < 20) and columns (n < 20): ");
    if (scanf("%d %d", &m, &n) != 2) return;
    if (m <= 0 || n <= 0 || m >= 20 || n >= 20) {
        printf("Error: Invalid matrix size (m and n must be in [1, 19]).\n");
        return;
    }
    double matrix[m][n];
    printf("Enter matrix elements (%d x %d):\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter element [%d][%d]: ", i, j);
            if (scanf("%lf", &matrix[i][j]) != 1) return;
        }
    }
    printf("Entered matrix:\n");
    print_matrix_double(m, n, (double *)matrix);
}

void task4() {
    printf("--- Task 4: Input and output of an integer matrix (row by row) ---\n");
    int m, n;
    printf("Enter number of rows (m < 25) and columns (n < 25): ");
    if (scanf("%d %d", &m, &n) != 2) return;
    if (m <= 0 || n <= 0 || m >= 25 || n >= 25) {
        printf("Error: Invalid matrix size (m and n must be in [1, 24]).\n");
        return;
    }
    int matrix[m][n];
    printf("Enter matrix elements (%d x %d):\n", m, n);
    for (int i = 0; i < m; i++) {
        printf("Enter elements for row %d (separated by space): ", i);
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) return;
        }
    }
    printf("Entered matrix:\n");
    print_matrix_int(m, n, (int *)matrix);
}

void task8() {
    printf("--- Task 8: Column permutation for diagonal maxima (n x m) ---\n");
    int n, m;
    printf("Enter number of rows (n < 100) and columns (m < 100): ");
    if (scanf("%d %d", &n, &m) != 2) return;
    if (n <= 0 || m <= 0 || n >= 100 || m >= 100) {
        printf("Error: Invalid size n or m (must be in [1, 99]).\n");
        return;
    }
    double matrix[n][m];
    printf("Enter matrix elements (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (scanf("%lf", &matrix[i][j]) != 1) return;

    int cols_to_permute = (n < m) ? n : m;
    int column_map[cols_to_permute];
    for (int i = 0; i < cols_to_permute; i++) column_map[i] = -1;

    bool col_used[m];
    for (int i = 0; i < m; i++) col_used[i] = false;

    for (int i = 0; i < cols_to_permute; i++) {
        double max_val = -INFINITY;
        int max_col = -1;
        for (int j = 0; j < m; j++) {
            if (!col_used[j] && matrix[i][j] > max_val) {
                max_val = matrix[i][j];
                max_col = j;
            }
        }
        if (max_col != -1) {
            column_map[i] = max_col;
            col_used[max_col] = true;
        }
    }

    double result[n][m];
    int current_col_in_result = 0;

    for (int i = 0; i < cols_to_permute; i++) {
        if (column_map[i] != -1) {
            for (int r = 0; r < n; r++) {
                result[r][current_col_in_result] = matrix[r][column_map[i]];
            }
            current_col_in_result++;
        }
    }

    for (int c = 0; c < m; c++) {
        if (!col_used[c]) {
            for (int r = 0; r < n; r++) {
                result[r][current_col_in_result] = matrix[r][c];
            }
            current_col_in_result++;
        }
    }

    printf("Original matrix:\n");
    print_matrix_double(n, m, (double *)matrix);

    printf("Matrix with permuted columns (maxima on 'main diagonal'):\n");
    print_matrix_double(n, m, (double *)result);
}

void task9() {
    printf("--- Task 9: Inverse matrix (Gauss–Jordan method) ---\n");
    int n;
    printf("Enter size of square matrix n (n < 200): ");
    if (scanf("%d", &n) != 1) return;
    if (n <= 0 || n >= 200) {
        printf("Error: Invalid size n (must be in [1, 199]).\n");
        return;
    }
    double a[n][2 * n];
    printf("Enter matrix elements (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (scanf("%lf", &a[i][j]) != 1) return;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][n + j] = (i == j) ? 1.0 : 0.0;
    for (int i = 0; i < n; i++) {
        int p = i;
        for (int k = i + 1; k < n; k++)
            if (fabs(a[k][i]) > fabs(a[p][i])) p = k;
        if (fabs(a[p][i]) < 1e-9) {
            printf("Error: Matrix is singular. Inverse does not exist.\n");
            return;
        }
        if (p != i)
            for (int j = 0; j < 2 * n; j++) {
                double t = a[i][j];
                a[i][j] = a[p][j];
                a[p][j] = t;
            }
        double d = a[i][i];
        for (int j = 0; j < 2 * n; j++) a[i][j] /= d;
        for (int k = 0; k < n; k++)
            if (k != i) {
                double f = a[k][i];
                for (int j = 0; j < 2 * n; j++)
                    a[k][j] -= f * a[i][j];
            }
    }
    printf("Inverse matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%8.2f ", a[i][n + j]);
        printf("\n");
    }
}

void task10() {
    printf("--- Task 10: Rotate matrix 180 degrees ---\n");
    int nh;
    printf("Enter half-size (nh), matrix size will be 2nh x 2nh: ");
    if (scanf("%d", &nh) != 1) return;
    if (nh <= 0) {
        printf("Error: Half-size must be greater than 0.\n");
        return;
    }
    int n = 2 * nh;
    int m[n][n];
    printf("Enter matrix elements (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (scanf("%d", &m[i][j]) != 1) return;

    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n; j++) {
            int r1 = i;
            int c1 = j;
            int r2 = n - 1 - i;
            int c2 = n - 1 - j;
            if (r1 * n + c1 < r2 * n + c2) {
                int temp = m[r1][c1];
                m[r1][c1] = m[r2][c2];
                m[r2][c2] = temp;
            }
        }
    }
    if (n % 2 != 0) {
        int mid = n / 2;
        int max_j = n / 2;
        for (int j = 0; j < max_j; j++) {
            int r1 = mid;
            int c1 = j;
            int r2 = mid;
            int c2 = n - 1 - j;
            int temp = m[r1][c1];
            m[r1][c1] = m[r2][c2];
            m[r2][c2] = temp;
        }
    }

    printf("Resulting matrix rotated 180 degrees:\n");
    print_matrix_int(n, n, (int *)m);
}

int main() {
    int choice;
    while (1) {
        printf("\n======================================================\n");
        printf("Select a task (1, 2, 3, 4, 8, 9, 10) or 0 to exit: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        if (choice == 0) break;
        switch (choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 8: task8(); break;
            case 9: task9(); break;
            case 10: task10(); break;
            default: printf("Task %d not found.\n", choice);
        }
    }
    printf("Program finished.\n");
    return 0;
}