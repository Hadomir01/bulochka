#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h> 

typedef struct room_0 {
    char name[50];
    int lvl;
    int code;
    int resolution;
} Room;

typedef struct node {
    Room* room;
    struct node *prev_up;   
    struct node *next_up;  
    struct node *prev_down;
    struct node *next_down; 
} Node;

Node* newRoom() {
    Node* new_room = (Node*)malloc(sizeof(Node));
    new_room->room = (Room*)malloc(sizeof(Room));

    new_room->prev_up = NULL;
    new_room->next_up = NULL;
    new_room->prev_down = NULL;
    new_room->next_down = NULL;

    return new_room;
}

void createList(Node** S, int n, int k) {
    Node* head_down = newRoom();

    Node* cur = head_down;
    for (int i = 1; i < n; i++) { // нижняя цепочка
        Node* room = newRoom();
        cur->next_down = room;
        room->prev_down = cur;
        cur = room;
    }

    Node* head_up = newRoom();
    cur = head_up;
    for (int i = n + 1; i < n + k; i++) { // верхняя цепочка
        Node* room = newRoom();
        cur->next_up = room;
        room->prev_up = cur;
        cur = room;
    }

    Node* tmp_up = head_up;
    Node* tmp_down = head_down;

    while (tmp_up != NULL && tmp_down != NULL) {
        tmp_up->next_down = tmp_down;
        tmp_down->next_up = tmp_up;

        tmp_up = tmp_up->next_up;
        tmp_down = tmp_down->next_down;
    }

    *S = head_up;
}

void fillRand(Node* head) {
    char *names_dungeons_room[] = {"Привал", "Сокровищница", "Комната с врагами", "Комната с боссом", "Комната-ловушка",
            "Быстрое перемещение", "Магазин"};
    Node* cur = head;

    while (cur) {
        int tmp1 = rand() % 7;
        strcpy(cur->room->name, names_dungeons_room[tmp1]);
        cur->room->lvl = rand() % 10;
        cur->room->code = 1000 + rand() % 9000;
        cur->room->resolution = 10 + rand() % 150;

        cur = cur->next_up;
    }

    if (head->next_down) {
        cur = head->next_down;
        while (cur) {
            int tmp1 = rand() % 7;
            strcpy(cur->room->name, names_dungeons_room[tmp1]);
            cur->room->lvl = rand() % 10;
            cur->room->code = 1000 + rand() % 9000;
            cur->room->resolution = 10 + rand() % 150;

            cur = cur->next_down;
        }
    }
}

void printRoom(Node* cur) {
    if (!cur) return;
    
    printf("============\n");
    printf("ТЫ ЗДЕСЬ:\n");
    printf("Комната: %s\n", cur->room->name);
    printf("Уровень: %d\n", cur->room->lvl);
    printf("Код: %d\n", cur->room->code);
    printf("Размер: %d\n", cur->room->resolution);
    printf("============\n\n");
}

void printDungeon(Node* head) {
    if (!head) return;
    
    printf("\n=== ВЕРХНЯЯ ЦЕПОЧКА  ===\n");
    Node* cur = head;
    int room_num = 1;
    while (cur) {
        printf("a_n+%d: %s: Ур. > %d | Код > %d | Размер > %d \n", 
               room_num++, cur->room->name, cur->room->lvl,
               cur->room->code, cur->room->resolution);
        cur = cur->next_up;
    }
    
    printf("\n=== НИЖНЯЯ ЦЕПОЧКА ===\n");
    if (head->next_down) {
        cur = head->next_down;
        room_num = 1;
        while (cur) {
            printf("a_%d: %s: Ур. > %d | Код > %d | Размер > %d \n", 
                   room_num++, cur->room->name, cur->room->lvl,
                   cur->room->code, cur->room->resolution);
            cur = cur->next_down;
        }
    }
}

int main() {
    srand(time(NULL));

    int n, k;
    printf("Сколько комнат создадим? (n) > ");
    scanf("%d", &n);
    printf("Сколько комнат создадим? (k) > ");
    scanf("%d", &k);

    if (n <= 0 || k <= 0) {
        printf("В подземелье нет комнат!\n");
        return 1;
    }

    Node* S = NULL;

    createList(&S, n, k);
    fillRand(S);
    printDungeon(S);

    Node* curPos = S;

    int is_up = 1;
    char choice;

    while (1) {
        printRoom(curPos);
        printf("W - вверх / A - налево / S - вниз / D - направо / Q - выйти\n");
        printf("Куда идем? > ");
        scanf(" %c", &choice);

        if (choice == 'Q' || choice == 'q') {
            break;
        }

        if (choice == 'D' || choice == 'd' || choice == '6') {
            Node* next = is_up ? curPos->next_up : curPos->next_down;
            if (next)  {
                curPos = next;
            } else {
                printf("Тупик! Вернуться в начало?? (y/n) > ");
                char start;
                scanf(" %c", &start);
                if (start == 'Y' || start == 'y') {
                    curPos = S;
                }
            }
        } 
        else if (choice == 'A' || choice == 'a' || choice == '4') {
            Node* prev = is_up ? curPos->prev_up : curPos->prev_down;
            if (prev) {
                curPos = prev;
            }
            else {
                printf("никак не пройти...\n");
            }
        }
        else if (choice == 'W' || choice == 'w' || choice == '8') {
            if (is_up) {
                printf("никак не пройти...\n");
            } else {
                if (curPos->next_up) {
                    curPos = curPos->next_up;
                    is_up = 1;
                } else if (curPos->prev_up) {
                    curPos = curPos->prev_up;
                    is_up = 1;
                } else {
                    printf("никак не пройти...\n");
                }
            }
        }
        else if (choice == 'S' || choice == 's' || choice == '2') {
            if (!is_up) {
                printf("никак не пройти...\n");
            } else {
                if (curPos->next_down) {
                    curPos = curPos->next_down;
                    is_up = 0;
                } else if (curPos->prev_down) {
                    curPos = curPos->prev_down;
                    is_up = 0;
                } else {
                    printf("никак не пройти...\n");
                }
            }
        }
        else {
            printf("Куда-куда?\n\n");
        }
    }
    return 0;
}