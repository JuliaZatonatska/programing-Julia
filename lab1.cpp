#include <stdio.h>
#include <math.h>

void task1() {
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    printf("Sum = %d\n", a + b);
}

void task2() {
    float r;
    printf("Enter radius: ");
    scanf("%f", &r);
    printf("Area = %.2f\n", M_PI * r * r);
    printf("Perimeter = %.2f\n", 2 * M_PI * r);
}

void task3() {
    int n;
    printf("Enter number: ");
    scanf("%d", &n);
    if (n % 2 == 0) printf("Even\n");
    else printf("Odd\n");
}

void task4() {
    int n, fact = 1;
    printf("Enter number: ");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) fact *= i;
    printf("Factorial = %d\n", fact);
}

void task5() {
    int n, prime = 1;
    printf("Enter number: ");
    scanf("%d", &n);
    if (n < 2) prime = 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) prime = 0;
    }
    if (prime) printf("Prime\n");
    else printf("Not prime\n");
}

void task6() {
    int n, sum = 0;
    printf("Enter number: ");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) sum += i;
    printf("Sum = %d\n", sum);
}

void task7() {
    int a, b, gcd = 1;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    int min = (a < b) ? a : b;
    for (int i = 1; i <= min; i++) {
        if (a % i == 0 && b % i == 0) gcd = i;
    }
    printf("GCD = %d\n", gcd);
}

void task8() {
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    printf("Max = %d\n", (a > b) ? a : b);
}

void task9() {
    int n, sum = 0;
    printf("Enter number: ");
    scanf("%d", &n);
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    printf("Sum of digits = %d\n", sum);
}

void task10() {
    int x[5] = {1, 2, 3, 4, 5};
    float y[5] = {3.0, 1.0, 5.0, 4.0, 2.1};

    printf("x |");
    for (int i = 0; i < 5; i++) printf(" %d |", x[i]);
    printf("\n-------------------------\n");
    printf("y |");
    for (int i = 0; i < 5; i++) printf(" %.1f |", y[i]);
    printf("\n");
}

void task14() {
    double a, v;
    printf("Enter acceleration a: ");
    scanf("%lf", &a);
    printf("Enter velocity v: ");
    scanf("%lf", &v);

    double t = v / a;
    double s = 0.5 * a * t * t;

    printf("Time = %.2f\n", t);
    printf("Distance = %.2f\n", s);
}

int main() {
    int choice;
    while (1) {
        printf("\nChoose task (1-9, 10, 14, 0 to exit): ");
        scanf("%d", &choice);

        if (choice == 0) break;

        switch(choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            case 6: task6(); break;
            case 7: task7(); break;
            case 8: task8(); break;
            case 9: task9(); break;
            case 10: task10(); break;
            case 14: task14(); break;
            default: printf("No such task\n");
        }
    }
    return 0;
}