#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Node {
    struct Node* next;
    int data;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} Queue;

void fillInc(int array[], int n) {
    for (int i = 0; i < n; i++) array[i] = i + 1;
}

void fillDec(int array[], int n) {
    for (int i = 0; i < n; i++) array[i] = n - i;
}

void fillRand(int array[], int n) {
    for (int i = 0; i < n; i++) array[i] = rand() % 5000;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enqueue(Queue* q, Node* node) {
    node->next = NULL;
    if (q->head == NULL) {
        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }
}

Node* dequeue(Node** list) {
    if (*list == NULL) {
        return NULL;
    }
    Node* node = *list;
    *list = (*list)->next;
    node->next = NULL;
    return node;
}

void initQueue(Queue* q) {
    q->head = NULL;
    q->tail = NULL;
}

Node* createList(int array[], int n) {
    Node* head = createNode(array[0]);
    Node* curr = head;
    for (int i = 1; i < n; i++) {
        curr->next = createNode(array[i]);
        curr = curr->next;
    }
    return head;
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

void splitList(Node* S, Node** a, Node** b, int* n, int* mv) {
    *a = S;
    *b = S->next;
    Node* k = *a;
    Node* p = *b;
    *n = 1;

    while (p != NULL) {
        (*n)++;
        k->next = p->next;
        k = p;
        p = p->next;
        (*mv)++;
    }
}

void merge(Node** a, Node** b, int q, int r, Queue* C, int* c, int* mv) {
    int q_new = q, r_new = r;

    while (q_new != 0 && r_new != 0) {
        (*c)++;
        if ((*a)->data <= (*b)->data) {
            enqueue(C, dequeue(a));
            (*mv)++;
            q_new--;
        } else {
            enqueue(C, dequeue(b));
            (*mv)++;
            r_new--;
        }
    }
    while (q_new > 0) {
        enqueue(C, dequeue(a));
        (*mv)++;
        q_new--;
    }
    while (r_new > 0) {
        enqueue(C, dequeue(b));
        (*mv)++;
        r_new--;
    }
}

Node* mergeSort(Node* S, int* size, int* c, int* mv) {
    Node* a = NULL, *b = NULL;
    int n = 0;

    splitList(S, &a, &b, &n, mv);
    *size = n;

    int p = 1;
    Queue C[2];
    int i;

    while (p < n) {
        initQueue(&C[0]);
        initQueue(&C[1]);
        i = 0;
        int m = n;

        while (m > 0) {
            int q = (m >= p) ? p : m;
            m = m - q;
            int r = (m >= p) ? p : m;
            m = m - r;

            merge(&a, &b, q, r, &C[i], c, mv);
            i = 1 - i;
        }

        a = C[0].head;
        b = C[1].head;
        p = p*2;
    }
    C[0].tail->next = NULL;
    return C[0].head;
}

void mergeSortArray(int arr[], int n, int* c, int* m) {
    *c = 0;
    *m = 0;
    
    Node* list = createList(arr, n);
    int size;
    
    list = mergeSort(list, &size, c, m);
    freeList(list);
}

int main() {
    srand(time(NULL));

    printf("%-4s | %-10s | %-21s \n", "N", "Теор.", "Merge M+C");
    printf("     |        | Возр   Случ   Убыв   \n");
    printf("----------------------------------\n");
        
    int testSizes[] = {100, 200, 300, 400, 500};
    for (int s = 0; s < 5; s++) {
        int n = testSizes[s];
        int theory = 2* n * log2(n) + n;
        printf("%-4d | %-6d |", n, theory);

        int res[2][3];
        void (*fills[])(int[], int) = {fillInc, fillRand, fillDec};

        for (int f = 0; f < 3; f++) {
            int* arr = (int*)malloc(n * sizeof(int));
            int m_f = 0, c_f = 0;

            fills[f](arr, n); 
            mergeSortArray(arr, n, &c_f, &m_f);
            res[0][f] = m_f + c_f;
            
            free(arr);
        }
        printf(" %-6d %-6d %-7d |\n", 
               res[0][0], res[0][1], res[0][2]);
    }
    printf("\n");

    return 0;
}
