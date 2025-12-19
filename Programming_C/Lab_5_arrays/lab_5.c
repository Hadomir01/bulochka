#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10

int main() {
    srand(time(NULL));
    int complex[N];
    int signal_energy;
    
    for (int s = 0; s<N; s++){
        complex[s] = rand()%65536-32768;
    }
    for (int n = 0, z = 0; n<N; n=n+2, z++) {
        printf("z[%d] = %d + %di\n", z, complex[n], complex[n+1]);
    }
    for (int x=0, signal_energy=0; x<N; x=x+2) {
        signal_energy = signal_energy + (complex[x]*complex[x]) + (complex[x+1]*complex[x+1]);
        if (x == N - 2) {
            printf("signal energy = %d\n", signal_energy);
        }
    }
    int max = complex[0];
    for (int k = 0; k<N; k=k+2){
        if (complex[k] > max) {
            max = complex[k];
        }
    }
    printf("Максимальное значение из вещественной части : %d\n", max);
}

void init_array(int n, int array[n]) {
    for (int i = 0; i<n; i++) {
        array[i] = rand()%100-50;
        printf("array[%d] = %d\n", i, array[i]); 
    }
}

int find_min(int min, int array[]) {
    min = array[0];
    int k_ind = 1;
    for (int k = 1, k_ind; k<N; k++) {
        if (array[k] < min) {
            min = array[k];
            k_ind = k;
        }
        if (k == N-1) {
            printf("%d\n", k_ind);
        }
    }
}

int sums(int array[]) {
    for (long int m = 0, sum=0, multp=1; m<N; m++) {
        if (m%2==0) {
            sum = sum + array[m];
        } else {
            multp = multp * array[m];
        }
        if (m==N-1) {
            printf("Сумма на четных позициях: %ld\n", sum);
            printf("Произведение на нечетных позициях: %ld\n", multp);
        }
    }
}

int main() { 
    int array[N];
    int new_array[N];

    srand(time(NULL));
    init_array(N, array);

    int min = array[0];
    find_min(min, array);

    for (int j = 0; j<N; j++) { 
        if (array[j] < 0) {
            array[j+1] = array[j+1]*10;
        } else {
            array[j] = array[j];
        }
        printf("new_array[%d] = %d\n", j, array[j]);
    }

    int new_min = array[0];
    find_min(new_min, array);

    sums(array);
}