//
// Created by User on 05.09.2025.
//
#include <stdio.h>
#include <math.h>

double Rosenbrock2d(double x, double y) {
    return 100 * pow((y - x * x), 2) + pow((1 - x), 2);
}
int main() {
    printf("%f\n", Rosenbrock2d(1, 1));
    printf("%f\n", Rosenbrock2d(2, 4));
    printf("%f\n", Rosenbrock2d(2, 3));
    return 0;
}



