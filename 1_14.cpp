#include <stdio.h>

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
    task14();
    return 0;
}