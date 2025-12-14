#include <stdio.h>

int getInputX() {
    int x;
    printf("Enter an integer value for x:\n");
    scanf("%d", &x);
    return x;
}


int calculate(int x) {
    return x*x*x*x*x + x*x*x + x;
}

int main() {
    int x_value;
    int y_result;

    x_value = getInputX();
    y_result = calculate(x_value);

    printf("x = %d , y =x^5 + x^3 + x ==>\n", x_value);
    printf("y = %d\n", y_result);

    return 0;
}
