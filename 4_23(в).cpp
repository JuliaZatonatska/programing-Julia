#include <stdio.h>

int main() {
    int n;
    double sum = 0.0;

    printf("Enter a natural number n (number of elements): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error: n must be a natural number.\n");
        return 1;
    }

    double y[n];

    printf("Enter %d real numbers y_1, y_2, ..., y_n:\n", n);
    for (int i = 0; i < n; i++) {
        printf("y[%d]: ", i + 1);
        if (scanf("%lf", &y[i]) != 1) {
            printf("Error: Invalid real number entered.\n");
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (y[i] < 10.0) {
            sum += y[i];
        } else {
            sum += 1.0;
        }
    }

    printf("\nThe calculated sum S = z_1 + ... + z_n is: %.2f\n", sum);

    return 0;
}
