#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 500

void printArr(int array[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int checkSum(int array[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += array[i];
    }
    return sum;
}

int runNumber(int array[], int n) {
    int c = 1;
    for (int i = 0; i < n-1; i++) {
        if (array[i] > array[i+1]) {
            c += 1;
        }
    }
    return c;
}

void fillInc(int array[], int n) {
    for (int i = 0; i < n; i++) {
        array[i] = i+1;
    }
}

void fillDec(int array[], int n) {
    for (int i = 0; i < n; i++) {
        array[i] = n-i;
    }
}

void fillRand(int array[], int n) {
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 5000;
    }
}

void selectSort(int array[], int n, int *M, int *C) {
    int min; *M = 0; *C = 0;

    for (int i = 0; i<n-1; i++) {
        min = i;
        for (int j = i+1; j<n; j++) {
            (*C)++;
            if (array[j] < array[min]) {
                min = j;
            }
        }
        int tmp = array[min];
        array[min] = array[i];
        array[i] = tmp;
        (*M) += 3;
    }
}

void bubbleSort(int array[], int n, int *M, int *C) {
    int min; *M = 0; *C = 0;
    for (int i = 0; i<n-1; i++) {
        for (int j = n-1; j>i; j--) {
            (*C)++;
            if (array[j] < array[j-1]) {
                int tmp = array[j-1];
                array[j-1] = array[j];
                array[j] = tmp;
                (*M)+=3;
            }
        }
    }
}

void shakerSort(int array[], int n, int *M, int *C) {
    *M = 0; *C = 0;
    int l = 0, r = n - 1, k = n - 1;
    while (l < r) {
        for (int i = r; i > l; i--) {
            (*C)++;
            if (array[i] < array[i-1]) {
                int temp = array[i];
                array[i] = array[i-1];
                array[i-1] = temp;
                *M += 3;
                k = i;
            }
        }
        if (k == r) break;
        l = k;
        for (int i = l; i < r; i++) {
            (*C)++;
            if (array[i] > array[i+1]) {
                int temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                *M += 3;
                k = i;
            }
        }
        if (k == l) break;
        r = k;
    }
}

void insertSort(int array[], int n, int *M, int *C) {
    *M = 0; *C = 0;

    for (int i = 1; i<n; i++) {
        int tmp = array[i];
        (*M)++;
        int j = i-1;

        while (j >= 0) {
            (*C)++;
            if (tmp < array[j]) {
                array[j+1] = array[j];
                (*M)++;
                j--;
            } else {
                break;
            }
        }
        array[j+1] = tmp;
        (*M)++;
    }
}

void test(const char* label, void (*fill)(int[], int)) {
    int A[N], B[N], m, c;
    fill(A, N);
    for(int i=0; i<N; i++) B[i] = A[i];

    printf(">>> %s Массив <<<\n", label);
    printf("До: "); printArr(A, N);
    printf("К. сумма: %d, К. серия: %d\n", checkSum(A, N), runNumber(A, N));

    insertSort(A, N, &m, &c);
    printf("После:  "); printArr(A, N);
    printf("M: %d, C: %d, Всего: %d\n", m, c, m+c);
}

int main() {
    srand(time(NULL));

    test("Возрастающий", fillInc);
    test("Убывающий", fillDec);
    test("Случайный", fillRand);

    printf("%-4s | %-11s| %-20s \n", "N", "Теоритические", "M+C");
    printf("     | M+C(для случ)| Возр    Случ   Убыв    \n");
    printf("-----|----------------------------------------------------------\n");

    int testSizes[] = {100, 200, 300, 400, 500};
    for (int s = 0; s < 5; s++) {
        int n = testSizes[s];
        int theory = (((n*n - n)/4)) + (((n*n - n)/4)+(n-1));
        int res[3];
        void (*fills[])(int[], int) = {fillInc, fillRand, fillDec};

        for (int f = 0; f < 3; f++) {
            int *arr = (int*)malloc(n * sizeof(int));
            int m, c;

            fills[f](arr, n);
            insertSort(arr, n, &m, &c);
            res[f] = m + c;

            free(arr);
        }

        printf("%-4d | %-12d | %-6d  %-6d  %-6d \n", n, theory, res[0], res[1], res[2]);
    }
    printf("\n");

    printf("N    |Select |Bubble |Shaker |Insert  \n");
    printf("-----|----------------------------------------------------------\n");
    for (int s = 0; s < 5; s++) {
        int n = testSizes[s];
        int res_2[4];
        void (*sorts[])(int[], int, int*, int*) = {selectSort, bubbleSort, shakerSort, insertSort};

        for (int srt = 0; srt < 4; srt++) {
            int *arr = (int*)malloc(n * sizeof(int));
            int m, c;
            
            fillRand(arr, n);
            sorts[srt](arr, n, &m, &c);
            res_2[srt] = m + c;

            free(arr);
        }
        printf("%-4d | %-6d  %-6d  %-6d  %-6d \n", n, res_2[0], res_2[1], res_2[2], res_2[3]);
    }
}