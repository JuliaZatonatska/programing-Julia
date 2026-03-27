#include <stdio.h>
#include <math.h>


double calculate_sine(double angle_in_radians) {
    double sine_result = sin(angle_in_radians);
    return sine_result;
}

int main() {
    double input_value = 0.785398;
    double intermediate_result;
    double final_sine_result;

    printf("--- Demonstration of mathematical functions ---\n");

    intermediate_result = sin(input_value);
    printf("1. sin(%f) = %f\n", input_value, intermediate_result);

    intermediate_result = atan(input_value);
    printf("2. atan(%f) = %f\n", input_value, intermediate_result);

    double sine_part;
    double arctan_part;
    double sum_result;

    sine_part = sin(input_value);
    arctan_part = atan(input_value);
    sum_result = sine_part + arctan_part;

    printf("3. sin(x) + atan(x) = %f\n", sum_result);

    printf("\n--- Demonstration of custom function ---\n");

    final_sine_result = calculate_sine(input_value);
    printf("4. Result of my_sin(%f) = %f\n", input_value, final_sine_result);

    return 0;
}
