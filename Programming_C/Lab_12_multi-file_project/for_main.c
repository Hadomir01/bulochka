#include "for_main.h"

void random_fill(Object array[], int arr_size) {
    char *names_cosmic_objects[] = {"Каллисто", "Титан", "Европа", "Ганимед", "Церера",
            "Седна", "Хаумея", "Макемаке", "Эрида", "Энцелад"};

    for (int i = 0; i < arr_size; i++) {
        int tmp1 = rand() % 10;
        strcpy(array[i].name, names_cosmic_objects[tmp1]);

        array[i].distance = rand() % 1024;

        array[i].weight = rand() % 4096;

        array[i].code = 1000 + rand() % 9000;
    }
}

void selectSort(Object array[], int arr_size) {
    int min;
    for (int i = 0; i<arr_size-1; i++) {
        min = i;
        for (int j = i+1; j< arr_size; j++) {
            if (array[j].code < array[min].code) {
                min = j;
            }
        }
        Object tmp = array[min];
        array[min] = array[i];
        array[i] = tmp;
    }
}

void measure_sort_time(int sizes[], int num_sizes) {
    printf("| Размер n\t | Время (мс)\t |Размер Kb |\n");
    printf("+-------------------------------------------+\n");
    for (int k = 0; k < num_sizes; k++) {
        int n = sizes[k];
        
        Object* array = (Object*)malloc(n * sizeof(Object));
        if (array == NULL) {
            printf("Ошибка выделения памяти для n=%d\n", n);
            continue;
        }
        
        int array_size = n * sizeof(Object);

        struct timeval tv1, tv2;

        random_fill(array, n);
                
        gettimeofday(&tv1, NULL);
        selectSort(array, n);
        gettimeofday(&tv2, NULL);
        
        long elapsed_usec = (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec);
        
        printf("|%d\t\t |%.4f\t |%d\t    |\n", n, elapsed_usec / 1000.0, array_size/1024);
        
        free(array);
    }
}

void print(Object array[], int arr_size) {
    printf("| %s\t | %s\t | %s| %s\t |\n", 
           "Код", "Название","Расстояние, км", "Масса, кг");
    printf("|________________________________________________________|\n");

    for (int i = 0; i < arr_size; i++) {
        printf("| %d\t | %s\t | %d * 10^6\t | %d * 10^27\t |\n",
               array[i].code,
               array[i].name,
               array[i].distance,
               array[i].weight);
    }
    printf("\n");
}