#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define NAME_SIZE 16
#define MSG_SIZE 129
#define CLIENTS_COUNT 3
#define SERVERS_COUNT 2

typedef struct {
    char name[NAME_SIZE];
    char msg[MSG_SIZE];
} Message;

typedef struct {
    Message buff[10];
    int head;
    int tail;
    int count;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    bool is_run;
} FIFO_t;

FIFO_t* fifo_init() {
    FIFO_t *fifo = malloc(sizeof(FIFO_t));
    if (!fifo) return NULL;

    fifo->head = 0;
    fifo->tail = 0;
    fifo->count = 0;
    fifo->is_run = true;

    if (pthread_mutex_init(&fifo->lock, NULL) != 0) {
        free(fifo);
        return NULL;
    }
    if (pthread_cond_init(&fifo->cond, NULL) != 0) {
        pthread_mutex_destroy(&fifo->lock);
        free(fifo);
        return NULL;
    }
    return fifo;
}

void fifo_deinit(FIFO_t *fifo) {
    if (!fifo) return;

    pthread_mutex_destroy(&fifo->lock);
    pthread_cond_destroy(&fifo->cond);
    free(fifo);
}

int msgSend(FIFO_t *fifo, const char* msg, const char* name) {
    pthread_mutex_lock(&fifo->lock);
    while (fifo->count >= 10 && fifo->is_run) {
        printf(" > Очередь заполнена, ждем освобождения\n");
        pthread_cond_wait(&fifo->cond, &fifo->lock);
    }

    if (!fifo->is_run) {
        pthread_mutex_unlock(&fifo->lock);
        return -1;
    }

    strncpy(fifo->buff[fifo->tail].name, name, NAME_SIZE - 1);
    fifo->buff[fifo->tail].name[NAME_SIZE - 1] = '\0';

    strncpy(fifo->buff[fifo->tail].msg, msg, MSG_SIZE - 1);
    fifo->buff[fifo->tail].msg[MSG_SIZE - 1] = '\0';

    fifo->tail = (fifo->tail + 1) % 10;
    fifo->count++;

    pthread_cond_broadcast(&fifo->cond);
    pthread_mutex_unlock(&fifo->lock);
    
    int len = strlen(msg);

    return len;
}

int msgRecv(FIFO_t* fifo, char *msg, int bufsize) {
    pthread_mutex_lock(&fifo->lock);

    while (fifo->count == 0 && fifo->is_run) {
        printf(" > Очередь пуста, ждем сообщений\n");
        pthread_cond_wait(&fifo->cond, &fifo->lock);
    }

    if (!fifo->is_run && fifo->count == 0) {
        pthread_mutex_unlock(&fifo->lock);
        return -1;
    }

    snprintf(msg, bufsize, "[%s] %s", fifo->buff[fifo->head].name, fifo->buff[fifo->head].msg);
    int len = strlen(msg);

    fifo->head = (fifo->head + 1) % 10;
    fifo->count--;

    pthread_cond_broadcast(&fifo->cond);
    pthread_mutex_unlock(&fifo->lock);

    return len;
}

void* client(void *var) {
    FIFO_t* fifo = (FIFO_t*)var;
    
    static _Atomic int count = 0;
    char name[NAME_SIZE];
    snprintf(name, sizeof(name), "Клиент %d", ++count);

    const char* text[] = {"Hello world!", "Cup of tea", "Event Horizon", 
                          "System of A Down", "Programming", "Wewew", "First In First Out"};
    int text_num = 7;

    for (int i = 0; i < text_num; i++) {
        int random = rand() % text_num;
        if (msgSend(fifo, text[random], name) < 0) break;

        usleep((rand() % 1000000) + 100000);
    }

    printf(" > [%s] Закончил отправку\n", name);
    return NULL;
}

void* server(void* var) {
    void** vars = (void**)var;
    FIFO_t* fifo = (FIFO_t*)vars[0];
    int id = *(int*)vars[1];
    free(vars[1]);
    free(vars);
    char buff[256];

    while (1) {
        int len = msgRecv(fifo, buff, sizeof(buff));
        if (len <= 0) {
            break;
        }
        printf("[Сервер %d] Сообщение: %s\n", id, buff);
        usleep((rand() % 1000000) + 100000);
    }
    printf(" > [Сервер %d] Закончил работу\n", id);
    return NULL;
}

int main() {
    srand(time(NULL));

    FIFO_t* fifo = fifo_init();
    if (!fifo) return 1;

    pthread_t clients[CLIENTS_COUNT];
    pthread_t servers[SERVERS_COUNT];

    for (int i = 0; i < SERVERS_COUNT; i++) {
        void** vars = malloc(2 * sizeof(void*));
        vars[0] = fifo;
        int* id = malloc(sizeof(int));
        *id = i + 1;
        vars[1] = id;
        pthread_create(&servers[i], NULL, server, vars);
    }

    sleep(1);

    for (int i = 0; i < CLIENTS_COUNT; i++) {
        pthread_create(&clients[i], NULL, client, fifo);
    }

    for (int i = 0; i < CLIENTS_COUNT; i++) {
        pthread_join(clients[i], NULL);
    }

    printf(" > Клиенты закончили работу\n");

    while(fifo->count != 0) {
        usleep(100000);
    }

    if (pthread_mutex_lock(&fifo->lock) != 0) abort();
    fifo->is_run = false;
    if (pthread_cond_signal(&fifo->cond) != 0) abort();
    if (pthread_mutex_unlock(&fifo->lock) != 0) abort();

    for (int i = 0; i < SERVERS_COUNT; i++) {
        pthread_join(servers[i], NULL);
    }

    fifo_deinit(fifo);

    return 0;
}