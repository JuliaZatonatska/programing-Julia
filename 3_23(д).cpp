#include <stdio.h>


double Function_Range(double tl, double tr, double al, double ar, double x) {
    if (x <= tl) {
        return tl + al * (x - tl);
    }
    else if (x < tr) {
        return 0.0;
    }
    else {
        return tr + ar * (x - tr);
    }
}


double Function_Range_derivative(double tl, double tr, double al, double ar, double x) {
    if (x < tl) {
        return al;
    }
    else if (x > tr) {
        return ar;
    }
    else if (x > tl && x < tr) {
        return 0.0;
    }
    else if (x == tl) {
        return al;
    }
    else {
        return ar;
    }
}

int main() {
    double left_limit = -1.0;
    double right_limit = 1.0;
    double left_slope = 0.5;
    double right_slope = 2.0;

    printf("--- Testing Function_Range ---\n");

    double x_left = -3.0;
    double result_left = Function_Range(left_limit, right_limit, left_slope, right_slope, x_left);
    printf("Function_Range(x=%.1f) = %.2f. Derivative: %.1f\n",
           x_left, result_left, Function_Range_derivative(left_limit, right_limit, left_slope, right_slope, x_left));

    double x_middle = 0.0;
    double result_middle = Function_Range(left_limit, right_limit, left_slope, right_slope, x_middle);
    printf("Function_Range(x=%.1f) = %.2f. Derivative: %.1f\n",
           x_middle, result_middle, Function_Range_derivative(left_limit, right_limit, left_slope, right_slope, x_middle));

    double x_right = 3.0;
    double result_right = Function_Range(left_limit, right_limit, left_slope, right_slope, x_right);
    printf("Function_Range(x=%.1f) = %.2f. Derivative: %.1f\n",
           x_right, result_right, Function_Range_derivative(left_limit, right_limit, left_slope, right_slope, x_right));

    return 0;
}
