#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NUMBERS 1000

typedef struct {
    int number;
    double top_left_x;
    double top_left_y;
    double bottom_right_x;
    double bottom_right_y;
    double area;
} Rectangle;

double calculate_area(const Rectangle *rect) {
    double width = fabs(rect->bottom_right_x - rect->top_left_x);
    double height = fabs(rect->top_left_y - rect->bottom_right_y);
    return width * height;
}

void print_double_file_content(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("File '%s' not found or is empty.\n", filename);
        return;
    }
    double number;
    int first_element = 1;
    printf("Content of file %s: ", filename);
    while (fread(&number, sizeof(double), 1, file) == 1) {
        if (!first_element) {
            printf(", ");
        }
        printf("%.2f", number);
        first_element = 0;
    }
    printf("\n");
    fclose(file);
}

void print_int_file_content(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("File '%s' not found or is empty.\n", filename);
        return;
    }
    int number;
    int first_element = 1;
    printf("Content of file %s: ", filename);
    while (fread(&number, sizeof(int), 1, file) == 1) {
        if (!first_element) {
            printf(", ");
        }
        printf("%d", number);
        first_element = 0;
    }
    printf("\n");
    fclose(file);
}

void print_rect_file_content(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("File '%s' not found or is empty.\n", filename);
        return;
    }
    Rectangle rect;
    int index = 0;
    printf("\n--- Rectangle File Content (%s) ---\n", filename);
    printf("Index | Number | x1,y1 | x2,y2 | Area\n");
    printf("--------------------------------------\n");

    while (fread(&rect, sizeof(Rectangle), 1, file) == 1) {
        printf("%5d | %5d | %.1f,%.1f | %.1f,%.1f | %.2f\n",
               index++, rect.number, rect.top_left_x, rect.top_left_y,
               rect.bottom_right_x, rect.bottom_right_y, rect.area);
    }
    printf("--------------------------------------\n");
    fclose(file);
}

void write_double_array_to_file(double *arr, int n, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }
    size_t written = fwrite(arr, sizeof(double), n, file);
    if (written != (size_t)n) {
        fprintf(stderr, "Write error: wrote %zu out of %d elements.\n", written, n);
    } else {
        printf("Array successfully written to binary file: %s\n", filename);
    }
    fclose(file);
}

void task1_execution() {
    int n;
    const char *filename = "reals_array_task1.bin";

    printf("\n--- EXECUTING TASK 1 ---\n");
    printf("Enter the length of the array of real numbers: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid array length.\n");
        return;
    }

    double *arr = (double *)malloc(n * sizeof(double));
    if (arr == NULL) {
        perror("Memory allocation error");
        return;
    }

    printf("Enter %d real numbers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        if (scanf("%lf", &arr[i]) != 1) {
            fprintf(stderr, "Error reading a real number. Skipping the rest of the elements.\n");
            free(arr);
            return;
        }
    }

    write_double_array_to_file(arr, n, filename);
    print_double_file_content(filename);

    free(arr);
}

void create_initial_file_f_task2(const char *filename) {
    double data[] = {1.5, -3.2, 0.8, 5.1, -1.1, 4.0, 0.1, -6.5};
    int n = sizeof(data) / sizeof(data[0]);

    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error creating initial file F");
        return;
    }
    fwrite(data, sizeof(double), n, file);
    fclose(file);
    printf("Initial file F created with test content.\n");
}

void filter_and_remove(const char *filename_f, const char *filename_g, double a) {
    const char *temp_filename = "temp_f_task2.bin";

    FILE *f_in = fopen(filename_f, "rb");
    if (f_in == NULL) {
        perror("Error opening file F");
        return;
    }

    FILE *g_out = fopen(filename_g, "wb");
    FILE *temp_f_out = fopen(temp_filename, "wb");

    if (g_out == NULL || temp_f_out == NULL) {
        perror("Error opening output files");
        if (g_out) fclose(g_out);
        if (temp_f_out) fclose(temp_f_out);
        fclose(f_in);
        return;
    }

    double number;
    int count_g = 0;

    while (fread(&number, sizeof(double), 1, f_in) == 1) {
        if (fabs(number) < a) {
            fwrite(&number, sizeof(double), 1, g_out);
            count_g++;
        } else {
            fwrite(&number, sizeof(double), 1, temp_f_out);
        }
    }

    fclose(f_in);
    fclose(g_out);
    fclose(temp_f_out);

    remove(filename_f);
    rename(temp_filename, filename_f);

    printf("File G successfully created. Number of elements: %d\n", count_g);
    printf("File F updated (elements less than |%.2f| removed).\n", a);
}

void task2_execution() {
    const char *filename_f = "file_f_task2.bin";
    const char *filename_g = "file_g_task2.bin";
    double a;

    printf("\n--- EXECUTING TASK 2 ---\n");
    create_initial_file_f_task2(filename_f);
    print_double_file_content(filename_f);

    printf("Enter number a (a > 0) for absolute value comparison: ");
    if (scanf("%lf", &a) != 1 || a <= 0) {
        fprintf(stderr, "Invalid value for a. Using a=2.0 for demonstration.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    filter_and_remove(filename_f, filename_g, a);

    printf("\n--- Checking results ---\n");
    printf("File F after removal: ");
    print_double_file_content(filename_f);
    printf("File G (filtered): ");
    print_double_file_content(filename_g);
}

bool is_even(int n) { return n % 2 == 0; }
bool is_power_of_3(int n) {
    if (n <= 0) return false;
    while (n > 1) {
        if (n % 3 != 0) return false;
        n /= 3;
    }
    return true;
}
bool is_perfect_square(int n) {
    if (n < 0) return false;
    long long root = round(sqrt(n));
    return (root * root == n);
}
bool is_prime_3(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}
bool has_three_divisors(int n) {
    if (n <= 0) return false;
    int root = (int)round(sqrt(n));
    if (root * root != n) return false;
    return is_prime_3(root);
}
bool is_palindrome(int n) {
    if (n < 0) return false;
    int original = n;
    int reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + (n % 10);
        n /= 10;
    }
    return original == reversed;
}
bool is_perfect_square_long(long long n) {
    if (n < 0) return false;
    long long root = round(sqrt(n));
    return (root * root == n);
}
bool is_fibonacci(int n) {
    if (n < 0) return false;
    if (n == 0 || n == 1) return true;
    long long n_ll = n;
    long long check1 = 5 * n_ll * n_ll + 4;
    long long check2 = 5 * n_ll * n_ll - 4;
    return is_perfect_square_long(check1) || is_perfect_square_long(check2);
}

int create_file_f_task3(const char *filename_f) {
    FILE *file_f = fopen(filename_f, "wb");
    if (file_f == NULL) {
        perror("Error opening file F");
        return 0;
    }

    int n;
    int count = 0;
    printf("Enter integers (0 to finish):\n");

    while (1) {
        printf("Enter number: ");
        if (scanf("%d", &n) != 1) {
            fprintf(stderr, "Input error. Please enter an integer.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (n == 0) break;
        fwrite(&n, sizeof(int), 1, file_f);
        count++;

        if (count >= MAX_NUMBERS) {
            printf("Number limit reached (%d). Stopping input.\n", MAX_NUMBERS);
            break;
        }
    }

    fclose(file_f);
    return count;
}

void build_file_g_task3(const char *filename_f, const char *filename_g, const char *type_name, bool (*condition)(int)) {
    FILE *f_in = fopen(filename_f, "rb");
    if (f_in == NULL) {
        perror("Error opening file F");
        return;
    }

    FILE *g_out = fopen(filename_g, "wb");
    if (g_out == NULL) {
        perror("Error opening file G");
        fclose(f_in);
        return;
    }

    int number;
    int count_g = 0;

    while (fread(&number, sizeof(int), 1, f_in) == 1) {
        if (condition(number)) {
            fwrite(&number, sizeof(int), 1, g_out);
            count_g++;
        }
    }

    fclose(f_in);
    fclose(g_out);
    printf("File G (%s) successfully created. Elements: %d\n", type_name, count_g);
}

void task3_execution() {
    const char *file_f_name = "ints_f_task3.bin";

    printf("\n--- EXECUTING TASK 3 ---\n");
    if (create_file_f_task3(file_f_name) == 0) {
        fprintf(stderr, "Failed to create file F or 0 elements entered.\n");
        return;
    }
    printf("File F (original): ");
    print_int_file_content(file_f_name);
    printf("----------------------------------------\n");

    build_file_g_task3(file_f_name, "ints_g_even.bin", "even numbers", is_even);
    print_int_file_content("ints_g_even.bin");

    build_file_g_task3(file_f_name, "ints_g_pow3.bin", "powers of 3", is_power_of_3);
    print_int_file_content("ints_g_pow3.bin");

    build_file_g_task3(file_f_name, "ints_g_square.bin", "perfect squares", is_perfect_square);
    print_int_file_content("ints_g_square.bin");

    build_file_g_task3(file_f_name, "ints_g_3div.bin", "3 divisors", has_three_divisors);
    print_int_file_content("ints_g_3div.bin");

    build_file_g_task3(file_f_name, "ints_g_pal.bin", "palindromes", is_palindrome);
    print_int_file_content("ints_g_pal.bin");

    build_file_g_task3(file_f_name, "ints_g_fib.bin", "Fibonacci", is_fibonacci);
    print_int_file_content("ints_g_fib.bin");
}

void initialize_rect_file(const char *filename) {
    Rectangle rects[] = {
        {101, 0.0, 10.0, 5.0, 0.0, 0.0},
        {202, 1.0, 1.0, 2.0, 0.0, 0.0},
        {303, 0.0, 5.0, 10.0, 0.0, 0.0}
    };
    int n = sizeof(rects) / sizeof(rects[0]);

    for (int i = 0; i < n; i++) {
        rects[i].area = calculate_area(&rects[i]);
    }

    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error initializing rectangle file");
        return;
    }

    fwrite(rects, sizeof(Rectangle), n, file);
    fclose(file);
    printf("Rectangle file '%s' initialized.\n", filename);
}

void find_largest_rectangle(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for search");
        return;
    }

    Rectangle current_rect;
    double max_area = -1.0;
    int max_number = -1;

    while (fread(&current_rect, sizeof(Rectangle), 1, file) == 1) {
        if (current_rect.area > max_area) {
            max_area = current_rect.area;
            max_number = current_rect.number;
        }
    }

    fclose(file);

    if (max_number != -1) {
        printf("\n--- Search Result ---\n");
        printf("Rectangle with the largest area:\n");
        printf("Number: %d\n", max_number);
        printf("Area: %.2f\n", max_area);
        printf("");
    } else {
        printf("File is empty or a reading error occurred.\n");
    }
}

void delete_rectangle_by_number(const char *filename, int number_to_delete) {
    const char *temp_filename = "temp_rects_task4.bin";

    FILE *f_in = fopen(filename, "rb");
    if (f_in == NULL) {
        perror("Error opening file for deletion");
        return;
    }

    FILE *f_out = fopen(temp_filename, "wb");
    if (f_out == NULL) {
        perror("Error opening temporary file");
        fclose(f_in);
        return;
    }

    Rectangle current_rect;
    int deleted_count = 0;

    while (fread(&current_rect, sizeof(Rectangle), 1, f_in) == 1) {
        if (current_rect.number != number_to_delete) {
            fwrite(&current_rect, sizeof(Rectangle), 1, f_out);
        } else {
            deleted_count++;
        }
    }

    fclose(f_in);
    fclose(f_out);

    if (deleted_count > 0) {
        remove(filename);
        rename(temp_filename, filename);
        printf("\nRemoved %d record(s) with number %d. File updated.\n", deleted_count, number_to_delete);
    } else {
        remove(temp_filename);
        printf("\nRectangle with number %d not found.\n", number_to_delete);
    }
}

void replace_rectangle_by_index(const char *filename, int index_to_replace) {
    FILE *file = fopen(filename, "r+b");
    if (file == NULL) {
        perror("Error opening file for replacement");
        return;
    }

    long offset = (long)index_to_replace * sizeof(Rectangle);

    if (fseek(file, offset, SEEK_SET) != 0) {
        fprintf(stderr, "Error: record #%d does not exist (index might be too large).\n", index_to_replace);
        fclose(file);
        return;
    }

    Rectangle new_rect;
    printf("\n--- Entering New Data for Replacement (Record #%d) ---\n", index_to_replace);

    printf("Enter the NEW Number: ");
    if (scanf("%d", &new_rect.number) != 1) { fclose(file); return; }
    while (getchar() != '\n');

    printf("Enter x1, y1 (top-left corner): ");
    if (scanf("%lf %lf", &new_rect.top_left_x, &new_rect.top_left_y) != 2) { fclose(file); return; }
    while (getchar() != '\n');

    printf("Enter x2, y2 (bottom-right corner): ");
    if (scanf("%lf %lf", &new_rect.bottom_right_x, &new_rect.bottom_right_y) != 2) { fclose(file); return; }
    while (getchar() != '\n');

    new_rect.area = calculate_area(&new_rect);

    if (fwrite(&new_rect, sizeof(Rectangle), 1, file) == 1) {
        printf("Record #%d successfully replaced. Number: %d, Area: %.2f\n", index_to_replace, new_rect.number, new_rect.area);
    } else {
        fprintf(stderr, "Error writing new rectangle.\n");
    }

    fclose(file);
}

void task4_execution() {
    const char *filename = "rectangles_task4.bin";
    int choice;
    int temp_num;

    printf("\n--- EXECUTING TASK 4 ---\n");
    initialize_rect_file(filename);
    print_rect_file_content(filename);

    do {
        printf("\nSelect action:\n");
        printf("1. Find rectangle with the largest area\n");
        printf("2. Replace record by sequential INDEX\n");
        printf("3. Delete record by rectangle NUMBER\n");
        printf("4. Show current file content\n");
        printf("0. Return to main menu\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                find_largest_rectangle(filename);
                break;
            case 2:
                printf("Enter the sequential INDEX (starting from 0) to replace: ");
                if (scanf("%d", &temp_num) == 1) {
                    while (getchar() != '\n');
                    replace_rectangle_by_index(filename, temp_num);
                }
                break;
            case 3:
                printf("Enter the rectangle NUMBER to delete: ");
                if (scanf("%d", &temp_num) == 1) {
                    while (getchar() != '\n');
                    delete_rectangle_by_number(filename, temp_num);
                }
                break;
            case 4:
                print_rect_file_content(filename);
                break;
            case 0:
                printf("Returning to main menu.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);
}

int main() {
    int choice;

    do {
        printf("\n====================================\n");
        printf(" 📂 C BINARY FILE OPERATIONS \n");
        printf("====================================\n");
        printf("Select a task to execute:\n");
        printf("1. Task 1: Write/Print array of real numbers.\n");
        printf("2. Task 2: Filter/Remove real numbers by absolute value.\n");
        printf("3. Task 3: Filter integers based on various conditions.\n");
        printf("4. Task 4: Operations with rectangle structures.\n");
        printf("0. Exit\n");
        printf("Your choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
            continue;
        }

        while (getchar() != '\n');

        switch (choice) {
            case 1:
                task1_execution();
                break;
            case 2:
                task2_execution();
                break;
            case 3:
                task3_execution();
                break;
            case 4:
                task4_execution();
                break;
            case 0:
                printf("Exiting. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number from 0 to 4.\n");
        }
    } while (choice != 0);

    return 0;
}