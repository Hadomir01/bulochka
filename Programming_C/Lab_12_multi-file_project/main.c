#include "for_main.h"

int main() {
    srand(time(NULL));

    Object array[N] = {};
    int sizes[3] = {100, 10000, 100000};
    int count_sizes = sizeof(sizes) / sizeof(sizes[0]);

    random_fill(array, N);
    printf("Нужна сортировка по коду? (y/n) ");
    char ans;
    scanf("%c", &ans);
    if (ans == 'y' || ans == 'Y') {
        selectSort(array, N);
    }
    print(array, N);

    measure_sort_time(sizes, count_sizes);
}