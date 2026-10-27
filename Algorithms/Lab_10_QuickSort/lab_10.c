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

void quickSort_I(int array[], int n, int l, int r, int *m, int *c, int depth, int *maxDepth) {
    if (depth > *maxDepth) *maxDepth = depth;

    int x = array[l];
    // int x = array[(l + r) / 2];
    int i = l, j = r;
    while (i <= j) {
        while (array[i] < x) { (*c)++; i++; }
        while (array[j] > x) { (*c)++; j--; }
        (*c)++;
        if (i <= j) {
            int tmp = array[i]; array[i] = array[j]; array[j] = tmp;
            (*m) += 3; i++; j--;
        }
    }
    if (l < j) quickSort_I(array, n, l, j, m, c, depth + 1, maxDepth);
    if (i < r) quickSort_I(array, n, i, r, m, c, depth + 1, maxDepth);
}

void quickSort_II(int array[], int n, int l, int r,  int *m, int *c, int depth, int *maxDepth) {
    while (l < r) {
        if (depth > *maxDepth) *maxDepth = depth;
        int x = array[l];
        // int x = array[(l + r) / 2];
        int i = l, j = r;
        while (i <= j) {
            while (array[i] < x) {(*c)++; i++;}
            while (array[j] > x) {(*c)++; j--;}
            (*c)++;
            if (i <= j) {
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
                (*m) += 3;
                i++;
                j--;
            }
        }
        if ((j - l) < (r - i)) {
            quickSort_II(array, n, l, j, m, c, depth + 1, maxDepth);
            l = i;
        } else {
            quickSort_II(array, n, i, r, m, c, depth + 1, maxDepth);
            r = j;
        }
    }
}

int main() {
    srand(time(NULL));

    printf("%-4s | %-22s \n", "N", "Quick I M+C");
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
            int m_f = 0, c_f = 0, maxD = 0;

            fills[f](arr, n); 
            quickSort_I(arr, n, 0, n - 1, &m_f, &c_f, 1, &maxD);
            res[0][f] = m_f + c_f;
            
            free(arr);
        }
        printf("%-6d %-6d %-7d |\n", 
               res[0][0], res[0][1], res[0][2]);
    }
    printf("\n");

    printf("%-4s | %-22s   | %-22s\n", "N", "Глубина Quick I M+C", "Глубина Quick II M+C");
    printf("     | Возр   Случ   Убыв    | Возр   Случ   Убыв\n");
    printf("-----------------------------------------------------\n");
        
    int testSizes_II[] = {100, 200, 300, 400, 500};
    for (int s = 0; s < 5; s++) {
        int n = testSizes_II[s];
        printf("%-4d | ", n);

        int res[2][3];
        void (*fills[])(int[], int) = {fillInc, fillRand, fillDec};

        for (int f = 0; f < 3; f++) {
            int *arr = (int*)malloc(n * sizeof(int));
            int m_f = 0, c_f = 0, maxD_I = 0, maxD_II = 0;

            fills[f](arr, n); 
            quickSort_I(arr, n, 0, n - 1, &m_f, &c_f, 1, &maxD_I);
            res[0][f] = maxD_I;

            fills[f](arr, n); 
            quickSort_II(arr, n, 0, n - 1, &m_f, &c_f, 1, &maxD_II);
            res[1][f] = maxD_II;
            
            free(arr);
        }
        printf("%-6d %-6d %-7d |%-6d %-6d %-7d\n", 
               res[0][0], res[0][1], res[0][2], res[1][0], res[1][1], res[1][2]);
    }
    printf("\n");

    return 0;
}
