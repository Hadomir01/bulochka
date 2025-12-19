#include <stdio.h>
#define SIZE 9

int check_rows(int sudoku[SIZE][SIZE]) {
    for (int x = 0; x<SIZE; x++) {
        for (int i = 0; i<SIZE-1; i++) {
            for (int j = i+1; j<SIZE; j++) {
                if (sudoku[x][i] == sudoku[x][j]) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int check_columns(int sudoku[SIZE][SIZE]) {
    for (int y = 0; y<SIZE; y++) {
        for (int i = 0; i<SIZE-1; i++) {
            for (int j = i+1; j<SIZE; j++) {
                if (sudoku[i][y] == sudoku[j][y]) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int check_squares(int sudoku[SIZE][SIZE]) {
    for (int start_i = 0; start_i < SIZE; start_i += 3) {
        for (int start_j = 0; start_j < SIZE; start_j += 3) {
            int tmp_arr[SIZE];
            int index = 0;
            
            for (int i = start_i; i < start_i + 3; i++) {
                for (int j = start_j; j < start_j + 3; j++) {
                    tmp_arr[index++] = sudoku[i][j];
                }
            }
            for (int a = 0; a < SIZE - 1; a++) {
                for (int b = a + 1; b < SIZE; b++) {
                    if (tmp_arr[a] == tmp_arr[b]) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void is_valid_sudoku(int sudoku[SIZE][SIZE]) {
    if (check_rows(sudoku) == 0 && check_columns(sudoku) == 0 && check_squares(sudoku) == 0) {
        printf("Данная матрица является решением судоку!\n");
    } else {
        printf("Данная матрица не является решением судоку!\n");
    }

}

int main() {
    int sudoku[SIZE][SIZE] = {
    {6, 3, 7, 2, 1, 4, 5, 8, 9},
    {5, 8, 9, 3, 7, 6, 1, 4, 2},
    {2, 1, 4, 5, 8, 9, 3, 7, 6},
    {7, 2, 5, 1, 4, 3, 9, 6, 8},
    {4, 9, 1, 8, 6, 2, 7, 5, 3},
    {3, 6, 8, 7, 9, 5, 4, 2, 1},
    {8, 7, 3, 6, 5, 1, 2, 9, 4},
    {1, 4, 6, 9, 2, 7, 8, 3, 5},
    {9, 5, 2, 4, 3, 8, 6, 1, 7}
    };
    is_valid_sudoku(sudoku);
}