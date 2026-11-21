#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int create_mtx(int n, int** matrix) {
    srand(time(NULL));

    for (int i = 0; i<n; i++) {
        matrix[i] = malloc(n*sizeof(int));
        for (int j = 0; j<n; j++) {
            matrix[i][j] = rand() % 10;
        }
    }

    printf("Матрица A:\n");
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return **matrix;
}

double arithmetic_mean(int n, int** matrix) {
    int tmp_arr[n*n];
    int index = 0;
    int sum = 0;
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            tmp_arr[index++] = matrix[i][j];
        }
    }
    for (int i = 0; i<n*n; i++) {
        sum = sum + tmp_arr[i];
    }
    double arit_mean = (double)sum / (n * n);
    return arit_mean;
}

int create_arr(int n, int** matrix, int* arr){
    int index = 0;
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            if (j > i && j < n - i - 1) {
                arr[index++] = matrix[i][j];
            }
        }
    }

    printf("Массив B: ");
    for (int i = 0; i < index; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return index;
}

int main_diagonal(int n, int** matrix, int** new_mtx) {
    int tmp[n];
    for (int i = 0; i<n; i++) {
        tmp[i] = matrix[i][i];
    }

    printf("Главная даигональ: ");
    for (int i = 0; i<n; i++) {
        printf("%d ", tmp[i]);
    }
    printf("\n");

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tmp[j] > tmp[j + 1]) {
                int temp = tmp[j];
                tmp[j] = tmp[j + 1];
                tmp[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i<n; i++) {
        new_mtx[i] = malloc(n*sizeof(int));
        for (int j = 0; j<n; j++) {
            if (i == j) {
                new_mtx[i][i] = tmp[i];
            } else {
                new_mtx[i][j] = matrix[i][j];
            }
        }
    }
    
    printf("Новая матрица С:\n");
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            printf("%d ", new_mtx[i][j]);
        }
        printf("\n");
    }
}

void result(int n, int** matrix, int* arr, int** new_mtx) {
    int count = 0;
    double a = arithmetic_mean(n, matrix);
    int len = create_arr(n, matrix, arr);

    for (int i = 0; i<len; i++) {
        if (arr[i] < a) {
            count+=1;
        }
    }

    printf("Среднее арифметическое: %.1f\n", a);
    printf("Элементов массива, меньше среднего значения элементов матрицы: %d\n", count);
    main_diagonal(n, matrix, new_mtx);
}

void free_memory(int n, int** matrix, int* arr, int** new_mtx) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    free(arr);
    
    for (int i = 0; i < n; i++) {
            free(new_mtx[i]);
        }
    free(new_mtx);
}

int main() {
    int n;
    printf("Введите размер матрицы > ");
    scanf("%d", &n);
    int** A = malloc(n*sizeof(*A));
    int* B = malloc(n*sizeof(B));
    int** C = malloc(n*sizeof(*C));

    create_mtx(n, A);
    result(n, A, B, C);
    free_memory(n, A, B, C);
    
}