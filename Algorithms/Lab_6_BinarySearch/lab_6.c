#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
    int value;
    int index;
} result;

void fillInc(int array[], int n) {
    for (int i = 0; i < n; i++) array[i] = i + 1;
}

void fillDec(int array[], int n) {
    for (int i = 0; i < n; i++) array[i] = n - i;
}

void fillRand(int array[], int n) {
    for (int i = 0; i < n; i++) array[i] = rand() % 50;
}

void insertSort(int array[], int n) {
    for (int i = 1; i<n; i++) {
        int tmp = array[i];
        int j = i-1;

        while (j >= 0) {
            if (tmp < array[j]) {
                array[j+1] = array[j];
                j--;
            } else {
                break;
            }
        }
        array[j+1] = tmp;
    }
}

result binSearchv1(int arr[], int n, int x, int *C) {
    int l = 0, r = n - 1;
    result res = {0, -1};
    *C = 0; 

     while (l <= r) {
        int m = l + (r - l) / 2;
        (*C)++;
        if (arr[m] == x) {
            res.value = arr[m];
            res.index = m;
            return res;
        }
        (*C)++;
        if (arr[m] < x) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return res;
} 

result binSearchv2(int arr[], int n, int x, int *C) {
    int l = 0, r = n - 1; 
    result res = {0, -1};
    *C = 0; 
    while (l < r) {
        int m = (l+r) / 2;
        (*C)++;
        if (arr[m] < x) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    (*C)++;
    if (arr[l] == x) {
        res.value = arr[l];
        res.index = l;
    } 
    return res;
}



int main() {
    srand(time(NULL));

    int testSizes[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int x;
    printf("Число для поиска > ");
    scanf("%d", &x);

    printf("n    | v1  | v2  \n");
    printf("--------------------------\n");
    for (int s = 0; s < 10; s++) {
        int n = testSizes[s];
        int res[2];
        void (*fills[])(int[], int) = {fillRand};

        int *arr = (int*)malloc(n * sizeof(int));
        int  c;

        fillRand(arr, n);
        insertSort(arr, n);

        binSearchv1(arr, n, x, &c);
        res[0] = c;

        binSearchv2(arr, n, x, &c);
        res[1] = c;

        free(arr);

        printf("%-4d | %-6d  %-6d  \n", n, res[0], res[1]);
    }
    return 0;
}
