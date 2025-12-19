#include "new_head.h"

int main() {
    int n; 
    printf("Введите количество окружностей > ");
    scanf("%d", &n);

    circ* circles = simulate_circles(n);
    if (circles == NULL) {
        return 1;
    }

    for (int i = 0; i<n; i++) {
        double len = len_circle(&circles[i]);
        printf("Длина окружности %d: %.2f\n", i+1, len);
    }

    for (int i = 0; i<n; i++) {
        printf("Окружность %d ", i+1);
        intersection(&circles[i]);
    }

    free(circles);
}
