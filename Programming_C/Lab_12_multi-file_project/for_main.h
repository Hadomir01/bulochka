#ifndef FOR_MAIN_H
#define FOR_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h> 

#define N 10

typedef struct {
    char name[32];
    int distance;
    int code;
    int weight;
} Object;

void random_fill(Object array[], int arr_size);
void selectSort(Object array[], int arr_size);
void print(Object array[], int arr_size);
void measure_sort_time(int sizes[], int num_sizes);

#endif