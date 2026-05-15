#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

struct data {
    pthread_t tid;
    int n;
    int start;
    int end;
    int *A;
    int *B;
    int *C;
};

void* matrix_multiplication(void *var) {
    struct data *tdata = (struct data*)var;
    int n = tdata->n;
    int *A = tdata->A;
    int *B = tdata->B;
    int *C = tdata->C;

    for (int i = tdata->start; i < tdata->end; i++) {
        for (int j = 0; j < n; j++) {
            int scalar = 0;
            for (int k = 0; k < n; k++) {
                scalar += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = scalar;
        }
    }
    return NULL;
}

void print_matrix(int n, int *A) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", A[i * n + j]);
        }
        printf("\n");
    }
}

int main() {
    int thread_counts[] = {1, 2, 4, 8, 16, 32, 64, 128};
    
    int num_threads = sizeof(thread_counts) / sizeof(thread_counts[0]);
    
    FILE *output = fopen("test_results.csv", "w");
    if (!output) {
        printf("Ошибка создания файла!\n");
        return 1;
    }
    
    fprintf(output, "MatrixSize,Threads,Time_ms\n");
    
    for (int s = 100; s < 2500; s = s + 100) {
        int n = s;
        
        int *matrix_A = malloc(n * n * sizeof(int));
        int *matrix_B = malloc(n * n * sizeof(int));
        int *matrix_C = malloc(n * n * sizeof(int));

        for (int i = 0; i < n * n; i++) {
            matrix_A[i] = 1;
            matrix_B[i] = 1;
        }
        
        for (int t = 0; t < num_threads; t++) {
            int threads = thread_counts[t];
            
            if (threads > n) {
                fprintf(output, "%d,%d,SKIP\n", n, threads);
                continue;
            }
            
            int rows_per_thread = n / threads;
            int remain = n % threads;
            
            struct data *tdata = malloc(threads * sizeof(struct data));
            
            struct timeval start_time, end_time;
            gettimeofday(&start_time, NULL);
            
            for (int i = 0; i < threads; i++) {
                tdata[i].n = n;
                tdata[i].start = i * rows_per_thread;
                tdata[i].end = tdata[i].start + rows_per_thread;
                tdata[i].A = matrix_A;
                tdata[i].B = matrix_B;
                tdata[i].C = matrix_C;
                pthread_create(&tdata[i].tid, NULL, matrix_multiplication, &tdata[i]);
            }
            
            if (remain > 0) {
                int remain_start = threads * rows_per_thread;
                int remain_end = remain_start + remain;
                
                for (int i = remain_start; i < remain_end; i++) {
                    for (int j = 0; j < n; j++) {
                        int scalar = 0;
                        for (int k = 0; k < n; k++) {
                            scalar += matrix_A[i * n + k] * matrix_B[k * n + j];
                        }
                        matrix_C[i * n + j] = scalar;
                    }
                }
            }
            
            for (int i = 0; i < threads; i++) {
                pthread_join(tdata[i].tid, NULL);
            }
            
            gettimeofday(&end_time, NULL);
            
            long seconds = end_time.tv_sec - start_time.tv_sec;
            long micros = seconds * 1000000 + (end_time.tv_usec - start_time.tv_usec);
            double ms = micros / 1000.0;
            
            fprintf(output, "%d,%d,%.2f\n", n, threads, ms);
            printf("Матрица %dx%d, потоков: %d -> %.2f мс\n", n, n, threads, ms);
            
            free(tdata);
        }
        
        free(matrix_A);
        free(matrix_B);
        free(matrix_C);
        printf("---\n");
    }
    
    fclose(output);
    
    return 0;
}