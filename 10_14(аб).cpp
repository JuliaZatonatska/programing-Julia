#include <stdio.h>
#include <string.h>

typedef struct {
    int name_index;
    char gender;
    double height_cm;
} PersonRecord;

double calculate_avg_female_height(const PersonRecord records_array[], int array_size) {
    double total_height = 0.0;
    int female_count = 0;

    for (int i = 0; i < array_size; i++) {
        if (records_array[i].gender == 'F') {
            total_height += records_array[i].height_cm;
            female_count++;
        }
    }

    return (female_count > 0) ? (total_height / female_count) : 0.0;
}

const char* find_tallest_male_name(const char names_list[][50], const PersonRecord records_array[], int array_size) {
    double max_height = -1.0;
    int tallest_male_index = -1;

    for (int i = 0; i < array_size; i++) {
        if (records_array[i].gender == 'M' && records_array[i].height_cm > max_height) {
            max_height = records_array[i].height_cm;
            tallest_male_index = i;
        }
    }

    return (tallest_male_index != -1) ? names_list[records_array[tallest_male_index].name_index] : "Not found";
}

int main() {
    char NamesList[][50] = {"Anna", "Peter", "Olena", "Ivan", "Maria", "Dmytro"};
    int L_size = sizeof(NamesList) / sizeof(NamesList[0]);

    PersonRecord PeopleRecords[] = {
        {0, 'F', 165.5},
        {1, 'M', 188.0},
        {2, 'F', 172.0},
        {3, 'M', 175.5},
        {4, 'F', 168.0},
        {5, 'M', 191.2}
    };
    int P_size = sizeof(PeopleRecords) / sizeof(PeopleRecords[0]);

    if (L_size != P_size) {
        printf("Error: L and P arrays must have the same number of elements!\n");
        return 1;
    }

    printf("=== Processing people data using L and P ===\n");

    double avg_female_height = calculate_avg_female_height(PeopleRecords, P_size);
    printf("\n[Task a)]\n");
    if (avg_female_height > 0.0) {
        printf("Average height of females: %.2f cm\n", avg_female_height);
    } else {
        printf("No females found in the array.\n");
    }

    const char* tallest_man = find_tallest_male_name(NamesList, PeopleRecords, P_size);
    printf("\n[Task b)]\n");
    printf("Name of the tallest male: %s\n", tallest_man);

    printf("================================================\n");

    return 0;
}
