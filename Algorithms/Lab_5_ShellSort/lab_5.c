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

void insertSort(int array[], int n, int *M, int *C) {
    *M = 0; *C = 0;
    for (int i = 1; i < n; i++) {
        int tmp = array[i]; (*M)++;
        int j = i - 1;
        while (j >= 0) {
            (*C)++;
            if (tmp < array[j]) {
                array[j + 1] = array[j]; (*M)++;
                j--;
            } else break;
        }
        array[j + 1] = tmp; (*M)++;
    }
}

void shellSort(int array[], int n, int *M, int *C) {
    *M = 0; *C = 0;
    
    int m = (int)(log2(n)) - 1;
    if (m < 1) m = 1;
    
    int *steps = (int*)malloc(m * sizeof(int));
    steps[0] = 1;
    for (int i = 1; i < m; i++) {
        steps[i] = 2 * steps[i-1] + 1;
    }
    for (int k = m - 1; k >= 0; k--) {
        int h = steps[k]; 

        for (int i = h; i < n; i++) {
            int temp = array[i]; 
            (*M)++; 
            int j = i - h; 

            while (j >= 0) {
                if (temp < array[j]) { 
                    (*C)++;
                    array[j + h] = array[j]; 
                    (*M)++; 
                    j -= h; 
                } else {
                    break;
                }
            }
            array[j + h] = temp; 
            (*M)++;
        }
    }
    free(steps);
}

void printSteps(int n) {
    int m = (int)(log2(n)) - 1;
    if (m < 1) m = 1;
    
    int *steps = (int*)malloc(m * sizeof(int));
    steps[0] = 1;
    for (int i = 1; i < m; i++) {
        steps[i] = 2 * steps[i-1] + 1;
    }

    printf("{");
    for (int i = m - 1; i >= 0; i--) {
        printf("%d%s", steps[i], i == 0 ? "" : ",");
    }
    printf("}");
    free(steps);
}

int main() {
    srand(time(NULL));

    printf("%-4s | %-12s | %-22s | %-22s\n", "N", "Шаги", "Insert M+C", "Shell M+C");
    printf("     |              | Возр   Случ   Убыв   | Возр   Случ   Убыв\n");
    printf("--------------------------------------------------------------------------\n");
        
    int testSizes[] = {100, 200, 300, 400, 500};
    for (int s = 0; s < 5; s++) {
        int n = testSizes[s];
        
        printf("%-4d | ", n);
        printSteps(n);
        
        int m_val = (int)(log2(n)) - 1;
        if (m_val < 1) m_val = 1;
        int spaces = 12 - (m_val * 2); 
        for(int i=0; i<spaces; i++) printf(" ");
        printf(" | ");

        int res[2][3];
        void (*fills[])(int[], int) = {fillInc, fillRand, fillDec};

        for (int f = 0; f < 3; f++) {
            int *arr = (int*)malloc(n * sizeof(int));
            int m_f, c_f;

            fills[f](arr, n);
            insertSort(arr, n, &m_f, &c_f);
            res[0][f] = m_f + c_f;

            fills[f](arr, n); 
            shellSort(arr, n, &m_f, &c_f);
            res[1][f] = m_f + c_f;
            
            free(arr);
        }
        printf("%-6d %-6d %-7d | %-6d %-6d %-6d\n", 
               res[0][0], res[0][1], res[0][2], 
               res[1][0], res[1][1], res[1][2]);
    }
    printf("\n");

    return 0;
}
