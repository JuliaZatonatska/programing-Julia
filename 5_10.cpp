#include <stdio.h>
#include <math.h>

double calculate_vn(int n) {
    if (n < 0) {
        printf("Error: The sequence index must be non-negative.\n");
        return -1.0;
    }

    if (n == 0 || n == 1) {
        return 1.0;
    }

    double u_prev_prev = 0.0;
    double v_prev_prev = 1.0;
    double u_prev = 0.0;
    double v_prev = 1.0;
    double u_current = 0.0;
    double v_current = 0.0;

    for (int i = 2; i <= n; i++) {
        v_current = (u_prev - v_prev) / (fabs(u_prev_prev + v_prev) + 2.0);
        u_current = (u_prev - u_prev_prev * v_prev - v_prev_prev) / (1.0 + u_prev * u_prev + v_prev * v_prev);

        u_prev_prev = u_prev;
        v_prev_prev = v_prev;
        u_prev = u_current;
        v_prev = v_current;
    }

    return v_current;
}

int main() {
    int target_n;
    double result_vn;

    printf("Enter the index n of the sequence element v_n to calculate (e.g., 5): ");
    if (scanf("%d", &target_n) != 1) {
        printf("Error: Invalid index input.\n");
        return 1;
    }

    result_vn = calculate_vn(target_n);

    if (result_vn != -1.0) {
        printf("\nCalculated element v_%d = %.10f\n", target_n, result_vn);
    }

    return 0;
}
