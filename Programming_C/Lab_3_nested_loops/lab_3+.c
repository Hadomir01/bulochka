#include <stdio.h>

void create_spiral(int n, int layer, int spiral[n][n], int num){
    
    for (int i = 0; i<layer; i++) {
        for (int j = i; j<n-i; j++) {
            spiral[i][j] = num;
            num = num + 1;
        }

        for (int j = i+1; j<n-i; j++) {
            spiral[j][n-i-1] = num;
            num = num + 1;
        }

        for (int j = n-i-2; j>=i; j--) {
            spiral[n-1-i][j] = num;
            num = num + 1;
        }

        for (int j = n-2-i; j>i; j--) {
            spiral[j][i] = num;
            num = num + 1;
        }
    }
}

int main() {
    int n;
    printf("Введите размер матрицы-спирали > ");
    scanf("%d", &n);

    int spiral[n][n];
    int num = 1;
    int layer = (n+1)/2;

    create_spiral(n, layer, spiral, num);

    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++) {
            printf("%2d ", spiral[i][j]);
        }
        printf("\n");
    }
}