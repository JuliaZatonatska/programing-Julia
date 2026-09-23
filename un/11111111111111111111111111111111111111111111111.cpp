#include <stdio.h>

void x() {
    static int score = 0;
    score++;
    printf("result: %d\n", score);
}

int main() {
    x(); // Перший виклик -> Виведе 1
    x(); // Другий виклик -> Виведе 2
    x(); // Третій виклик -> Виведе 3
    return 0;
}