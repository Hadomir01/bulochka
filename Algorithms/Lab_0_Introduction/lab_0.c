#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

void printArr(int array[N]) {
    for (int i = 0; i < N; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

long checkSum(int array[N]) {
    long sum = 0;
    for (int i = 0; i < N; i++) {
        sum += array[i];
    }
    return sum;
}

int runNumber(int array[N]) {
    int c = 1;
    for (int i = 0; i < N-1; i++) {
        if (array[i] > array[i+1]) {
            c += 1;
        }
    }
    return c;
}

void fillInc(int array[N]) {
    for (int i = 0; i < N; i++) {
        array[i] = i+1;
    }
    printArr(array);
}

void fillDec(int array[N]) {
    for (int i = 0; i < N; i++) {
        array[i] = N-i;
    }
    printArr(array);
}

void fillRand(int array[N]) {
    for (int i = 0; i < N; i++) {
        array[i] = rand() % 2147483647;
    }
    printArr(array);
}

int main() {
    srand(time(NULL));
    int arr[N] = {};
    int rand_arr[N] = {};

    fillInc(arr);
    fillDec(arr);
    fillRand(rand_arr);
}