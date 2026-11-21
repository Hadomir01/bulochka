#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

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

void selectSortUp(int array[], int n, int *M, int *C) {
    *M = 0; *C = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_i = i;
        for (int j = i + 1; j < n; j++) {
            (*C)++;
            if (array[j] < array[min_i]) min_i = j;
        }
        if (min_i != i) {
            int temp = array[i];
            array[i] = array[min_i];
            array[min_i] = temp;
            (*M) += 3;
        }
    }
}

void test(const char* label, void (*fill)(int[], int)) {
    int A[N], B[N], m, c;
    fill(A, N);
    for(int i=0; i<N; i++) B[i] = A[i];

    printf(">>> %s Массив <<<\n", label);
    printf("До: "); printArr(A, N);
    printf("К. сумма: %d, К. серия: %d\n", checkSum(A, N), runNumber(A, N));

    selectSort(A, N, &m, &c);
    printf("После:  "); printArr(A, N);
    printf("Стандарт  -> M: %d, C: %d, Всего: %d\n", m, c, m+c);
    
    selectSortUp(B, N, &m, &c);
    printf("Улучшение -> М: %d, С: %d, Всего: %d\n", m, c, m+c);
    printf("К. сумма после: %d, К. серия после: %d\n", checkSum(A, N), runNumber(A, N));
}

int main() {
    srand(time(NULL));

    test("Возрастающий", fillInc);
    test("Убывающий", fillDec);
    test("Слчайный", fillRand);

    printf("%-4s | %-12s | %-20s | %-24s\n", "N", "Теоритические", "Классик. M+C", "Улучшенный M+C");
    printf("     | M+C          | Возр    Случ   Убыв    | Возр    Случ   Убыв\n");
    printf("----------------------------------------------------------------\n");
        
    int testSizes[] = {10, 100};
    for (int s = 0; s < 2; s++) {
        int n = testSizes[s];
        int theory = (3 * (n - 1)) + (n * (n - 1) / 2);
        int res[2][3];
        void (*fills[])(int[], int) = {fillInc, fillRand, fillDec};

        for (int f = 0; f < 3; f++) {
            int *arr = (int*)malloc(n * sizeof(int));
            int m, c;

            fills[f](arr, n);
            selectSort(arr, n, &m, &c);
            res[0][f] = m + c;

            fills[f](arr, n); 
            selectSortUp(arr, n, &m, &c);
            res[1][f] = m + c;
            free(arr);
        }

        printf("%-4d | %-12d | %-6d %-6d %-6d | %-6d %-6d %-6d\n", n, theory, res[0][0], res[0][1], res[0][2], res[1][0], res[1][1], res[1][2]);
    }

}