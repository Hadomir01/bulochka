#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    struct Node* next;
    int data;
} Node;

typedef struct {
    Node* head;
    Node** tail; 
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

void freeList(Node* head) {
    while (head != NULL) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

Node* arrayToListInc(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    fillInc(arr, n);
    Node* head = createNode(arr[0]);
    Node* curr = head;
    for (int i = 1; i < n; i++) {
        curr->next = createNode(arr[i]);
        curr = curr->next;
    }
    free(arr);
    return head;
}

Node* arrayToListRand(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    fillRand(arr, n);
    Node* head = createNode(arr[0]);
    Node* curr = head;
    for (int i = 1; i < n; i++) {
        curr->next = createNode(arr[i]);
        curr = curr->next;
    }
    free(arr);
    return head;
}

Node* arrayToListDec(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    fillDec(arr, n);
    Node* head = createNode(arr[0]);
    Node* curr = head;
    for (int i = 1; i < n; i++) {
        curr->next = createNode(arr[i]);
        curr = curr->next;
    }
    free(arr);
    return head;
}

int getDigit(int data, int j) {
    int shift = (j - 1) * 8;
    return (data >> shift) & 0xFF;
}

Node* digitalSort(Node* S, int L, long long* m_f) {
    Queue Q[256];
    *m_f = 0;

    for (int j = 1; j <= L; j++) {
        for (int i = 0; i < 256; i++) {
            Q[i].head = NULL;
            Q[i].tail = &(Q[i].head);
        }

        Node* p = S;
        while (p != NULL) {
            int d = getDigit(p->data, j);
            *(Q[d].tail) = p;            
            Q[d].tail = &(p->next);      
            p = p->next;                 
            (*m_f)++;
        }

        Node** p_ptr = &S; 
        for (int i = 0; i < 256; i++) {
            if (Q[i].tail != &(Q[i].head)) {
                *p_ptr = Q[i].head; 
                p_ptr = Q[i].tail;  
            }
        }
        *p_ptr = NULL; 
    }
    return S;
}

int main() {
    srand(time(NULL));

    int testSizes[] = {100, 200, 300, 400, 500};
    int L_values[] = {2, 4};

    for (int l_idx = 0; l_idx < 2; l_idx++) {
        int L = L_values[l_idx];
        printf("Цифровая сортировка по байтам, L = %d\n", L);
        printf("%-4s | %-10s | %-21s \n", "N", "Теор. М", "Digital M_фактич.");
        printf("     |            | Возр   Случ   Убыв   \n");
        printf("-----------------------------------------\n");

        for (int s = 0; s < 5; s++) {
            int n = testSizes[s];
            
            long long theoryM = L * n; 
            printf("%-4d | %-10lld |", n, theoryM);

            long long res[3]; 
            Node* (*fills[])(int) = {arrayToListInc, arrayToListRand, arrayToListDec};

            for (int f = 0; f < 3; f++) {
                long long mf = 0;
                Node* head = fills[f](n); 
                head = digitalSort(head, L, &mf);
                
                // Если считать и распределение, и сборку (как в теории):
                res[f] = mf; 
                
                freeList(head); 
            }
            printf(" %-6lld %-6lld %-7lld |\n", res[0], res[1], res[2]);
        }
        printf("\n");
    }

    return 0;
}
