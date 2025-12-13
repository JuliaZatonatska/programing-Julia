#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define FILENAME_F "F_array.bin"
#define FILENAME_G "G_filtered.bin"
#define MAX_ELEMENTS 100

typedef struct {
    double sum;
    int negative_count;
    double last_component;
    double prev_last_component;
    double max_abs;
    double min_even_index;
    int total_count;
    double global_min;
    double global_max;
} FileStats;

int write_array_to_file(const char *fileName, double arr[], int count);
int print_file_content(const char *fileName);
bool read_and_calculate_stats(FileStats *stats);
void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();
void task9();
void task10();
int main();

int write_array_to_file(const char *fileName, double arr[], int count) {
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        return -1;
    }

    fwrite(&count, sizeof(int), 1, file);
    fwrite(arr, sizeof(double), count, file);

    fclose(file);
    printf("Successfully wrote %d elements to file '%s'.\n", count, fileName);
    return 0;
}

int print_file_content(const char *fileName) {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        return -1;
    }

    int count = 0;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        fprintf(stderr, "Error reading element count from file %s\n", fileName);
        fclose(file);
        return -1;
    }

    printf("File '%s' content (%d elements): ", fileName, count);

    for (int i = 0; i < count; i++) {
        double value;
        if (fread(&value, sizeof(double), 1, file) != 1) {
            fprintf(stderr, "Error reading element #%d from file %s\n", i + 1, fileName);
            fclose(file);
            return -1;
        }

        printf("%.2f", value);
        if (i < count - 1) {
            printf(", ");
        }
    }
    printf("\n");

    fclose(file);
    return 0;
}

bool read_and_calculate_stats(FileStats *stats) {
    FILE *file = fopen(FILENAME_F, "rb");
    if (file == NULL) {
        perror("Error opening file F for reading stats. Run Task 1 first.");
        return false;
    }

    int count = 0;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        fprintf(stderr, "Error reading element count.\n");
        fclose(file);
        return false;
    }
    stats->total_count = count;

    stats->sum = 0.0;
    stats->negative_count = 0;
    stats->last_component = NAN;
    stats->prev_last_component = NAN;
    stats->max_abs = -1.0;
    stats->min_even_index = INFINITY;
    stats->global_min = INFINITY;
    stats->global_max = -INFINITY;

    double all_elements[MAX_ELEMENTS];
    int effective_count = (count > MAX_ELEMENTS) ? MAX_ELEMENTS : count;

    for (int i = 0; i < effective_count; i++) {
        double value;
        if (fread(&value, sizeof(double), 1, file) != 1) {
            fprintf(stderr, "Error reading element #%d.\n", i + 1);
            fclose(file);
            return false;
        }

        all_elements[i] = value;

        stats->sum += value;

        if (value < 0.0) {
            stats->negative_count++;
        }

        stats->prev_last_component = stats->last_component;
        stats->last_component = value;

        if (fabs(value) > stats->max_abs) {
            stats->max_abs = fabs(value);
        }

        if ((i % 2 == 0) && (value < stats->min_even_index)) {
            stats->min_even_index = value;
        }

        if (value < stats->global_min) {
            stats->global_min = value;
        }
        if (value > stats->global_max) {
            stats->global_max = value;
        }
    }

    fclose(file);

    if (effective_count > 0) {
        double average = stats->sum / effective_count;
        int less_than_avg_count = 0;
        for (int i = 0; i < effective_count; i++) {
            if (all_elements[i] < average) {
                less_than_avg_count++;
            }
        }
        printf("\nз) Count of elements less than Avg (%.2f): %d\n", average, less_than_avg_count);
    } else {
         printf("\nз) Cannot calculate average for empty file.\n");
    }

    if (effective_count >= 1) {
        double first = all_elements[0];
        double last = stats->last_component;
        printf("ж) Difference of first (%.2f) and last (%.2f) component: %.2f\n", first, last, first - last);
    } else {
        printf("ж) Cannot calculate difference for less than 1 element.\n");
    }

    return true;
}

void task1() {
    printf("\n--- Task 1: Write array to F_array.bin and print ---\n");
    int n;
    printf("Enter array length (max %d): ", MAX_ELEMENTS);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_ELEMENTS) {
        fprintf(stderr, "Invalid or too large length.\n");
        return;
    }

    double arr[MAX_ELEMENTS];
    printf("Enter %d double numbers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        if (scanf("%lf", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input. Aborting.\n");
            return;
        }
    }

    if (write_array_to_file(FILENAME_F, arr, n) == 0) {
        print_file_content(FILENAME_F);
    }
}

void task2() {
    printf("\n--- Task 2: Filter F to G (|x| < a) and modify F ---\n");
    double a;
    printf("Enter the positive threshold 'a': ");
    if (scanf("%lf", &a) != 1 || a <= 0) {
        fprintf(stderr, "Invalid or non-positive value for 'a'. Aborting.\n");
        return;
    }

    FILE *file_f_read = fopen(FILENAME_F, "rb");
    if (file_f_read == NULL) {
        perror("Error opening file F for reading. Run Task 1 first.");
        return;
    }

    FILE *file_g_write = fopen(FILENAME_G, "wb");
    if (file_g_write == NULL) {
        perror("Error opening file G for writing");
        fclose(file_f_read);
        return;
    }

    int count_f = 0;
    if (fread(&count_f, sizeof(int), 1, file_f_read) != 1) {
        fprintf(stderr, "Error reading count from F.\n");
        fclose(file_f_read);
        fclose(file_g_write);
        return;
    }

    double arr_f_new[MAX_ELEMENTS];
    double arr_g_new[MAX_ELEMENTS];
    int count_f_new = 0;
    int count_g_new = 0;
    int effective_count = (count_f > MAX_ELEMENTS) ? MAX_ELEMENTS : count_f;

    for (int i = 0; i < effective_count; i++) {
        double value;
        if (fread(&value, sizeof(double), 1, file_f_read) != 1) {
            fprintf(stderr, "Error reading element %d from F. Breaking.\n", i);
            break;
        }

        if (fabs(value) < a) {
            if (count_g_new < MAX_ELEMENTS) {
                arr_g_new[count_g_new++] = value;
            } else {
                fprintf(stderr, "Warning: G array capacity reached. Skipping element.\n");
            }
        } else {
            if (count_f_new < MAX_ELEMENTS) {
                arr_f_new[count_f_new++] = value;
            } else {
                fprintf(stderr, "Warning: F array capacity reached. Skipping element.\n");
            }
        }
    }

    if (count_f > MAX_ELEMENTS) {
        double dummy;
        for (int i = MAX_ELEMENTS; i < count_f; i++) {
            fread(&dummy, sizeof(double), 1, file_f_read);
        }
    }

    fclose(file_f_read);

    fwrite(&count_g_new, sizeof(int), 1, file_g_write);
    fwrite(arr_g_new, sizeof(double), count_g_new, file_g_write);
    fclose(file_g_write);
    printf("Created file G (%s) with %d elements (where |x| < %.2f).\n", FILENAME_G, count_g_new, a);

    FILE *file_f_write = fopen(FILENAME_F, "wb");
    if (file_f_write == NULL) {
        perror("Error opening file F for rewriting");
        return;
    }
    fwrite(&count_f_new, sizeof(int), 1, file_f_write);
    fwrite(arr_f_new, sizeof(double), count_f_new, file_f_write);
    fclose(file_f_write);
    printf("Modified file F (%s): %d elements remaining (where |x| >= %.2f).\n", FILENAME_F, count_f_new, a);

    print_file_content(FILENAME_G);
    print_file_content(FILENAME_F);
}

void task7() {
    printf("\n--- Task 7: Calculation of all file properties ---\n");
    FileStats stats;

    if (!read_and_calculate_stats(&stats)) {
        printf("Could not complete Task 7 due to file error.\n");
        return;
    }

    printf("\nResults for File %s (%d elements):\n", FILENAME_F, stats.total_count);

    printf("а) Sum of components: %.2f\n", stats.sum);
    printf("б) Count of negative components: %d\n", stats.negative_count);

    if (stats.total_count >= 1) {
        printf("в) Last component: %.2f\n", stats.last_component);
    } else {
        printf("в) Last component: N/A\n");
    }

    if (stats.total_count >= 2) {
        printf("г) Second to last component: %.2f\n", stats.prev_last_component);
    } else {
        printf("г) Second to last component: N/A\n");
    }

    if (stats.total_count > 0) {
        printf("д) Largest component by absolute value: %.2f\n", stats.max_abs);
    } else {
        printf("д) Largest component by absolute value: N/A\n");
    }

    if (stats.min_even_index != INFINITY) {
        printf("е) Smallest component with even index: %.2f\n", stats.min_even_index);
    } else {
        printf("е) Smallest component with even index: N/A\n");
    }

    if (stats.total_count > 0) {
        printf("є) Sum of largest (%.2f) and smallest (%.2f) component: %.2f\n",
               stats.global_max, stats.global_min, stats.global_max + stats.global_min);
    } else {
        printf("є) Sum of largest and smallest: N/A\n");
    }
}

void task3() { printf("Task 3 is not yet implemented.\n"); }
void task4() { printf("Task 4 is not yet implemented.\n"); }
void task5() { printf("Task 5 is not yet implemented.\n"); }
void task6() { printf("Task 6 is not yet implemented.\n"); }
void task8() { printf("Task 8 is not yet implemented.\n"); }
void task9() { printf("Task 9 is not yet implemented.\n"); }
void task10() { printf("Task 10 is not yet implemented.\n"); }

int main() {
    int choice;

    while (1) {
        printf("\n-----------------------------------------------\n");
        printf("Available tasks:\n");
        printf("1 - Task 1 (Write array to F_array.bin and print)\n");
        printf("2 - Task 2 (Filter F to G and modify F)\n");
        printf("7 - Task 7 (Calculate all properties of F)\n");
        printf("0 - Exit\n");
        printf("-----------------------------------------------\n");
        printf("Choose task (0 to exit): ");

        if (scanf("%d", &choice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            fprintf(stderr, "Invalid input. Please enter a number.\n");
            continue;
        }

        if (choice == 0) break;

        switch(choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            case 6: task6(); break;
            case 7: task7(); break;
            case 8: task8(); break;
            case 9: task9(); break;
            case 10: task10(); break;
            default: printf("No such task implemented yet.\n");
        }
    }
    printf("Exiting program.\n");
    return 0;
}
