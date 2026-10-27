#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    struct Node *next;
    int data;
} Node_t;

Node_t* createNode(int data) {
    Node_t* newNode = (Node_t*)malloc(sizeof(Node_t));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

Node_t* createStackInc(int n) {
    Node_t* head = NULL;
    for (int i = n; i >= 1; i--) {
        Node_t* newNode = createNode(i);
        newNode->next = head;
        head = newNode;
    }
    return head;
}

Node_t* createStackDec(int n) {
    Node_t* head = NULL;
    for (int i = 1; i <= n; i++) {
        Node_t* newNode = createNode(i);
        newNode->next = head;
        head = newNode;
    }
    return head;
}

Node_t* createStackRand(int n) {
    Node_t* head = NULL;
    for (int i = 0; i < n; i++) {
        Node_t* newNode = createNode(rand() % 100);
        newNode->next = head;
        head = newNode;
    }
    return head;
}

Node_t* createQueueInc(int n) {
    Node_t* head = createNode(1);
    Node_t* tail = head;
    for (int i = 2; i <= n; i++) {
        tail->next = createNode(i);
        tail = tail->next;
    }
    return head;
}

Node_t* createQueueDec(int n) {
    Node_t* head = createNode(n);
    Node_t* tail = head;
    for (int i = n-1; i >= 1; i--) {
        tail->next = createNode(i);
        tail = tail->next;
    }
    return head;
}

Node_t* createQueueRand(int n) {
    Node_t* head = createNode(rand() % 100);
    Node_t* tail = head;
    for (int i = 0; i < n; i++) {
        tail->next = createNode(rand() % 100);
        tail = tail->next;
    }
    return head;
}

void printList(Node_t* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int checkSum(Node_t* head) {
    int sum = 0;
    while (head) {
        sum += head->data;
        head = head->next;
    }
    return sum;
}

int countSeries(Node_t* head) {
    int count = 1;
    while (head->next) {
        if (head->next->data < head->data) {
            count++;
        }
        head = head->next;
    }
    return count;
}

Node_t* clearList(Node_t* head) {
    while (head) {
        Node_t* tmp = head;
        head = head->next;
        free(tmp);
    }
    return NULL;
}

void recPrint(Node_t* head) {
    if (!head) return;
    printf("%d ", head->data);
    recPrint(head->next);
}

void reverseRecPrint(Node_t* head) {
    if (!head) return;
    reverseRecPrint(head->next);
    printf("%d ", head->data);
}

int main() {
    srand(time(NULL));

    printf("Стек Inc. ");
    Node_t* stack_1 = createStackInc(10);
    printList(stack_1);
    printf("Сумма = %d, Серии = %d\n", checkSum(stack_1), countSeries(stack_1));

    printf("Стек Dec. ");
    Node_t* stack_2 = createStackDec(10);
    printList(stack_2);
    printf("Сумма = %d, Серии = %d\n", checkSum(stack_2), countSeries(stack_2));
    
    printf("Стек Rand. ");
    Node_t* stack_3 = createStackRand(10);
    printList(stack_3);
    printf("Сумма = %d, Серии = %d\n", checkSum(stack_3), countSeries(stack_3));

    printf("Очередь Inc. ");
    Node_t* queue_1 = createQueueInc(10);
    printList(queue_1);
    printf("Сумма = %d, Серии = %d\n", checkSum(queue_1), countSeries(queue_1));

    printf("Очередь Dec. ");
    Node_t* queue_2 = createQueueDec(10);
    printList(queue_2);
    printf("Сумма = %d, Серии = %d\n", checkSum(queue_2), countSeries(queue_2));
    
    printf("Очередь Rand. ");
    Node_t* queue_3 = createQueueRand(10);
    printList(queue_3);
    printf("Сумма = %d, Серии = %d\n", checkSum(queue_3), countSeries(queue_3));

    printf("Рекурсивный вывод: ");
    recPrint(stack_1);
    printf("\n");

    printf("Обратный рекурсивный вывод: ");
    reverseRecPrint(stack_1);
    printf("\n");

    stack_1 = clearList(stack_1);
    stack_2 = clearList(stack_2);
    stack_3 = clearList(stack_3);
    queue_1 = clearList(queue_1);
    queue_2 = clearList(queue_2);
    queue_3 = clearList(queue_3);

    return 0;
}