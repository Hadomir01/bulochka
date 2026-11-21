#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void fillInc(int array[], int n) {
    for (int i = 0; i < n; i++) array[i] = i + 1;
}

void fillDec(int array[], int n) {
    for (int i = 0; i < n; i++) array[i] = n - i;
}

void fillRand(int array[], int n) {
    for (int i = 0; i < n; i++) array[i] = rand() % 5000;
}

void buildPyramid(int array[], int l, int r, int *m, int *c) {
    int x = array[l];
    (*m)++;
    int i = l;

    while (1) {
        int j = 2 * i + 1;
        if (j > r) {
            break;
        }
        if (j + 1 <= r) {
            (*c)++;
            if (array[j + 1] <= array[j]) {
                j = j + 1;
            }
        }
        (*c)++;
        if (x <= array[j]) {
            break;
        }
        array[i] = array[j];
        (*m)++;
        i = j;
    }
    array[i] = x;
    (*m)++;
}

void buildPyramid_check(int array[], int n, int *m, int *c) {
    *m = 0, *c = 0;
    int L = (n / 2) - 1;
    while (L >= 0) {
        buildPyramid(array, L, n - 1, m, c);
        L = L - 1;
    }
}

void heapSort(int array[], int n, int *m, int *c) {
    *m = 0, *c = 0;
    int L = (n / 2) - 1;
    while (L >= 0) {
        buildPyramid(array, L, n - 1, m, c);
        L = L - 1;
    }
    int R = n - 1;
    while (R > 0) {
        int tmp = array[0];
        array[0] = array[R];
        array[R] = tmp;
        (*m) += 3;
        R = R - 1;
        buildPyramid(array, 0, R, m, c);
    }
}

int main() {
    srand(time(NULL));

    printf("%-4s | %-12s | %-22s  \n", "N", "M+C теор.", "M+C факт.");
    printf("     |           | Возр   Случ   Убыв   \n");
    printf("----------------------------------\n");
        
    int testSizes_P[] = {100, 200, 300, 400, 500};
    for (int s = 0; s < 5; s++) {
        int n = testSizes_P[s];
        int theory = 0;
        for (int L = n/2; L >=1; L--) {
            theory += (int) (log2((double) n / L) + 2) + (int) (2 * log2((double) n / L));
        }
        printf("%-4d | %-9d | ", n, theory);

        int res[2][3];
        void (*fills[])(int[], int) = {fillInc, fillRand, fillDec};

        for (int f = 0; f < 3; f++) {
            int *arr = (int*)malloc(n * sizeof(int));
            int m_f = 0, c_f = 0;

            fills[f](arr, n); 
            buildPyramid_check(arr, n, &m_f, &c_f);
            res[0][f] = m_f + c_f;
            
            free(arr);
        }
        printf("%-6d %-6d %-7d |\n", 
               res[0][0], res[0][1], res[0][2]);
    }
    printf("\n");

    printf("%-4s | %-22s \n", "N", "Heap M+C");
    printf("     | Возр   Случ   Убыв   \n");
    printf("----------------------------------\n");
        
    int testSizes[] = {100, 200, 300, 400, 500};
    for (int s = 0; s < 5; s++) {
        int n = testSizes[s];
        printf("%-4d | ", n);

        int res[2][3];
        void (*fills[])(int[], int) = {fillInc, fillRand, fillDec};

        for (int f = 0; f < 3; f++) {
            int *arr = (int*)malloc(n * sizeof(int));
            int m_f, c_f;

            fills[f](arr, n); 
            heapSort(arr, n, &m_f, &c_f);
            res[0][f] = m_f + c_f;
            
            free(arr);
        }
        printf("%-6d %-6d %-7d |\n", 
               res[0][0], res[0][1], res[0][2]);
    }
    printf("\n");

    return 0;
}
