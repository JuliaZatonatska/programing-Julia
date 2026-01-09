#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int read_natural_number() {
    int n = 0;
    printf("Enter a positive integer N: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Input error. N must be a positive integer.\n");
        clear_input_buffer();
        return 0;
    }
    clear_input_buffer();
    return n;
}

long double* allocate_ld_array(int n) {
    long double* array = (long double*)malloc(n * sizeof(long double));
    if (array == NULL) {
        perror("Memory allocation error (malloc)");
        return NULL;
    }
    return array;
}

void read_ld_array_values(long double* array, int n) {
    int i;
    printf("Enter %d real numbers:\n", n);
    for (i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        if (scanf("%Lf", &array[i]) != 1) {
            printf("Input error. Please enter a real number.\n");
            clear_input_buffer();
            i--;
        }
    }
    clear_input_buffer();
}

long double calculate_sum_of_squares(const long double* array, int n) {
    long double sum = 0.0L;
    int i;
    for (i = 0; i < n; i++) {
        long double square = array[i] * array[i];
        sum = sum + square;
    }
    return sum;
}

void task1() {
    int n;
    long double* array = NULL;
    long double sum_of_squares;

    printf("\n--- Task 1: Sum of squares of real numbers ---\n");

    n = read_natural_number();
    if (n == 0) return;

    array = allocate_ld_array(n);
    if (array == NULL) {
        return;
    }

    read_ld_array_values(array, n);

    sum_of_squares = calculate_sum_of_squares(array, n);

    printf("\nNumber of elements N: %d\n", n);
    printf("Sum of squares of array elements: %Lf\n", sum_of_squares);

    free(array);
    printf("Memory freed.\n");
}

#define MAX_ELEMENTS_T2 100

int is_perfect_square(int num) {
    if (num < 0) {
        return 0;
    }
    int root = (int)round(sqrt((double)num));
    return (root * root == num);
}

int is_perfect_cube(int num) {
    long long abs_num = (long long)llabs(num);
    long long root = (long long)round(cbrt((double)abs_num));

    if (root * root * root == abs_num) {
        return 1;
    } else {
        return 0;
    }
}

int read_int_array_until_zero(int** array_ptr, int max_size) {
    int count = 0;
    int input_val;
    int* temp_array = NULL;

    printf("Enter integers (max %d), 0 to finish input:\n", max_size);

    while (count < max_size) {
        printf("Element %d: ", count + 1);
        if (scanf("%d", &input_val) != 1) {
            printf("Input error. Please enter an integer.\n");
            clear_input_buffer();
            continue;
        }

        if (input_val == 0) {
            break;
        }

        int* new_array = (int*)realloc(temp_array, (count + 1) * sizeof(int));

        if (new_array == NULL) {
            printf("Realloc error. Input terminated.\n");
            free(temp_array);
            clear_input_buffer();
            *array_ptr = NULL;
            return 0;
        }

        temp_array = new_array;
        temp_array[count] = input_val;
        count++;
    }

    clear_input_buffer();
    *array_ptr = temp_array;

    if (count == max_size) {
        printf("Maximum number of elements (%d) reached.\n", max_size);
    }

    return count;
}

void task2() {
    int* array = NULL;
    int n;
    int i;
    int perfect_squares_count = 0;
    int perfect_cubes_count = 0;

    printf("\n--- Task 2: Counting perfect squares and cubes ---\n");

    n = read_int_array_until_zero(&array, MAX_ELEMENTS_T2);

    if (n == 0) {
        printf("Array is empty or memory allocation failed.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        int current_num = array[i];

        if (is_perfect_square(current_num)) {
            perfect_squares_count++;
        }

        if (is_perfect_cube(current_num)) {
            perfect_cubes_count++;
        }
    }

    printf("\nActual number of array elements: %d\n", n);
    printf("Number of perfect squares: %d\n", perfect_squares_count);
    printf("Number of perfect cubes: %d\n", perfect_cubes_count);

    free(array);
    printf("Memory freed.\n");
}

long double* allocate_vector(int n) {
    long double* vector = (long double*)malloc(n * sizeof(long double));
    if (vector == NULL) {
        perror("Memory allocation error for vector (malloc)");
        return NULL;
    }
    return vector;
}

void free_vector(long double* vector) {
    if (vector != NULL) {
        free(vector);
    }
}

void read_vector_values(long double* vector, int n) {
    int i;
    printf("Enter %d real values for the vector:\n", n);
    for (i = 0; i < n; i++) {
        printf("Coordinate %d: ", i + 1);
        if (scanf("%Lf", &vector[i]) != 1) {
            printf("Input error. Please enter a real number.\n");
            clear_input_buffer();
            i--;
        }
    }
    clear_input_buffer();
}

long double* calculate_vector_difference(const long double* v1, int n1, const long double* v2, int n2) {
    if (n1 != n2) {
        printf("Cannot calculate difference: vector dimensions do not match (%d != %d).\n", n1, n2);
        return NULL;
    }

    long double* v_res = allocate_vector(n1);
    if (v_res == NULL) {
        return NULL;
    }

    int i;
    for (i = 0; i < n1; i++) {
        v_res[i] = v1[i] - v2[i];
    }

    return v_res;
}

void print_vector(const long double* vector, int n) {
    int i;
    printf("(");
    for (i = 0; i < n; i++) {
        printf("%.2Lf", vector[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

void task3() {
    int n1, n2;
    long double* v1 = NULL;
    long double* v2 = NULL;
    long double* v_diff = NULL;

    printf("\n--- Task 3: Difference of n-dimensional vectors ---\n");

    printf("--- Vector 1 ---\n");
    n1 = read_natural_number();
    if (n1 == 0) goto cleanup;
    v1 = allocate_vector(n1);
    if (v1 == NULL) goto cleanup;
    read_vector_values(v1, n1);

    printf("--- Vector 2 ---\n");
    n2 = read_natural_number();
    if (n2 == 0) goto cleanup;
    v2 = allocate_vector(n2);
    if (v2 == NULL) goto cleanup;
    read_vector_values(v2, n2);

    v_diff = calculate_vector_difference(v1, n1, v2, n2);

    printf("\nVector 1 (N=%d): ", n1);
    print_vector(v1, n1);
    printf("Vector 2 (N=%d): ", n2);
    print_vector(v2, n2);

    if (v_diff != NULL) {
        printf("Difference V1 - V2: ");
        print_vector(v_diff, n1);
    } else {
        printf("Difference was not calculated due to dimension mismatch.\n");
    }

cleanup:
    free_vector(v1);
    free_vector(v2);
    free_vector(v_diff);
    printf("Memory freed.\n");
}

typedef struct {
    long double* data;
    int rows;
    int cols;
} Matrix;

long double* allocate_matrix_data(int rows, int cols) {
    long double* data = (long double*)malloc(rows * cols * sizeof(long double));
    if (data == NULL) {
        perror("Memory allocation error for matrix (malloc)");
    }
    return data;
}

void free_matrix_data(Matrix* m) {
    if (m != NULL && m->data != NULL) {
        free(m->data);
        m->data = NULL;
    }
}

Matrix read_single_matrix() {
    Matrix m = {NULL, 0, 0};
    int i, j;
    int rows, cols;

    printf("Enter number of rows (M): ");
    if (scanf("%d", &rows) != 1 || rows <= 0) {
        printf("Input error M.\n");
        clear_input_buffer();
        return m;
    }

    printf("Enter number of columns (N): ");
    if (scanf("%d", &cols) != 1 || cols <= 0) {
        printf("Input error N.\n");
        clear_input_buffer();
        return m;
    }
    clear_input_buffer();

    m.rows = rows;
    m.cols = cols;
    m.data = allocate_matrix_data(rows, cols);

    if (m.data == NULL) {
        return m;
    }

    printf("Enter %d x %d matrix elements:\n", rows, cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            if (scanf("%Lf", &m.data[i * cols + j]) != 1) {
                printf("Input error. Please enter a real number.\n");
                clear_input_buffer();
                j--;
            }
        }
    }
    clear_input_buffer();
    return m;
}

Matrix calculate_matrix_array_sum(const Matrix* matrices, int count) {
    Matrix sum_matrix = {NULL, 0, 0};
    int i, r, c;

    if (count == 0) {
        return sum_matrix;
    }

    int R = matrices[0].rows;
    int C = matrices[0].cols;

    for (i = 1; i < count; i++) {
        if (matrices[i].rows != R || matrices[i].cols != C) {
            printf("Sum impossible: matrices have different dimensions.\n");
            return sum_matrix;
        }
    }

    sum_matrix.rows = R;
    sum_matrix.cols = C;
    sum_matrix.data = allocate_matrix_data(R, C);
    if (sum_matrix.data == NULL) {
        return sum_matrix;
    }

    for (r = 0; r < R * C; r++) {
        sum_matrix.data[r] = 0.0L;
    }

    for (i = 0; i < count; i++) {
        for (r = 0; r < R; r++) {
            for (c = 0; c < C; c++) {
                int index = r * C + c;
                sum_matrix.data[index] += matrices[i].data[index];
            }
        }
    }

    return sum_matrix;
}

void print_matrix(const Matrix* m, const char* name) {
    int r, c;
    printf("\n%s (%d x %d):\n", name, m->rows, m->cols);
    for (r = 0; r < m->rows; r++) {
        printf("|");
        for (c = 0; c < m->cols; c++) {
            int index = r * m->cols + c;
            printf(" %8.2Lf ", m->data[index]);
        }
        printf("|\n");
    }
}

void task6() {
    Matrix* matrix_array = NULL;
    Matrix sum_matrix = {NULL, 0, 0};
    int num_matrices;
    int i;

    printf("\n--- Task 6: Sum of array of matrices ---\n");

    printf("Enter the number of matrices in the array: ");
    if (scanf("%d", &num_matrices) != 1 || num_matrices <= 0) {
        printf("Input error. Count must be a positive integer.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    matrix_array = (Matrix*)malloc(num_matrices * sizeof(Matrix));
    if (matrix_array == NULL) {
        perror("Memory allocation error for array of structures (malloc)");
        return;
    }

    for (i = 0; i < num_matrices; i++) {
        printf("\n--- Matrix %d ---\n", i + 1);
        matrix_array[i] = read_single_matrix();

        if (matrix_array[i].data == NULL && (matrix_array[i].rows != 0 || matrix_array[i].cols != 0)) {
            printf("Memory allocation error for matrix %d. Aborting.\n", i + 1);
            goto cleanup;
        }
    }

    sum_matrix = calculate_matrix_array_sum(matrix_array, num_matrices);

    if (sum_matrix.data != NULL) {
        print_matrix(&sum_matrix, "Sum Matrix");
    } else {
        printf("\nSum was not calculated.\n");
    }

cleanup:
    for (i = 0; i < num_matrices; i++) {
        free_matrix_data(&matrix_array[i]);
    }
    if (matrix_array != NULL) {
        free(matrix_array);
    }
    free_matrix_data(&sum_matrix);
    printf("Memory freed.\n");
}

int is_power_of_base(unsigned long long num, int base) {
    if (num <= 0) {
        return 0;
    }
    if (num == 1) {
        return 1;
    }

    unsigned long long current = num;
    while (current % base == 0) {
        current = current / base;
    }

    return (current == 1);
}

unsigned long long* read_ull_array_values(int n) {
    unsigned long long* array = (unsigned long long*)malloc(n * sizeof(unsigned long long));
    int i;

    if (array == NULL) {
        perror("Memory allocation error for long long array (malloc)");
        return NULL;
    }

    printf("Enter %d positive long integers:\n", n);
    for (i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        if (scanf("%llu", &array[i]) != 1) {
            printf("Input error. Enter a positive long integer.\n");
            clear_input_buffer();
            i--;
        }
        else if (array[i] == 0) {
             printf("Number must be positive (> 0).\n");
             i--;
        }
    }
    clear_input_buffer();
    return array;
}

void task7() {
    int n;
    unsigned long long* array = NULL;
    int i;
    int powers_of_2_count = 0;
    int powers_of_3_count = 0;

    printf("\n--- Task 7: Counting powers of two and three ---\n");

    n = read_natural_number();
    if (n == 0) return;

    array = read_ull_array_values(n);
    if (array == NULL) {
        return;
    }

    for (i = 0; i < n; i++) {
        unsigned long long current_num = array[i];

        if (is_power_of_base(current_num, 2)) {
            powers_of_2_count++;
        }

        if (is_power_of_base(current_num, 3)) {
            powers_of_3_count++;
        }
    }

    printf("\nNumber of elements N: %d\n", n);
    printf("Count of numbers that are powers of 2: %d\n", powers_of_2_count);
    printf("Count of numbers that are powers of 3: %d\n", powers_of_3_count);

    free(array);
    printf("Memory freed.\n");
}

typedef struct {
    long double* data;
    int count;
    int capacity;
} CumulativeData;

static CumulativeData cd = {NULL, 0, 0};

void clear_cumulative_data() {
    if (cd.data != NULL) {
        free(cd.data);
        cd.data = NULL;
    }
    cd.count = 0;
    cd.capacity = 0;
    printf("Cumulative data cleared and memory freed.\n");
}

int add_data_to_cumulative(const long double* new_data, int new_count) {
    int required_capacity = cd.count + new_count;
    long double* new_block;
    int i;

    if (required_capacity > cd.capacity) {
        int new_capacity = (cd.capacity == 0) ? required_capacity : cd.capacity * 2;
        if (new_capacity < required_capacity) new_capacity = required_capacity;

        new_block = (long double*)realloc(cd.data, new_capacity * sizeof(long double));

        if (new_block == NULL) {
            perror("Realloc error for cumulative data");
            return 0;
        }

        cd.data = new_block;
        cd.capacity = new_capacity;
    }

    for (i = 0; i < new_count; i++) {
        cd.data[cd.count + i] = new_data[i];
    }

    cd.count = cd.count + new_count;
    return 1;
}

long double calculate_mean(const long double* data, int count) {
    long double sum = 0.0L;
    int i;
    if (count == 0) return 0.0L;

    for (i = 0; i < count; i++) {
        sum = sum + data[i];
    }

    return sum / count;
}

long double calculate_variance(const long double* data, int count, long double mean) {
    long double sum_of_squared_diffs = 0.0L;
    int i;
    if (count <= 1) return 0.0L;

    for (i = 0; i < count; i++) {
        long double diff = data[i] - mean;
        long double squared_diff = diff * diff;
        sum_of_squared_diffs = sum_of_squared_diffs + squared_diff;
    }

    return sum_of_squared_diffs / (count - 1);
}

void task8() {
    int n;
    long double* current_vector = NULL;
    long double mean, variance;

    printf("\n--- Task 8: Cumulative Arithmetic Mean and Variance ---\n");
    printf("Current number of accumulated values: %d\n", cd.count);

    printf("Enter the size of the new vector (0 to clear memory): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Input error N.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (n == 0) {
        clear_cumulative_data();
        return;
    }

    current_vector = allocate_ld_array(n);
    if (current_vector == NULL) {
        return;
    }
    read_ld_array_values(current_vector, n);

    if (!add_data_to_cumulative(current_vector, n)) {
        free(current_vector);
        return;
    }

    mean = calculate_mean(cd.data, cd.count);
    variance = calculate_variance(cd.data, cd.count, mean);

    printf("\nEntered %d new values. Total accumulated count: %d\n", n, cd.count);
    printf("Cumulative Arithmetic Mean: %Lf\n", mean);
    printf("Cumulative Variance (Sample): %Lf\n", variance);

    free(current_vector);
}


int main() {
    int choice;
    int cleanup_needed = 0;

    printf("----------------------------------------------------\n");
    printf("Available Tasks (Numeration according to requirements):\n");
    printf("1. Sum of squares of real numbers.\n");
    printf("2. Counting perfect squares and cubes (input until 0).\n");
    printf("3. Difference of n-dimensional vectors.\n");
    printf("6. Sum of an array of matrices.\n");
    printf("7. Counting powers of two and three (long integers).\n");
    printf("8. Cumulative Arithmetic Mean and Variance.\n");
    printf("----------------------------------------------------\n");

    while (1) {
        printf("\nChoose task (1, 2, 3, 6, 7, 8, or 0 to exit):\nInput: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        if (choice == 8) cleanup_needed = 1;

        if (choice == 0) break;

        switch(choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 6: task6(); break;
            case 7: task7(); break;
            case 8: task8(); break;
            default:
                 printf("Invalid task number. Choose from 1, 2, 3, 6, 7, 8.\n");
        }
    }

    if (cleanup_needed && cd.data != NULL) {
        printf("\n--- Final Cleanup ---\n");
        clear_cumulative_data();
    }

    printf("\nProgram shutting down.\n");

    return 0;
}