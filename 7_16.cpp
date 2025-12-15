#include <stdio.h>
#include <math.h>

#define MAX_DIMENSION 100

double calculate_rosenbrock(const double x[], int d) {
    if (d < 2) {
        return 0.0;
    }

    double sum = 0.0;

    for (int i = 0; i < d - 1; i++) {
        double term1_inner = x[i+1] - (x[i] * x[i]);
        double term2_inner = x[i] - 1.0;
        sum += 100.0 * (term1_inner * term1_inner) + (term2_inner * term2_inner);
    }

    return sum;
}

int main() {
    double x_min_2d[2] = {1.0, 1.0};
    int d_2d = 2;
    double result_2d_min = calculate_rosenbrock(x_min_2d, d_2d);

    double x_test_2d[2] = {0.0, 0.0};
    double result_2d_test = calculate_rosenbrock(x_test_2d, d_2d);

    double x_min_4d[4] = {1.0, 1.0, 1.0, 1.0};
    int d_4d = 4;
    double result_4d_min = calculate_rosenbrock(x_min_4d, d_4d);

    double x_test_4d[4] = {2.0, 3.0, 4.0, 5.0};
    double result_4d_test = calculate_rosenbrock(x_test_4d, d_4d);

    printf("--- Test for d=2 ---\n");
    printf("Vector (1.0, 1.0) -> f(x) = %f (Expected 0.0)\n", result_2d_min);
    printf("Vector (0.0, 0.0) -> f(x) = %f (Expected 101.0)\n", result_2d_test);
    printf("\n");

    printf("--- Test for d=4 ---\n");
    printf("Vector (1.0, 1.0, 1.0, 1.0) -> f(x) = %f (Expected 0.0)\n", result_4d_min);
    printf("Vector (2.0, 3.0, 4.0, 5.0) -> f(x) = %f\n", result_4d_test);

    return 0;
}
