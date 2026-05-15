#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 32

void *sleepSort(void *var) {
    int* time = (int*)var;
    usleep(*time * 10000);
    printf("%d ", *time);
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t tid[50];

    int arr[N];
    printf("Неотсортированный массив >> ");
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Отсортированный массив >> ");
    for (int i = 0; i < N; i++) {
        pthread_create(&tid[i], NULL, sleepSort, &arr[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }
    printf("\n");


}