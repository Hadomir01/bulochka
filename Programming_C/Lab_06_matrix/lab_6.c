#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10

void create_mtx(int n, double matrix[N][N], double vector[N]) {
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            printf("Вводите элементы матрицы [%d][%d]> ", i, j);
            scanf("%lf", &matrix[i][j]);
        }
    } 
    for (int i = 0; i<n; i++) {
        printf("Вводите элементы вектора-столбца правых частей > ");
        scanf("%lf", &vector[i]);
    }
}

void replace_col(int n, double matrix[N][N], double vector[N], double new_mtx[N][N], int col) {
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            if (j == col) {
                new_mtx[i][j] = vector[i];
            } else {
                new_mtx[i][j] = matrix[i][j];
            }
        }
    }
}

void find_mtx_minor(int n, double matrix[N][N], int del_x, int del_y, double mtx_minor[N][N]) {
    int m_i = 0;
    int m_j = 0;

    for (int i = 0; i<n; i++) {
        if (i == del_x) {
            continue;
        }
        for (int j = 0; j<n; j++) {
            if (j == del_y) {
                continue;
            }
            mtx_minor[m_i][m_j] = matrix[i][j];
            m_j++;
        }
        m_i++;
    }
}

int find_det(int n, double matrix[N][N]) {
    double det = 0;

    if (n == 1) {
        det = matrix[0][0];
    } else if (n == 2) {
        det = matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
    } else {
        double mtx_minor[N][N];
        int znak = 1;

        for (int j = 0; j<n; j++) {
            find_mtx_minor(n, matrix, 0, j, mtx_minor);
            double det_minor = find_det(n-1, mtx_minor);
            det += znak*matrix[0][j]*det_minor;
            znak = -znak;
        }
    }
    return det;
}

int solve_clay(int n, double matrix[N][N], double vector[N], double result[N]) {
    int det_main_mtx = find_det(n, matrix);

    if (det_main_mtx == 0) {
        printf("СЛАУ не определенная: решений нет или их бесконечное множество!\n");
        return 0;
    }
    double repl_mtx[N][N];

    for (int i = 0; i<n; i++) {
        replace_col(n, matrix, vector, repl_mtx, i);
        double det_repl_mtx = find_det(n, repl_mtx);
        result[i] = det_repl_mtx / det_main_mtx;
    }
    return 1;
}

void init_result(int n,double result[N]) {
    printf("Решение СЛАУ:");
    for (int i = 0; i<n; i++) {
        printf("x%d = %1.2f\n", i+1, result[i]);
    }
}

void init_mtx(int n, double matrix[N][N], double vector[N]) {
    printf("Расширенная матрица:\n");
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            printf("%1.0f ", matrix[i][j]);
        }
        printf("| %1.0f\n", vector[i]);
    }
}


int main() {
    int n;
    double matrix[N][N];
    double vector[N];
    double result[N];

    printf("Размер матрицы > ");
    scanf("%d", &n);

    create_mtx(n, matrix, vector);

    init_mtx(n, matrix, vector);

    if (solve_clay(n, matrix, vector, result) == 1) {
        init_result(n, result);
    }
}