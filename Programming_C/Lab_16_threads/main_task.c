#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int parent_turn = 1;

void AtExit(void *var) {
    printf("Поток завершен\n");
}

void *routine(void *var) {
    char** text = var;
    pthread_cleanup_push(AtExit, text[0]);

    for (int i = 0; i < 4; i++) {
        pthread_mutex_lock(&mutex);

        while (parent_turn != 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("%s \n", text[i]);
        parent_turn = 1;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex); 

    }

    pthread_cleanup_pop(1);
    return NULL;
}

int main() {
    pthread_t tid;

    // char* strings[4][4] = {{"Поток 1", "Бумага", "Камень", "Ножницы"},
    //                      {"Поток 2", "Чай", "Печенька", "Сгущенка"},
    //                      {"Поток 3", "Ключ", "Замок", "Код"},
    //                      {"Поток 4", "Лыжи", "Винтовка", "Трасса"}};


    // for (int i = 0; i < 4; i++) {
    //     pthread_create(&tid[i], NULL, routine, strings[i]);
    // }
    char* string_arr[] = {"Булочка", "Печенька", "Сметанка", "Блинчики", "Чай"};
    pthread_create(&tid, NULL, routine, string_arr);

    for (int i = 0; i < 4; i++) {
        pthread_mutex_lock(&mutex);

        while (parent_turn != 1) {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("Родительский поток: %d\n", i+1);
        parent_turn = 0;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex); 

    }

    pthread_join(tid, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    // for (int i = 0; i < 4; i++) {
    //     pthread_cancel(tid[i]);
    //     pthread_join(tid[i], NULL);
    //     printf("Прервано: %d поток\n", i + 1);
    // }
    
    return 0;
}
