#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double calculate_torus_volume(double inner_radius, double outer_radius) {
    if (inner_radius <= 0 || outer_radius <= 0 || inner_radius >= outer_radius) {
        printf("Error: Radii must be positive, and the inner radius (r) must be smaller than the outer radius (R).\n");
        return -1.0;
    }

    double major_radius = (outer_radius + inner_radius) / 2.0;
    double minor_radius = (outer_radius - inner_radius) / 2.0;
    double volume = 2.0 * PI * PI * major_radius * minor_radius * minor_radius;

    return volume;
}

int main() {
    double R = 10.0;
    double r = 4.0;
    double volume;

    printf("--- Torus Volume Calculation ---\n");
    printf("Outer radius (R) = %.2f\n", R);
    printf("Inner radius (r) = %.2f\n", r);

    volume = calculate_torus_volume(r, R);

    if (volume > 0) {
        printf("\nCalculated Parameters:\n");
        printf("  Mean radius (R0) = %.2f\n", (R + r) / 2.0);
        printf("  Cross-section radius (a) = %.2f\n", (R - r) / 2.0);
        printf("\nTorus Volume (V) = %f\n", volume);
    }

    printf("\n--- Example with Incorrect Data ---\n");
    calculate_torus_volume(15.0, 5.0);

    return 0;
}
