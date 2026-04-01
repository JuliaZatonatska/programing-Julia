#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 100

void print_matrix(int n, int m, int matrix[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n, m;
    int matrix[MAX_SIZE][MAX_SIZE];

    printf("Enter the number of rows (n, up to %d): ", MAX_SIZE);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_SIZE) {
        printf("Error: Invalid value of n.\n");
        return 1;
    }

    printf("Enter the number of columns (m, up to %d): ", MAX_SIZE);
    if (scanf("%d", &m) != 1 || m <= 0 || m > MAX_SIZE) {
        printf("Error: Invalid value of m.\n");
        return 1;
    }

    printf("Enter the elements of the %d x %d matrix:\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("Error reading element.\n");
                return 1;
            }
        }
    }

    printf("\n--- Original Matrix ---\n");
    print_matrix(n, m, matrix);
    printf("----------------------\n");

    int min_val = INT_MAX;
    int max_val = INT_MIN;
    int col_min = -1;
    int col_max = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] < min_val) {
                min_val = matrix[i][j];
                col_min = j;
            }
            if (matrix[i][j] > max_val) {
                max_val = matrix[i][j];
                col_max = j;
            }
        }
    }

    if (col_min == -1 || col_max == -1) {
        printf("Error: Could not find min/max elements.\n");
        return 1;
    }

    printf("Minimum element: %d (in column %d)\n", min_val, col_min + 1);
    printf("Maximum element: %d (in column %d)\n", max_val, col_max + 1);

    if (col_min != col_max) {
        printf("Swapping columns %d and %d...\n", col_min + 1, col_max + 1);
        for (int i = 0; i < n; i++) {
            int temp = matrix[i][col_min];
            matrix[i][col_min] = matrix[i][col_max];
            matrix[i][col_max] = temp;
        }
        printf("\n--- Matrix After Swap ---\n");
        print_matrix(n, m, matrix);
        printf("------------------------\n");
    } else {
        printf("The minimum and maximum elements are in the same column (%d). No swap needed.\n", col_min + 1);
    }

    return 0;
}
