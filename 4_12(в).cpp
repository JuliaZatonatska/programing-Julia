#include <stdio.h>
#include <math.h>

double calculate_polynomial_b(double x, int n) {
    double y = 0.0;
    for (int i = 1; i <= n; i++) {
        int power = i * i;
        double term = pow(x, power);
        y += term;
    }
    return y;
}

int main() {
    double x_value = 2.0;
    int n_value = 3;

    double result = calculate_polynomial_b(x_value, n_value);

    printf("Calculating the polynomial: y = x^(1^2) + ... + x^(n^2)\n");
    printf("For x = %.2f and n = %d\n", x_value, n_value);
    printf("The value of y = %.2f\n", result);

    return 0;
}

