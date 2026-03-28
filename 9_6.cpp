#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int rows;
    int cols;
    int** data;
} Matrix;

Matrix* createMatrix() {
    Matrix* m = (Matrix*)malloc(sizeof(Matrix));
    if (m == NULL) {
        perror("Memory allocation error for Matrix structure");
        return NULL;
    }

    printf("\n--- Input of a new matrix ---\n");
    printf("Enter the number of rows: ");
    if (scanf("%d", &(m->rows)) != 1 || m->rows <= 0) {
        printf("Invalid input for number of rows.\n");
        free(m);
        return NULL;
    }

    printf("Enter the number of columns: ");
    if (scanf("%d", &(m->cols)) != 1 || m->cols <= 0) {
        printf("Invalid input for number of columns.\n");
        free(m);
        return NULL;
    }

    m->data = (int**)malloc(m->rows * sizeof(int*));
    if (m->data == NULL) {
        perror("Memory allocation error for row pointers");
        free(m);
        return NULL;
    }

    for (int i = 0; i < m->rows; i++) {
        m->data[i] = (int*)malloc(m->cols * sizeof(int));
        if (m->data[i] == NULL) {
            perror("Memory allocation error for row elements");
            for (int j = 0; j < i; j++) {
                free(m->data[j]);
            }
            free(m->data);
            free(m);
            return NULL;
        }
    }

    printf("Enter the elements of the %dx%d matrix:\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            if (scanf("%d", &(m->data[i][j])) != 1) {
                printf("Invalid element input. Terminating input.\n");
                for (int r = 0; r < m->rows; r++) {
                    free(m->data[r]);
                }
                free(m->data);
                free(m);
                return NULL;
            }
        }
    }

    return m;
}

void freeMatrix(Matrix* m) {
    if (m == NULL) {
        return;
    }

    if (m->data != NULL) {
        for (int i = 0; i < m->rows; i++) {
            free(m->data[i]);
            m->data[i] = NULL;
        }
        free(m->data);
        m->data = NULL;
    }

    free(m);
}

void printMatrix(const Matrix* m) {
    if (m == NULL || m->data == NULL) {
        printf("[Matrix is empty or uninitialized]\n");
        return;
    }

    printf("Matrix %dx%d:\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%5d ", m->data[i][j]);
        }
        printf("\n");
    }
}

Matrix* addMatrices(const Matrix* m1, const Matrix* m2) {
    if (m1 == NULL || m2 == NULL || m1->rows != m2->rows || m1->cols != m2->cols) {
        printf("Error: Matrices have different sizes or are uninitialized. Addition is impossible.\n");
        return NULL;
    }

    Matrix* sum = (Matrix*)malloc(sizeof(Matrix));
    if (sum == NULL) {
        perror("Memory allocation error for sum matrix");
        return NULL;
    }

    sum->rows = m1->rows;
    sum->cols = m1->cols;

    sum->data = (int**)malloc(sum->rows * sizeof(int*));
    if (sum->data == NULL) {
        perror("Memory allocation error for sum row pointers");
        free(sum);
        return NULL;
    }

    for (int i = 0; i < sum->rows; i++) {
        sum->data[i] = (int*)malloc(sum->cols * sizeof(int));
        if (sum->data[i] == NULL) {
            perror("Memory allocation error for sum row elements");
            for (int j = 0; j < i; j++) {
                free(sum->data[j]);
            }
            free(sum->data);
            free(sum);
            return NULL;
        }

        for (int j = 0; j < sum->cols; j++) {
            sum->data[i][j] = m1->data[i][j] + m2->data[i][j];
        }
    }

    return sum;
}

int main() {
    int num_matrices;
    printf("Enter the number of matrices in the array: ");
    if (scanf("%d", &num_matrices) != 1 || num_matrices <= 0) {
        printf("Invalid input for the number of matrices. Program terminated.\n");
        return 1;
    }

    Matrix** matrix_array = (Matrix**)calloc(num_matrices, sizeof(Matrix*));
    if (matrix_array == NULL) {
        perror("Memory allocation error for matrix array");
        return 1;
    }

    for (int i = 0; i < num_matrices; i++) {
        printf("\n--- Input of matrix #%d ---\n", i + 1);
        matrix_array[i] = createMatrix();
        if (matrix_array[i] == NULL) {
            printf("Error creating matrix #%d. Freeing memory.\n", i + 1);
            for (int j = 0; j < i; j++) {
                freeMatrix(matrix_array[j]);
            }
            free(matrix_array);
            return 1;
        }
    }

    printf("\n==================================\n");
    printf("Created array of matrices:\n");
    for (int i = 0; i < num_matrices; i++) {
        printf("Matrix #%d:\n", i + 1);
        printMatrix(matrix_array[i]);
    }
    printf("==================================\n");

    Matrix* total_sum = NULL;
    bool all_same_size = true;

    if (num_matrices > 0) {
        int ref_rows = matrix_array[0]->rows;
        int ref_cols = matrix_array[0]->cols;

        for (int i = 1; i < num_matrices; i++) {
            if (matrix_array[i]->rows != ref_rows || matrix_array[i]->cols != ref_cols) {
                all_same_size = false;
                break;
            }
        }

        if (all_same_size) {
            printf("\n✅ All matrices have the same size. Calculating the sum...\n");

            total_sum = (Matrix*)malloc(sizeof(Matrix));
            total_sum->rows = ref_rows;
            total_sum->cols = ref_cols;
            total_sum->data = (int**)malloc(ref_rows * sizeof(int*));

            for (int i = 0; i < ref_rows; i++) {
                total_sum->data[i] = (int*)calloc(ref_cols, sizeof(int));
            }

            for (int k = 0; k < num_matrices; k++) {
                for (int i = 0; i < ref_rows; i++) {
                    for (int j = 0; j < ref_cols; j++) {
                        total_sum->data[i][j] += matrix_array[k]->data[i][j];
                    }
                }
            }

            printf("\nTotal sum matrix:\n");
            printMatrix(total_sum);
        } else {
            printf("\n❌ Matrices have different sizes. Sum was not calculated.\n");
        }
    }

    printf("\n--- Freeing memory ---\n");

    if (total_sum != NULL) {
        freeMatrix(total_sum);
        printf("Memory for the total sum matrix has been freed.\n");
    }

    for (int i = 0; i < num_matrices; i++) {
        if (matrix_array[i] != NULL) {
            freeMatrix(matrix_array[i]);
            printf("Memory for matrix #%d has been freed.\n", i + 1);
        }
    }

    free(matrix_array);
    printf("Memory for the pointer array has been freed.\n");
    printf("Program terminated successfully.\n");

    return 0;
}
