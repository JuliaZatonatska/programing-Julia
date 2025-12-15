#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PASSENGERS_FILE "passengers.bin"
#define LUGGAGE_FILE "luggage.bin"
#define MAX_NAME_LEN 50
#define LUGGAGE_COUNT 5
#define PASSENGER_COUNT 5

typedef struct {
    char lastName[MAX_NAME_LEN];
} Passenger;

typedef struct {
    int passengerID;
    int itemCount;
    double totalWeight;
} LuggageInfo;

void create_test_files();
void write_passengers_to_file();
void write_luggage_to_file();
void find_matching_passengers(double a);
double calculate_global_average_weight();
void get_passenger_name(int id, char *name_buffer);

int main() {
    double a;

    printf("--- Working with Binary Files in C ---\n");

    create_test_files();

    printf("Enter the maximum allowable difference 'a' (kg): ");
    if (scanf("%lf", &a) != 1 || a < 0) {
        printf("Invalid input for a.\n");
        return 1;
    }

    find_matching_passengers(a);

    return 0;
}

void create_test_files() {
    printf("Creating test files...\n");
    write_passengers_to_file();
    write_luggage_to_file();
    printf("Files created.\n");
}

void write_passengers_to_file() {
    FILE *fp = fopen(PASSENGERS_FILE, "wb");
    if (fp == NULL) {
        perror("Error opening passenger file for writing");
        exit(EXIT_FAILURE);
    }

    Passenger p[PASSENGER_COUNT] = {
        {"Kovalenko"},
        {"Shevchenko"},
        {"Melnyk"},
        {"Petrov"},
        {"Sydorov"}
    };

    fwrite(p, sizeof(Passenger), PASSENGER_COUNT, fp);
    fclose(fp);
}

void write_luggage_to_file() {
    FILE *fp = fopen(LUGGAGE_FILE, "wb");
    if (fp == NULL) {
        perror("Error opening luggage file for writing");
        exit(EXIT_FAILURE);
    }

    LuggageInfo l[LUGGAGE_COUNT] = {
        {1, 3, 15.0},
        {2, 1, 8.0},
        {3, 4, 10.0},
        {4, 2, 9.0},
        {5, 5, 20.0}
    };

    fwrite(l, sizeof(LuggageInfo), LUGGAGE_COUNT, fp);
    fclose(fp);
}

double calculate_global_average_weight() {
    FILE *fp = fopen(LUGGAGE_FILE, "rb");
    if (fp == NULL) {
        perror("Error opening luggage file for reading");
        exit(EXIT_FAILURE);
    }

    LuggageInfo current_luggage;
    double total_sum_weight = 0.0;
    long total_sum_count = 0;

    while (fread(&current_luggage, sizeof(LuggageInfo), 1, fp) == 1) {
        total_sum_weight += current_luggage.totalWeight;
        total_sum_count += current_luggage.itemCount;
    }

    fclose(fp);

    if (total_sum_count == 0) {
        return 0.0;
    }

    double global_avg = total_sum_weight / total_sum_count;
    printf("\nTotal sum of weights: %.2f kg\n", total_sum_weight);
    printf("Total number of items: %ld\n", total_sum_count);
    printf("Global average weight per item: %.2f kg\n", global_avg);
    return global_avg;
}

void get_passenger_name(int id, char *name_buffer) {
    if (id <= 0) {
        strcpy(name_buffer, "Unknown ID");
        return;
    }

    FILE *fp = fopen(PASSENGERS_FILE, "rb");
    if (fp == NULL) {
        perror("Error opening passenger file for reading");
        strcpy(name_buffer, "FILE ERROR");
        return;
    }

    Passenger p;
    long offset = (long)(id - 1) * sizeof(Passenger);

    if (fseek(fp, offset, SEEK_SET) != 0) {
        strcpy(name_buffer, "FSEEK ERROR");
    } else {
        if (fread(&p, sizeof(Passenger), 1, fp) == 1) {
            strcpy(name_buffer, p.lastName);
        } else {
            strcpy(name_buffer, "ID not found");
        }
    }

    fclose(fp);
}

void find_matching_passengers(double a) {
    double global_avg_weight = calculate_global_average_weight();

    if (global_avg_weight == 0.0) {
        printf("\nCannot perform search (global average weight = 0).\n");
        return;
    }

    FILE *fp = fopen(LUGGAGE_FILE, "rb");
    if (fp == NULL) {
        perror("Error opening luggage file for reading (search)");
        return;
    }

    printf("\n--- Search Results (Difference <= %.2f kg) ---\n", a);
    printf("-------------------------------------------------------------------\n");
    printf("| %-20s | %-10s | %-10s | %-10s | %-10s |\n",
           "Last Name", "ID", "Avg Indiv.", "Difference", "Status");
    printf("-------------------------------------------------------------------\n");


    LuggageInfo current_luggage;
    int found_count = 0;

    while (fread(&current_luggage, sizeof(LuggageInfo), 1, fp) == 1) {
        double individual_avg = 0.0;
        double difference = 0.0;
        char name[MAX_NAME_LEN];
        char status[10];

        if (current_luggage.itemCount > 0) {
            individual_avg = current_luggage.totalWeight / current_luggage.itemCount;
        }

        difference = fabs(individual_avg - global_avg_weight);

        if (difference <= a) {
            get_passenger_name(current_luggage.passengerID, name);
            strcpy(status, "FOUND");
            found_count++;
        } else {
             get_passenger_name(current_luggage.passengerID, name);
             strcpy(status, "---");
        }

        printf("| %-20s | %-10d | %-10.2f | %-10.2f | %-10s |\n",
               name,
               current_luggage.passengerID,
               individual_avg,
               difference,
               status);
    }

    printf("-------------------------------------------------------------------\n");
    if (found_count == 0) {
        printf("No passengers matching the condition were found.\n");
    }

    fclose(fp);
}