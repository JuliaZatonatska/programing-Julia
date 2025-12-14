#include <stdio.h>
#include <math.h>

int find_intersections(double r, double a, double b, double c_sqr) {
    if (r <= 0.0 || c_sqr < 0.0) {
        fprintf(stderr, "Error: Radius must be positive (r > 0) or c_sqr is negative.\n");
        return -1;
    }

    const double r_sqr = r * r;
    const double a_sqr = a * a;

    if (a_sqr > r_sqr) {
        return 0;
    }

    const double y_sqr = r_sqr - a_sqr;
    const double y_abs = sqrt(y_sqr);

    const double y_min = b;
    const double y_max = b + c_sqr;

    int count = 0;

    if (y_abs >= y_min && y_abs <= y_max) {
        count++;
    }

    if (y_abs > 0.0) {
        const double y_negative = -y_abs;
        if (y_negative >= y_min && y_negative <= y_max) {
            count++;
        }
    }

    return count;
}

int main() {
    double r1 = 5.0;
    double a1 = 3.0;
    double b1 = 2.0;
    double c1_sqr = 4.0;

    int result1 = find_intersections(r1, a1, b1, c1_sqr);
    printf("--- Example 1 ---\n");
    printf("Circle r=%.1f, Line x=%.1f\n", r1, a1);
    printf("Segment y=[%.1f, %.1f]\n", b1, b1 + c1_sqr);
    printf("Result: %d intersection points.\n\n", result1);

    double r2 = 10.0;
    double a2 = 6.0;
    double b2 = -10.0;
    double c2_sqr = 20.0;

    int result2 = find_intersections(r2, a2, b2, c2_sqr);
    printf("--- Example 2 ---\n");
    printf("Circle r=%.1f, Line x=%.1f\n", r2, a2);
    printf("Segment y=[%.1f, %.1f]\n", b2, b2 + c2_sqr);
    printf("Result: %d intersection points.\n\n", result2);

    double r3 = 5.0;
    double a3 = 7.0;
    double b3 = 0.0;
    double c3_sqr = 1.0;

    int result3 = find_intersections(r3, a3, b3, c3_sqr);
    printf("--- Example 3 ---\n");
    printf("Circle r=%.1f, Line x=%.1f\n", r3, a3);
    printf("Segment y=[%.1f, %.1f]\n", b3, b3 + c3_sqr);
    printf("Result: %d intersection points.\n\n", result3);

    return 0;
}
