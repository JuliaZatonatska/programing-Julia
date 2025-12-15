#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 50
#define MAX_DAY_LEN 15

typedef struct {
    char subject[MAX_STR_LEN];
    char lecturer[MAX_STR_LEN];
    int group_number;
    char day_of_week[MAX_DAY_LEN];
    char time[MAX_STR_LEN];
    int classroom;
} Seminar;

void input_seminar(Seminar *s) {
    printf("\n*** Enter seminar information ***\n");

    printf("Enter subject name: ");
    scanf("%s", s->subject);

    printf("Enter lecturer's full name (no spaces): ");
    scanf("%s", s->lecturer);

    printf("Enter group number: ");
    scanf("%d", &s->group_number);

    printf("Enter day of the week: ");
    scanf("%s", s->day_of_week);

    printf("Enter class hours (e.g., 9:00): ");
    scanf("%s", s->time);

    printf("Enter classroom number: ");
    scanf("%d", &s->classroom);

    while (getchar() != '\n');
}

void output_seminar(const Seminar s) {
    printf("\n*** Seminar Information ***\n");
    printf("--------------------------------------\n");
    printf("  Subject: %s\n", s.subject);
    printf("  Lecturer: %s\n", s.lecturer);
    printf("  Group Number: %d\n", s.group_number);
    printf("  Day of the Week: %s\n", s.day_of_week);
    printf("  Class Hours: %s\n", s.time);
    printf("  Classroom: %d\n", s.classroom);
    printf("--------------------------------------\n");
}

int main() {
    Seminar my_seminar;
    input_seminar(&my_seminar);
    output_seminar(my_seminar);
    return 0;
}
