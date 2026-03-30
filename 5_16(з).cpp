#include <stdio.h>
#include <math.h>

void calculate_series_sum(double x, double epsilon) {
    if (fabs(x) >= 1.0) {
        printf("Error: Convergence condition |x| < 1 is not satisfied.\n");
        return;
    }
    if (epsilon <= 0.0) {
        printf("Error: Precision epsilon must be > 0.\n");
        return;
    }

    double sum = 0.0;
    double current_term;
    int n = 0;

    current_term = 1.0;

    printf("\nCalculations:\n");
    do {
        sum += current_term;
        printf("n=%d, term=%.10lf, |term|=%.10lf, sum=%.10lf\n",
               n, current_term, fabs(current_term), sum);

        n++;
        current_term = current_term * (-(n + 1.0) / n) * x;

    } while (fabs(current_term) >= epsilon);

    double exact_value = 1.0 / pow((1.0 + x), 2);

    printf("\n--- Results ---\n");
    printf("Precision (epsilon): %.10lf\n", epsilon);
    printf("Number of terms added (until |a_n| < epsilon): %d\n", n);
    printf("Approximate sum of the series (S): %.10lf\n", sum);
    printf("Exact value of the function (y): %.10lf\n", exact_value);
    printf("Absolute error: %.10lf\n", fabs(exact_value - sum));
}

int main() {
    double x_value;
    double epsilon_value;

    printf("--- Program to calculate the sum of the series y = 1/(1+x)^2 ---\n");

    printf("Enter the value of x (where |x| < 1): ");
    if (scanf("%lf", &x_value) != 1) {
        printf("Error in entering x.\n");
        return 1;
    }

    printf("Enter the precision epsilon (> 0): ");
    if (scanf("%lf", &epsilon_value) != 1) {
        printf("Error in entering epsilon.\n");
        return 1;
    }

    calculate_series_sum(x_value, epsilon_value);

    return 0;
}
