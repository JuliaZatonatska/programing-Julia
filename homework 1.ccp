#include <stdio.h>
#include <math.h>



void task10() {
    int x[5] = { 1, 2, 3, 4, 5 };
    float y[5] = { 3.0, 1.0, 5.0, 4.0, 2.1 };
    printf("x");
    for (int i = 0; i < 5; i++) {
        printf("| %.2d", x[i]);

    }printf("|\n");
    printf("- - - - - - - - - - -  \n");

    printf("y");
    for (int i = 0; i < 5; i++) {
        printf("| %.2f", y[i]);
    }
        printf("|\n");


    }


int main() {
    task10();
    return 0;
}