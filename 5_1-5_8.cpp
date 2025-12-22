#include <stdio.h>
#include <math.h>
#include <float.h>

long long factorial(int n) {
    long long res = 1;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

void task1_a_b(double a) {
    printf("\n--- Task 1 ---\n");
    double sum = 0.0;
    int n = 0;

    printf("a) First number of the sequence 1 + 1/2 + ... + 1/n greater than %.3f:\n", a);

    do {
        n++;
        sum += 1.0 / n;
        printf("S_%d = %.5f\n", n, sum);
    } while (sum <= a);

    printf("   Found: S_%d = %.5f\n", n, sum);
    printf("b) Smallest n > 0 such that 1 + 1/2 + ... + 1/n > %.3f: n = %d\n", a, n);
}

long long fib_recursive(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

long long fib_iterative(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    long long prev1 = 1;
    long long prev2 = 0;
    long long current = 0;

    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    return current;
}

void task2(double a) {
    printf("\n--- Task 2 (Fibonacci numbers) ---\n");
    int n_test = 10;
    printf("a) F_%d (iterative) = %lld\n", n_test, fib_iterative(n_test));

    long long F_k = 0;
    long long prev1 = 1;
    long long prev2 = 0;
    int k = 1;
    int max_k_le_a = 0;

    while (prev1 <= a) {
        max_k_le_a = k;
        F_k = prev1 + prev2;
        prev2 = prev1;
        prev1 = F_k;
        k++;
    }
    printf("b) Index of the largest F_k <= %.3f: k = %d (F_%d = %lld)\n", a, max_k_le_a, max_k_le_a, (max_k_le_a == 0) ? 0 : fib_iterative(max_k_le_a));
    printf("c) Index of the smallest F_k > %.3f: k = %d (F_%d = %lld)\n", a, k - 1, k - 1, prev2);

    long long limit = 1000;
    long long sum_fib = 0;
    prev1 = 1;
    prev2 = 0;
    k = 1;

    printf("d) Sum of F_k <= 1000: ");
    while (prev1 <= limit) {
        sum_fib += prev1;
        printf("%lld ", prev1);
        F_k = prev1 + prev2;
        prev2 = prev1;
        prev1 = F_k;
    }
    printf("\n   Total sum: %lld\n", sum_fib);
}

int collatz_steps(int n, int *steps_count) {
    (*steps_count)++;
    if (n == 1) {
        return 1;
    }
    if (n % 2 == 0) {
        return collatz_steps(n / 2, steps_count);
    } else {
        return collatz_steps(3 * n + 1, steps_count);
    }
}

void task3() {
    printf("\n--- Task 3 (3n+1 sequence) ---\n");
    int max_n = 999;
    int max_steps = 0;
    int n_with_max_steps = 0;

    for (int n = 1; n <= max_n; n++) {
        int steps = 0;
        collatz_steps(n, &steps);

        if (steps > max_steps) {
            max_steps = steps;
            n_with_max_steps = n;
        }
    }
    printf("Among n < 1000, the number requiring the most steps to reach 1: n = %d\n", n_with_max_steps);
    printf("   Maximum number of steps: %d\n", max_steps);
    printf("(Sequence always converges to 1 for n < 1000, verified in the loop)\n");
}

void task4(int n) {
    printf("\n--- Task 4 (Products) ---\n");
    double P_n_a = 1.0;
    double P_n_b = 1.0;

    printf("For n = %d:\n", n);

    for (int i = 1; i <= n; i++) {
        double a_i = 1.0 + 1.0 / i;
        P_n_a *= a_i;
    }
    printf("a) P_n = Prod(1 + 1/i) = %.5f\n", P_n_a);

    for (int i = 1; i <= n; i++) {
        double sign = (i % 2 == 1) ? 1.0 : -1.0;
        double a_i = 1.0 + sign / pow(2.0, i);
        P_n_b *= a_i;
    }
    printf("b) P_n = Prod(1 + (-1)^(i+1) / 2^i) = %.5f\n", P_n_b);
}

void task5(int max_n) {
    printf("\n--- Task 5 (Smallest positive term) ---\n");
    if (max_n < 3) max_n = 10;

    int x1 = -99;
    int x2 = -99;
    int x3 = -99;
    int x_current;

    int min_positive_x = 2147483647;
    int min_positive_index = -1;

    for (int n = 4; n <= max_n; n++) {
        x_current = x3 + x1 + 100;

        if (x_current > 0 && x_current < min_positive_x) {
            min_positive_x = x_current;
            min_positive_index = n;
            if (min_positive_index != -1 && n > min_positive_index + 10) break;
        }

        x1 = x2;
        x2 = x3;
        x3 = x_current;
    }

    if (min_positive_index != -1) {
        printf("Smallest positive term: x_%d = %d\n", min_positive_index, min_positive_x);
    } else {
        printf("No positive terms found up to n = %d.\n", max_n);
    }
}

double chain_fraction_a(double b, int n) {
    if (n == 0) return 0;
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result = b + 1.0 / result;
    }
    return result;
}

double chain_fraction_b(int n) {
    if (n == 0) return 2.0;

    double b_prev = (double)(4 * n + 2);
    double b_current = 0.0;

    for (int k = 1; k <= n; k++) {
        double current_denominator = (double)(4 * (n - k) + 2);
        b_current = current_denominator + 1.0 / b_prev;
        b_prev = b_current;
    }

    return 2.0 + 1.0 / b_current;
}

double chain_fraction_c(int n) {
    if (n == 0) return 1.0;

    double result = 0.0;
    for (int k = 2 * n; k >= 2; k--) {
        result = 2.0 + (double)k / result;
    }
    return 1.0 + 2.0 / result;
}

void task6(int n) {
    printf("\n--- Task 6 (Continued fractions) ---\n");
    double b_val = 2.0;
    printf("For n=%d, b=%.1f:\n", n, b_val);

    printf("a) b_n (b + 1/(b + ...)): %.5f\n", chain_fraction_a(b_val, n));
    printf("b) lambda_n (by recursive instruction): %.5f\n", chain_fraction_b(n));
    printf("c) x_2n (for 2n=%d): %.5f\n", 2 * n, chain_fraction_c(n));
}

void task7(int n) {
    printf("\n--- Task 7 (Sum with recurrent sequences) ---\n");

    if (n < 1) {
        printf("Sum S_n is undefined for n < 1.\n");
        return;
    }

    long long a_prev2 = 0;
    long long a_prev1 = 1;
    long long a_current;

    long long b_prev2 = 1;
    long long b_prev1 = 0;
    long long b_current;

    double S_n = 0.0;

    double term1 = (double)pow(2, 1) / (a_prev2 + b_prev2);
    S_n += term1;

    if (n >= 2) {
        double term2 = (double)pow(2, 2) / (a_prev1 + b_prev1);
        S_n += term2;
    }

    for (int k = 3; k <= n; k++) {
        a_current = a_prev1 + a_prev2;
        b_current = b_prev1 + a_prev1;

        double term_k = (double)pow(2, k) / (a_current + b_current);
        S_n += term_k;

        a_prev2 = a_prev1;
        a_prev1 = a_current;
        b_prev2 = b_prev1;
        b_prev1 = b_current;
    }

    printf("Sum S_%d = %.5f\n", n, S_n);
}

double taylor_exp(double x, double epsilon) {
    double sum = 1.0;
    double term = 1.0;
    int n = 1;

    do {
        term *= x / n;
        sum += term;
        n++;
    } while (fabs(term) >= epsilon);

    return sum;
}

double taylor_phi(double x, double epsilon) {
    double sum = x;
    double term = x;
    int n = 1;

    do {
        term *= -1.0 * x * x / ((2 * n + 1) * (2 * n));
        sum += term;
        n++;
    } while (fabs(term) >= epsilon);

    return sum;
}

void task8(double x, double epsilon) {
    printf("\n--- Task 8 (Taylor series) ---\n");
    printf("x = %.3f, Precision epsilon = %.1e\n", x, epsilon);

    double exp_taylor = taylor_exp(x, epsilon);
    double exp_math = exp(x);
    printf("a) e^x:\n");
    printf("   Taylor series: %.10f\n", exp_taylor);
    printf("   exp() function: %.10f\n", exp_math);
    printf("   Difference: %.1e\n", fabs(exp_taylor - exp_math));

    double phi_taylor = taylor_phi(x, epsilon);
    printf("b) Phi(x) = Integral(exp(-t^2) dt):\n");
    printf("   Taylor series: %.10f\n", phi_taylor);
}

int main() {

    double a_val = 5.0;
    int n_val = 10;
    int max_n_val = 100;
    double x_val = 0.5;
    double epsilon_val = 1e-6;

    task1_a_b(a_val);
    task2(a_val);
    task3();
    task4(n_val);
    task5(max_n_val);
    task6(n_val);
    task7(n_val);
    task8(x_val, epsilon_val);

    return 0;
}
