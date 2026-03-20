#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

typedef struct room_0 {
    char name[50];
    int lvl;
    int code;
    int resolution;
} Room;

typedef struct node {
    Room* room;
    struct node *next;
    struct node *down;
} Node;

Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->room = (Room*)malloc(sizeof(Room));
    newNode->next = NULL;
    newNode->down = NULL;
    return newNode;
}

void fillNode(Node* node) {
    char *names_dungeons_room[] = {"Привал", "Сокровищница", "Комната с врагами", "Комната с боссом",
        "Комната-ловушка", "Быстрое перемещение", "Магазин"};
    strcpy(node->room->name, names_dungeons_room[rand() % 7]);
    node->room->lvl = rand() % 10 + 1;
    node->room->code = 1000 + rand() % 9000;
    node->room->resolution = 10 + rand() % 50;
}

void createDungeon(Node** S, int n, int k) {
    Node* head_down = createNode();
    fillNode(head_down);
    Node* cur = head_down;
    for (int i = 1; i < n; i++) {
        cur->next = createNode();
        fillNode(cur->next);
        cur = cur->next;
    }

    Node* head_up = createNode();
    fillNode(head_up);
    cur = head_up;
    for (int i = 1; i < k; i++) {
        cur->next = createNode();
        fillNode(cur->next);
        cur = cur->next;
    }

    Node* tmp_up = head_up;
    Node* tmp_down = head_down;

    while (tmp_up != NULL && tmp_down != NULL) {
        tmp_up->down = tmp_down;
        tmp_up = tmp_up->next;
        tmp_down = tmp_down->next;
    }

    *S = head_up; 
}

void printRoom(Node* cur) {
    if (!cur) return;
    printf("--- ВЫ НАХОДИТЕСЬ ЗДЕСЬ ---\n");
    printf("Комната: %s | Ур: %d | Код: %d | Разм: %d\n", 
           cur->room->name, cur->room->lvl, cur->room->code, cur->room->resolution);
    printf("---------------------------\n");
}

void printDungeon(Node* head) {
    if (!head) return;
    
    Node* cur;
    int room_num;

    printf("=== ВЕРХНЯЯ ЦЕПОЧКА  ===\n");
    cur = head;
    room_num = 1;
    while (cur) {
        printf("a_n+%d: %-15s | Ур: %d | Код: %d | Разм: %d\n", 
               room_num++, cur->room->name, cur->room->lvl,
               cur->room->code, cur->room->resolution);
        cur = cur->next; 
    }
    
    printf("=== НИЖНЯЯ ЦЕПОЧКА ===\n");
    if (head->down) {
        cur = head->down;
        room_num = 1;
        while (cur) {
            printf("a_%d:   %-15s | Ур: %d | Код: %d | Разм: %d\n", 
                   room_num++, cur->room->name, cur->room->lvl,
                   cur->room->code, cur->room->resolution);
            cur = cur->next;
        }
    }
}

int main() {
    srand(time(NULL));

    int n, k;
    printf("Кол-во комнат внизу (n): ");
    scanf("%d", &n);
    printf("Кол-во комнат наверху (k): ");
    scanf("%d", &k);

    if (n <= 0 || k <= 0) {
        return 1;
    }

    Node* S = NULL;
    createDungeon(&S, n, k);
    printDungeon(S);

    Node* curPos = S;
    char choice;

    while (1) {
        printRoom(curPos);
        printf("S - вниз / D - направо / Q - выйти\n");
        printf("Куда идем? > ");
        scanf(" %c", &choice);

        if (choice == 'q' || choice == 'Q') break;

        if ((choice == 'd' || choice == 'D')) {
            if (curPos->next) {
                curPos = curPos->next;
            } else {
                printf("Тупик. Вернуться в начало?(y/n) > ");
                char back;
                scanf(" %c", &back);
                
                if (back == 'y' || back == 'Y') {
                    curPos = S;
                }
            }
        } else if ((choice == 's' || choice == 'S')) {
            if (curPos->down) {
                curPos = curPos->down;
            } else {
                printf("Тупик. Вернуться в начало?(y/n) > ");
                char back;
                scanf(" %c", &back);
                
                if (back == 'y' || back == 'Y') {
                    curPos = S;
                }
            }
        } else if (choice == 'w' || choice == 'W') {
            printf("некая сила не позволяте пройти наверх\n");
        } else if (choice == 'a' || choice == 'A') {
            printf("не отступать!\n");
        } else {
            printf("Куда-куда??\n");
        }
    }
    return 0;
}
