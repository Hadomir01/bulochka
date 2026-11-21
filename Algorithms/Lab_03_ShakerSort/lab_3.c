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

void test(const char* label, void (*fill)(int[], int)) {
    int A[N], B[N], m, c;
    fill(A, N);
    for(int i=0; i<N; i++) B[i] = A[i];

    printf(">>> %s Массив <<<\n", label);
    printf("До: "); printArr(A, N);
    printf("К. сумма: %d, К. серия: %d\n", checkSum(A, N), runNumber(A, N));

    bubbleSort(A, N, &m, &c);
    printf("После:  "); printArr(A, N);
    printf("Стандарт  -> M: %d, C: %d, Всего: %d\n", m, c, m+c);

    shakerSort(A, N, &m, &c);
    printf("После:  "); printArr(A, N);
    printf("Стандарт  -> M: %d, C: %d, Всего: %d\n", m, c, m+c);
}

int main() {
    srand(time(NULL));

    test("Возрастающий", fillInc);
    test("Убывающий", fillDec);
    test("Слчайный", fillRand);

    printf("%-4s | %-20s | %-24s\n", "N", "Bubble M+C", "Shaker M+C");
    printf("     | Возр    Случ   Убыв    | Возр    Случ   Убыв\n");
    printf("----------------------------------------------------------------\n");
        
    int testSizes[] = {100, 200, 300, 400, 500};
    for (int s = 0; s < 5; s++) {
        int n = testSizes[s];
        int theory = (3*(n*n - n) / 4) +((n*n - n)/2);
        int res[2][3];
        void (*fills[])(int[], int) = {fillInc, fillRand, fillDec};

        for (int f = 0; f < 3; f++) {
            int *arr = (int*)malloc(n * sizeof(int));
            int m, c;

            fills[f](arr, n);
            bubbleSort(arr, n, &m, &c);
            res[0][f] = m + c;

            fills[f](arr, n); 
            shakerSort(arr, n, &m, &c);
            res[1][f] = m + c;
            free(arr);
        }

        printf("%-4d | %-6d %-6d %-6d | %-6d %-6d %-6d\n", n, res[0][0], res[0][1], res[0][2], res[1][0], res[1][1], res[1][2]);
    }

}