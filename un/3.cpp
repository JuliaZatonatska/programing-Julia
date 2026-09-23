//
// Created by User on 17.09.2025.
//

#include <stdio.h>

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task3();


int main() {
    int choice;
    printf("input n= ");
    scanf("%d", &choice);

    if (choice == 1) {
        task1();
    } else if (choice == 2) {
        task2();
    } else if (choice == 3) {
        task3();
    } else if (choice == 4) {
        task4();
    } else if (choice == 5) {
        task5();
    } else if (choice == 6) {
        task6();
    } else if (choice == 7) {
        task7();
    } else {
        printf("error.\n");
    }
    void task1() {
        unsigned char n;
        printf("input n=: ");
       scanf("%hhu", &n);

      if (n == 0 || n >= 64) {
            printf("error.\n");
            return;
        }

        unsigned long long result = 1ULL << n;
        printf("2^%hhu = %llu\n", n, result);
    }

    void task2() {}

    void task3() {unsigned long long t;

        printf("Input number: ");
        scanf("%llu", &t)

        t = t | 1;

        printf("tenteen : %llu\n", t);
        printf("sixteen: %llX\n", t);
    }
    void task4() {}


    void task5() {}

    void task6() {}

    void task7() {}