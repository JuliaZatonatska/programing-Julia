#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX_SIZE 100

bool is_even_perfect_cube(int num) {
    if (num <= 0 || num % 2 != 0) {
        return false;
    }

    double cube_root_double = cbrt((double)num);
    int root = (int)round(cube_root_double);

    if ((long long)root * root * root == num) {
        return true;
    }

    return false;
}

int main() {
    int N;
    int arr[MAX_SIZE];
    int count = 0;

    printf("Enter the size of the array N (max %d): ", MAX_SIZE);
    if (scanf("%d", &N) != 1 || N <= 0 || N > MAX_SIZE) {
        printf("Error: Invalid array size N.\n");
        return 1;
    }

    printf("Enter %d natural numbers:\n", N);
    for (int i = 0; i < N; i++) {
        printf("Element %d: ", i + 1);
        if (scanf("%d", &arr[i]) != 1 || arr[i] <= 0) {
            printf("Error: Entered value is not a natural number.\n");
            return 1;
        }
    }

    for (int i = 0; i < N; i++) {
        if (is_even_perfect_cube(arr[i])) {
            count++;
        }
    }

    printf("\n--- Result ---\n");
    printf("Number of even perfect cubes in the array: %d\n", count);

    return 0;
}
