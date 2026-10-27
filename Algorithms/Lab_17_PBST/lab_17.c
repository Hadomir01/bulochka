// perfectly balanced search tree

#include <stdio.h>
#include <stdlib.h>
#define N 500

typedef struct vertex {
    int data;
    struct vertex* left;
    struct vertex* right;
} Vertex;

void generateArray(int array[N], int n) {
    for (int i = 0; i < N; i++) {
        array[i] = i+1;
    }
}

Vertex* PBST(int L, int R, int array[N]) {
    if (L > R) {
        return NULL;
    }
    else {
        int m = (L+R)/2;
        Vertex* p = (Vertex*)malloc(sizeof(Vertex));
        p->data = array[m];
        p->left = PBST(L, m-1, array);
        p->right = PBST(m+1, R, array);
        return p;
    }
}

void getRound_L_R(Vertex *root) {
    if (root == NULL) return;
    
    getRound_L_R(root->left);
    printf("%d ", root->data);
    getRound_L_R(root->right);
}

int Size(Vertex* root) {
    if (root == NULL) { return 0; }
    else {
        return 1 + Size(root->left) + Size(root->right);
    }
}

int Sum(Vertex* root) {
    if (root == NULL) { return 0; }
    else {
        return root->data + Sum(root->left) + Sum(root->right);
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int Height(Vertex* root) {
    if (root == NULL) { return 0; }
    else {
        return 1 + max(Height(root->left), Height(root->right));
    }
}

int TotalPathLength(Vertex* root, int current_depth) {
    if (root == NULL) {
        return 0;
    }
    return current_depth + 
           TotalPathLength(root->left, current_depth + 1) + 
           TotalPathLength(root->right, current_depth + 1);
}

double AveragePathLength(Vertex* root) {
    int size = Size(root);
    if (size == 0) {
        return 0.0;
    }
    
    int total_depth = TotalPathLength(root, 1);
    
    return (double)total_depth / size;
}

void Search(Vertex* root, int key) {
    Vertex* p = root;
    while (p != NULL) {
        if (key < p->data) {
            p = p->left;
        } else if (key > p->data) {
            p = p->right;
        } else {
            break;
        }
    }
    if (p != NULL) {
        printf("Найдено: %d\n", p->data);
    } else {
        printf("Не найдено!\n");
    }
}

void Search_Recursion(Vertex* root, int key) {
    if (root == NULL) {
        printf("Не найдено!\n");
        return; 
    }
    if (key == root->data) {
        printf("Найдено: %d\n", root->data);
        return;
    }
    if (key < root->data) {
        Search_Recursion(root->left, key);
    } else if (key > root->data) {
        Search_Recursion(root->right, key);
    }
}

void Results(Vertex* root) {
    printf("Размер дерева: %d\n", Size(root));
    printf("Контрольная сумма: %d\n", Sum(root));
    
    printf("Высота дерева: %d\n", Height(root));
    printf("Средняя длина : %.2f\n", AveragePathLength(root));
}

void freeTree(Vertex* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    int arr[N];
    generateArray(arr, N);
    
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    Vertex* root = PBST(0, N-1, arr);

    getRound_L_R(root);
    printf("\n");

    Results(root);
    printf("\n");

    int key;
    printf("Введите ключ поиска >> ");
    scanf("%d", &key);

    printf("Обычный поиск: ");
    Search(root, key);

    printf("Рекурсивный поиск: ");
    Search_Recursion(root, key);

    freeTree(root);
}