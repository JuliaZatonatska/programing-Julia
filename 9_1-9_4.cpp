#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_SIZE 100

bool is_perfect_square(int n) {
    if (n < 0) return false;
    if (n == 0) return true;
    long long root = round(sqrt((double)n));
    return (root * root == n);
}

bool is_perfect_cube(int n) {
    if (n == 0) return true;
    double cube_root_double = cbrt((double)n);
    int cube_root_int = round(cube_root_double);
    return ((long long)cube_root_int * cube_root_int * cube_root_int == (long long)n);
}

void task1() {
    int n;
    double *arr = NULL;
    double sum_of_squares = 0.0;

    printf("\n--- Task 1: Sum of squares of array elements ---\n");

    do {
        printf("Enter the array size n (positive integer): ");
        if (scanf("%d", &n) != 1 || n <= 0) {
            printf("Error: Enter a positive integer.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);

    arr = (double *)malloc(n * sizeof(double));
    if (arr == NULL) {
        printf("Memory allocation error!\n");
        return;
    }

    printf("Enter %d real numbers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element [%d]: ", i);
        if (scanf("%lf", &arr[i]) != 1) {
            printf("Invalid input. Using 0.0.\n");
            arr[i] = 0.0;
            while (getchar() != '\n');
        }
        sum_of_squares += arr[i] * arr[i];
    }

    printf("\nSum of squares of array elements: %.4f\n", sum_of_squares);
    free(arr);
    printf("Task 1 memory freed.\n");
}

int read_array_until_zero(int arr_ptr[]) {
    int count = 0;
    int input;

    printf("Enter integers (up to %d elements). Input stops at 0.\n", MAX_SIZE);

    for (int i = 0; i < MAX_SIZE; i++) {
        printf("Element [%d]: ", i);
        if (scanf("%d", &input) != 1) {
            printf("Invalid input. Skipping.\n");
            while (getchar() != '\n');
            continue;
        }
        if (input == 0) break;
        arr_ptr[i] = input;
        count++;
    }

    return count;
}

void task2() {
    int array[MAX_SIZE];
    int count;
    int square_count = 0;
    int cube_count = 0;

    printf("\n--- Task 2: Input until zero, perfect squares and cubes ---\n");

    count = read_array_until_zero(array);

    if (count == 0) {
        printf("Array is empty.\n");
        return;
    }

    printf("\nEntered array: [");
    for (int i = 0; i < count; i++) {
        printf("%d%s", array[i], (i == count - 1) ? "" : ", ");
        if (is_perfect_square(array[i])) square_count++;
        if (is_perfect_cube(array[i])) cube_count++;
    }
    printf("]\n");

    printf("Number of array elements: %d\n", count);
    printf("Number of perfect squares: %d\n", square_count);
    printf("Number of perfect cubes: %d\n", cube_count);
}

double *create_and_read_vector(int n, const char *name) {
    double *vec = (double *)malloc(n * sizeof(double));
    if (vec == NULL) {
        printf("Error: Could not allocate memory for vector %s.\n", name);
        return NULL;
    }

    printf("Enter elements for vector %s (size %d):\n", name, n);
    for (int i = 0; i < n; i++) {
        printf("%s[%d]: ", name, i);
        if (scanf("%lf", &vec[i]) != 1) {
            vec[i] = 0.0;
            while (getchar() != '\n');
        }
    }
    return vec;
}

void free_vector(double **vec_ptr) {
    if (*vec_ptr != NULL) {
        free(*vec_ptr);
        *vec_ptr = NULL;
    }
}

double *calculate_difference(const double *vec1, const double *vec2, int n) {
    double *diff_vec = (double *)malloc(n * sizeof(double));
    if (diff_vec == NULL) return NULL;
    for (int i = 0; i < n; i++) diff_vec[i] = vec1[i] - vec2[i];
    return diff_vec;
}

void task3() {
    int n1, n2;
    double *vec_a = NULL;
    double *vec_b = NULL;
    double *vec_diff = NULL;

    printf("\n--- Task 3: Vector difference (dynamic arrays and pointers) ---\n");

    do {
        printf("Enter size of first vector (n1): ");
        if (scanf("%d", &n1) != 1 || n1 <= 0) {
            while (getchar() != '\n');
        } else break;
    } while (1);

    do {
        printf("Enter size of second vector (n2): ");
        if (scanf("%d", &n2) != 1 || n2 <= 0) {
            while (getchar() != '\n');
        } else break;
    } while (1);

    vec_a = create_and_read_vector(n1, "A");
    vec_b = create_and_read_vector(n2, "B");

    if (vec_a == NULL || vec_b == NULL) goto cleanup3;

    if (n1 != n2) {
        printf("\nDifference impossible: Vectors have different sizes (%d != %d).\n", n1, n2);
    } else {
        vec_diff = calculate_difference(vec_a, vec_b, n1);
        if (vec_diff != NULL) {
            printf("\nVector difference A - B (size %d):\n[", n1);
            for (int i = 0; i < n1; i++) {
                printf("%.2f%s", vec_diff[i], (i == n1 - 1) ? "" : ", ");
            }
            printf("]\n");
        }
    }

cleanup3:
    free_vector(&vec_a);
    free_vector(&vec_b);
    free_vector(&vec_diff);
    printf("Task 3 memory freed. Proper termination.\n");
}

double **allocate_matrix_2d(int n) {
    if (n <= 0) return NULL;
    double **mat = (double **)malloc(n * sizeof(double *));
    if (mat == NULL) return NULL;
    for (int i = 0; i < n; i++) {
        mat[i] = (double *)calloc(n, sizeof(double));
        if (mat[i] == NULL) {
            for (int j = 0; j < i; j++) free(mat[j]);
            free(mat);
            return NULL;
        }
    }
    return mat;
}

void read_matrix_2d(double **mat, int n, const char *name) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (scanf("%lf", &mat[i][j]) != 1) {
                mat[i][j] = 0.0;
                while (getchar() != '\n');
            }
        }
}

double **multiply_matrices_2d(double **A, double **B, int n) {
    double **C = allocate_matrix_2d(n);
    if (C == NULL) return NULL;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

void free_matrix_2d(double ***mat_ptr, int n) {
    if (*mat_ptr != NULL) {
        for (int i = 0; i < n; i++) free((*mat_ptr)[i]);
        free(*mat_ptr);
        *mat_ptr = NULL;
    }
}

void print_matrix_2d(double **mat, int n) {
    for (int i = 0; i < n; i++) {
        printf("| ");
        for (int j = 0; j < n; j++) printf("%7.2f ", mat[i][j]);
        printf("|\n");
    }
}

void task4_2d() {
    int n;
    double **mat_a = NULL, **mat_b = NULL, **mat_c = NULL;

    do {
        if (scanf("%d", &n) != 1 || n <= 0) while (getchar() != '\n');
        else break;
    } while (1);

    mat_a = allocate_matrix_2d(n);
    mat_b = allocate_matrix_2d(n);

    if (mat_a == NULL || mat_b == NULL) goto cleanup4_2d;

    read_matrix_2d(mat_a, n, "A");
    read_matrix_2d(mat_b, n, "B");

    mat_c = multiply_matrices_2d(mat_a, mat_b, n);

    if (mat_c != NULL) print_matrix_2d(mat_c, n);

cleanup4_2d:
    free_matrix_2d(&mat_a, n);
    free_matrix_2d(&mat_b, n);
    free_matrix_2d(&mat_c, n);
}

double *allocate_matrix_linear(int n) {
    if (n <= 0) return NULL;
    return (double *)calloc(n * n, sizeof(double));
}

void read_matrix_linear(double *mat, int n, const char *name) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (scanf("%lf", &mat[i * n + j]) != 1) {
                mat[i * n + j] = 0.0;
                while (getchar() != '\n');
            }
        }
}

double *multiply_matrices_linear(const double *A, const double *B, int n) {
    double *C = allocate_matrix_linear(n);
    if (C == NULL) return NULL;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++)
                sum += A[i * n + k] * B[k * n + j];
            C[i * n + j] = sum;
        }
    return C;
}

void free_matrix_linear(double **mat_ptr) {
    if (*mat_ptr != NULL) {
        free(*mat_ptr);
        *mat_ptr = NULL;
    }
}

void print_matrix_linear(const double *mat, int n) {
    for (int i = 0; i < n; i++) {
        printf("| ");
        for (int j = 0; j < n; j++) printf("%7.2f ", mat[i * n + j]);
        printf("|\n");
    }
}

void task4_linear() {
    int n;
    double *mat_a = NULL, *mat_b = NULL, *mat_c = NULL;

    do {
        if (scanf("%d", &n) != 1 || n <= 0) while (getchar() != '\n');
        else break;
    } while (1);

    mat_a = allocate_matrix_linear(n);
    mat_b = allocate_matrix_linear(n);

    if (mat_a == NULL || mat_b == NULL) goto cleanup4_linear;

    read_matrix_linear(mat_a, n, "A");
    read_matrix_linear(mat_b, n, "B");

    mat_c = multiply_matrices_linear(mat_a, mat_b, n);

    if (mat_c != NULL) print_matrix_linear(mat_c, n);

cleanup4_linear:
    free_matrix_linear(&mat_a);
    free_matrix_linear(&mat_b);
    free_matrix_linear(&mat_c);
}

int main() {
    task1();
    task2();
    task3();
    task4_2d();
    task4_linear();
    return 0;
}
