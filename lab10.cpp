#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char file;
    int rank;
} ChessSquare;

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point p1;
    Point p2;
} Rectangle;

typedef struct {
    int degree;
    double coeffs[10];
} Polynomial;

typedef struct {
    double price;
    int age;
} Car;

typedef struct {
    double price;
    int circulation;
} Magazine;

void print_date(Date d) {
    printf("%02d.%02d.%d", d.day, d.month, d.year);
}

Date read_date() {
    Date d;
    printf("Enter day, month, year (e.g., 20 12 2025): ");
    scanf("%d %d %d", &d.day, &d.month, &d.year);
    return d;
}

void print_square(ChessSquare s) {
    printf("%c%d", s.file, s.rank);
}

ChessSquare read_square() {
    ChessSquare s;
    printf("Enter a chess square (e.g., a5): ");
    scanf(" %c%d", &s.file, &s.rank);
    return s;
}

bool is_queen_move(ChessSquare s1, ChessSquare s2) {
    int rank_diff = abs(s1.rank - s2.rank);
    int file_diff = abs(s1.file - s2.file);

    bool is_vertical = (rank_diff > 0 && file_diff == 0);
    bool is_horizontal = (rank_diff == 0 && file_diff > 0);
    bool is_diagonal = (rank_diff == file_diff && rank_diff > 0);

    return is_vertical || is_horizontal || is_diagonal;
}

bool is_leap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int month, int year) {
    if (month == 2) {
        return is_leap(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}

Date get_tomorrow(Date today) {
    Date tomorrow = today;
    int max_days = days_in_month(today.month, today.year);

    if (today.day < max_days) {
        tomorrow.day++;
    } else {
        tomorrow.day = 1;
        if (today.month < 12) {
            tomorrow.month++;
        } else {
            tomorrow.month = 1;
            tomorrow.year++;
        }
    }
    return tomorrow;
}

int get_day_of_week(Date d) {
    int day_number = 0;
    for (int m = 1; m < d.month; m++) {
        day_number += days_in_month(m, d.year);
    }
    day_number += d.day;

    int day_of_week_start = 0;

    return (day_number - 1 + day_of_week_start) % 7;
}

void print_day_of_week_name(int dow) {
    switch (dow) {
        case 0: printf("Monday"); break;
        case 1: printf("Tuesday"); break;
        case 2: printf("Wednesday"); break;
        case 3: printf("Thursday"); break;
        case 4: printf("Friday"); break;
        case 5: printf("Saturday"); break;
        case 6: printf("Sunday"); break;
        default: printf("Day of week error");
    }
}

void calculate_avg_old_cars_price(Car cars[], int n) {
    double total_price = 0.0;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (cars[i].age > 5) {
            total_price += cars[i].price;
            count++;
        }
    }

    printf("\n--- Task 7 Result ---\n");
    if (count > 0) {
        double average_price = total_price / count;
        printf("Found %d cars older than 5 years.\n", count);
        printf("Average price of these cars: %.2f\n", average_price);
    } else {
        printf("No cars older than 5 years found.\n");
    }
}

void calculate_avg_low_circulation_magazines(Magazine mags[], int n) {
    double total_price = 0.0;
    int count = 0;
    const int CIRCULATION_LIMIT = 10000;

    for (int i = 0; i < n; i++) {
        if (mags[i].circulation < CIRCULATION_LIMIT) {
            total_price += mags[i].price;
            count++;
        }
    }

    printf("\n--- Task 8 Result ---\n");
    if (count > 0) {
        double average_price = total_price / count;
        printf("Found %d magazines with circulation less than %d.\n", count, CIRCULATION_LIMIT);
        printf("Average price of these magazines: %.2f\n", average_price);
    } else {
        printf("No magazines with circulation less than %d found.\n", CIRCULATION_LIMIT);
    }
}

void task1() {
    printf("\n--- Task 1: Structure Demonstration and I/O ---\n");

    Date d = read_date();
    printf("You entered date: ");
    print_date(d);
    printf("\n");

    ChessSquare s = read_square();
    printf("You entered square: ");
    print_square(s);
    printf("\n");

    Rectangle rect = {{1.0, 2.0}, {5.0, 8.0}};
    printf("Rectangle declared with coordinates (%.1f, %.1f) and (%.1f, %.1f).\n",
           rect.p1.x, rect.p1.y, rect.p2.x, rect.p2.y);

    Polynomial poly = {2, {3.0, 4.0, 1.0}};
    printf("Polynomial of second degree declared: %.1f + %.1fx + %.1fx^2.\n",
           poly.coeffs[0], poly.coeffs[1], poly.coeffs[2]);
}

void task2() {
    printf("\n--- Task 2: Queen's Move Check ---\n");
    ChessSquare start = read_square();
    ChessSquare end = read_square();

    printf("Checking move from ");
    print_square(start);
    printf(" to ");
    print_square(end);
    printf(".\n");

    if (is_queen_move(start, end)) {
        printf("Result: ✅ Queen can move in one step.\n");
    } else {
        printf("Result: ❌ Queen cannot move in one step.\n");
    }
}

void task3() {
    printf("\n--- Task 3: Date Calculations ---\n");
    Date today = read_date();

    Date tomorrow = get_tomorrow(today);
    printf("Today's date: ");
    print_date(today);
    printf("\n");
    printf("Tomorrow's date: ");
    print_date(tomorrow);
    printf("\n");

    int dow = get_day_of_week(today);
    printf("Day of the week for the entered date: ");
    print_day_of_week_name(dow);
    printf(" (NOTE: A reference day is needed for accurate calculation).\n");
}

void task7() {
    printf("\n--- Task 7: Average price of cars older than 5 years ---\n");
    const int N_CARS = 5;
    Car cars[N_CARS] = {
        {15000.0, 2},
        { 8000.0, 6},
        {25000.0, 1},
        { 5000.0, 8},
        {10000.0, 5}
    };

    printf("Using test data for %d cars.\n", N_CARS);
    calculate_avg_old_cars_price(cars, N_CARS);
}

void task8() {
    printf("\n--- Task 8: Average price of magazines with circulation < 10000 ---\n");
    const int N_MAGS = 4;
    Magazine mags[N_MAGS] = {
        {25.50, 5000},
        {40.00, 12000},
        {18.99, 9999},
        {30.00, 1500}
    };

    printf("Using test data for %d magazines.\n", N_MAGS);
    calculate_avg_low_circulation_magazines(mags, N_MAGS);
}

void task4() { }
void task5() { }
void task6() { }
void task9() { }
void task10() { }
void task14() { }

int main() {
    int choice;
    while (1) {
        printf("\n======================================================\n");
        printf("Select a task to execute:\n");
        printf("1: Structures Date, Square, Rectangle, Polynomial (I/O)\n");
        printf("2: Queen's Move Check (ChessSquare)\n");
        printf("3: Calculate Tomorrow's Date and Day of Week (Date)\n");
        printf("7: Average Car Price (age > 5)\n");
        printf("8: Average Magazine Price (circulation < 10000)\n");
        printf("0: Exit\n");
        printf("======================================================\n");
        printf("Your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 0) break;

        while (getchar() != '\n');

        switch(choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 7: task7(); break;
            case 8: task8(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            case 6: task6(); break;
            case 9: task9(); break;
            case 10: task10(); break;
            case 14: task14(); break;
            default: printf("Task %d is not implemented or does not exist.\n", choice);
        }
    }
    return 0;
}