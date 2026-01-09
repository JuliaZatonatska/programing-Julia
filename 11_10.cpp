#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <io.h>
#define TRUNCATE_FUNC _chsize
#else
#include <unistd.h>
#define TRUNCATE_FUNC ftruncate
#endif

typedef struct TPair {
    unsigned key;
    char data[10];
} TPair;

#define FILENAME "datafile.bin"
#define RECORD_SIZE sizeof(TPair)

void check_file(FILE *f) {
    if (f == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
}

long get_file_size_records(FILE *f) {
    long current_pos = ftell(f);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, current_pos, SEEK_SET);

    if (size % RECORD_SIZE != 0) {
        fprintf(stderr, "Warning: File size is not a multiple of record size.\n");
    }

    return size / RECORD_SIZE;
}

void print_file_content(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        printf("File '%s' not found or is empty.\n", filename);
        return;
    }

    TPair record;
    long count = 0;
    printf("\n--- Content of file '%s' ---\n", filename);
    while (fread(&record, RECORD_SIZE, 1, f) == 1) {
        printf("Record %ld: Key = %u, Data = '%s'\n", count, record.key, record.data);
        count++;
    }
    printf("--- End of Content (%ld records) ---\n", count);

    fclose(f);
}

int find_record_ordered(const char *filename, unsigned key, long *position) {
    FILE *f = fopen(filename, "rb");
    check_file(f);

    long low = 0;
    long high = get_file_size_records(f) - 1;
    long mid;
    TPair record;
    int found = 0;

    *position = -1;

    while (low <= high) {
        mid = low + (high - low) / 2;

        fseek(f, mid * RECORD_SIZE, SEEK_SET);

        if (fread(&record, RECORD_SIZE, 1, f) != 1) {
             fprintf(stderr, "Error reading record at position %ld\n", mid);
             break;
        }

        if (record.key == key) {
            *position = mid;
            found = 1;
            break;
        } else if (record.key < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    fclose(f);

    if (found) {
        printf("✅ Ordered Search: Key %u found at position (index) %ld.\n", key, *position);
    } else {
        printf("❌ Ordered Search: Key %u not found.\n", key);
    }

    return found;
}

int delete_record_ordered(const char *filename, unsigned key) {
    FILE *f = fopen(filename, "r+b");
    check_file(f);

    long pos_to_delete = -1;
    long file_size = get_file_size_records(f);
    TPair current_record;
    int found = 0;

    fseek(f, 0, SEEK_SET);
    for (long i = 0; i < file_size; i++) {
        if (fread(&current_record, RECORD_SIZE, 1, f) != 1) {
            fprintf(stderr, "Error reading record during linear search at %ld\n", i);
            break;
        }

        if (current_record.key == key) {
            pos_to_delete = i;
            found = 1;
            break;
        }

        fseek(f, (i + 1) * RECORD_SIZE, SEEK_SET);
    }
    fseek(f, 0, SEEK_SET);

    if (!found) {
        printf("❌ Ordered Deletion: Key %u not found.\n", key);
        fclose(f);
        return 0;
    }

    printf("✅ Ordered Deletion: Key %u found at position %ld. Starting shift.\n", key, pos_to_delete);

    for (long i = pos_to_delete; i < file_size - 1; i++) {
        fseek(f, (i + 1) * RECORD_SIZE, SEEK_SET);
        if (fread(&current_record, RECORD_SIZE, 1, f) != 1) {
            fprintf(stderr, "Error reading record at position %ld during shift.\n", i + 1);
            break;
        }

        fseek(f, i * RECORD_SIZE, SEEK_SET);
        if (fwrite(&current_record, RECORD_SIZE, 1, f) != 1) {
            perror("Error writing record during shift");
            break;
        }
    }

    if (TRUNCATE_FUNC(fileno(f), (file_size - 1) * RECORD_SIZE) == -1) {
        perror("Error truncating file (TRUNCATE_FUNC)");
    }


    fclose(f);
    return 1;
}

int delete_record_unordered(const char *filename, unsigned key) {
    FILE *f = fopen(filename, "r+b");
    check_file(f);

    long pos_to_delete = -1;
    long file_size = get_file_size_records(f);
    TPair current_record;
    int found = 0;

    fseek(f, 0, SEEK_SET);
    for (long i = 0; i < file_size; i++) {
        if (fread(&current_record, RECORD_SIZE, 1, f) != 1) {
            fprintf(stderr, "Error reading record during linear search at %ld\n", i);
            break;
        }

        if (current_record.key == key) {
            pos_to_delete = i;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("❌ Unordered Deletion: Key %u not found.\n", key);
        fclose(f);
        return 0;
    }

    long last_pos = file_size - 1;
    if (pos_to_delete == last_pos) {
        if (TRUNCATE_FUNC(fileno(f), last_pos * RECORD_SIZE) == -1) {
            perror("Error truncating file (TRUNCATE_FUNC) for last record");
        }
        printf("✅ Unordered Deletion: Key %u deleted (was the last record).\n", key);
        fclose(f);
        return 1;
    }

    fseek(f, last_pos * RECORD_SIZE, SEEK_SET);
    TPair last_record;
    if (fread(&last_record, RECORD_SIZE, 1, f) != 1) {
        fprintf(stderr, "Error reading last record at position %ld\n", last_pos);
        fclose(f);
        return 0;
    }

    fseek(f, pos_to_delete * RECORD_SIZE, SEEK_SET);
    if (fwrite(&last_record, RECORD_SIZE, 1, f) != 1) {
        perror("Error writing last record to deleted position");
        fclose(f);
        return 0;
    }

    if (TRUNCATE_FUNC(fileno(f), last_pos * RECORD_SIZE) == -1) {
        perror("Error truncating file (TRUNCATE_FUNC)");
    }

    printf("✅ Unordered Deletion: Key %u deleted at position %ld, replaced by the last record.\n", key, pos_to_delete);

    fclose(f);
    return 1;
}

void create_ordered_file(const char *filename) {
    FILE *f = fopen(filename, "wb");
    check_file(f);

    TPair records[] = {
        {10, "DataA"},
        {20, "DataB"},
        {30, "DataC"},
        {40, "DataD"},
        {50, "DataE"}
    };
    int num_records = sizeof(records) / RECORD_SIZE;

    if (fwrite(records, RECORD_SIZE, num_records, f) != num_records) {
        perror("Error writing to file");
    } else {
        printf("\nCreated ordered file '%s' with %d records.\n", filename, num_records);
    }

    fclose(f);
}

void create_unordered_file(const char *filename) {
    FILE *f = fopen(filename, "wb");
    check_file(f);

    TPair records[] = {
        {45, "UnordA"},
        {12, "UnordB"},
        {78, "UnordC"},
        {22, "UnordD"},
        {90, "UnordE"}
    };
    int num_records = sizeof(records) / RECORD_SIZE;

    if (fwrite(records, RECORD_SIZE, num_records, f) != num_records) {
        perror("Error writing to file");
    } else {
        printf("Created unordered file '%s' with %d records.\n", filename, num_records);
    }

    fclose(f);
}

int main() {

    const char *ordered_file = "ordered.bin";

    create_ordered_file(ordered_file);
    print_file_content(ordered_file);

    long found_pos;
    find_record_ordered(ordered_file, 30, &found_pos);
    find_record_ordered(ordered_file, 77, &found_pos);

    printf("\n--- Ordered File Deletion Scenario ---\n");
    delete_record_ordered(ordered_file, 30);
    print_file_content(ordered_file);
    delete_record_ordered(ordered_file, 10);
    print_file_content(ordered_file);
    delete_record_ordered(ordered_file, 50);
    print_file_content(ordered_file);

    const char *unordered_file = "unordered.bin";

    create_unordered_file(unordered_file);
    print_file_content(unordered_file);

    printf("\n--- Unordered File Deletion Scenario ---\n");
    delete_record_unordered(unordered_file, 78);
    print_file_content(unordered_file);
    delete_record_unordered(unordered_file, 45);
    print_file_content(unordered_file);
    delete_record_unordered(unordered_file, 90);
    print_file_content(unordered_file);

    return 0;
}