// randomly search tree

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define N 100

typedef struct vertex {
    int data;
    struct vertex* left;
    struct vertex* right;
} Vertex;

void generateArray(int array[N]) {
    bool used[5000] = { false };
    int count = 0;
    
    while (count < N) {
        int num = rand() % 10000;
        if (!used[num]) { 
            used[num] = true;
            array[count] = num;
            count++;
        }
    }
}

void RST_doublePointer(int data, Vertex** Root) {
    Vertex** p = Root;
    
    while (*p != NULL) {
        if (data < (*p)->data) {
            p = &((*p)->left);
        } else if (data > (*p)->data) {
            p = &((*p)->right);
        } else {
            return;
        }
    }

    *p = (Vertex*)malloc(sizeof(Vertex));
    if (*p != NULL) {
        (*p)->data = data;
        (*p)->left = NULL;
        (*p)->right = NULL;
    }
}

Vertex* RST_recursion(int data, Vertex* p) {
    if (p == NULL) {
        Vertex* new_node = (Vertex*)malloc(sizeof(Vertex));
        if (new_node != NULL) {
            new_node->data = data;
            new_node->left = NULL;
            new_node->right = NULL;
        }
        return new_node;
    } 
    
    if (data < p->data) {
        p->left = RST_recursion(data, p->left);
    } else if (data > p->data) {
        p->right = RST_recursion(data, p->right);
    }
    
    return p;
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

void getRound_L_R(Vertex *root) {
    if (root == NULL) return;
    
    getRound_L_R(root->left);
    printf("%d ", root->data);
    getRound_L_R(root->right);
}

void freeTree(Vertex* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int treeToArray(Vertex* root, int* arr, int index) {
    if (root == NULL) return index;
    index = treeToArray(root->left, arr, index);
    arr[index++] = root->data;
    return treeToArray(root->right, arr, index);
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

int main() {
    srand(time(NULL));
    
    int arr[N];
    generateArray(arr);
    
    printf("Исходный массив:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    Vertex* root_1 = NULL; 
    Vertex* root_2 = NULL; 

    for (int i = 0; i < N; i++) {
        RST_doublePointer(arr[i], &root_1);
        root_2 = RST_recursion(arr[i], root_2); 
    }

    // printf("Дерево (двойной указатель) (Обход ->): ");
    // getRound_L_R(root_1);
    // printf("\n\n");

    // printf("Дерево (рекурсия) (Обход ->): ");
    // getRound_L_R(root_2);
    // printf("\n\n");

    int unique_size = Size(root_1);
    int* sorted_arr = (int*)malloc(unique_size * sizeof(int));
    treeToArray(root_1, sorted_arr, 0);
    
    Vertex* root_isdp = PBST(0, unique_size - 1, sorted_arr);

    printf("+-----------+--------+--------------+--------+--------------+\n");
    printf("| n = %-5d | Размер | Контр. сумма | Высота | Средн.высота |\n", N);
    printf("+-----------+--------+--------------+--------+--------------+\n");
    printf("| ИСДП      | %-6d | %-12d | %-6d | %-12.2f |\n", 
           Size(root_isdp), Sum(root_isdp), Height(root_isdp), AveragePathLength(root_isdp));
    printf("+-----------+--------+--------------+--------+--------------+\n");
    printf("| СДП1      | %-6d | %-12d | %-6d | %-12.2f |\n", 
           Size(root_1), Sum(root_1), Height(root_1), AveragePathLength(root_1));
    printf("+-----------+--------+--------------+--------+--------------+\n");
    printf("| СДП2      | %-6d | %-12d | %-6d | %-12.2f |\n", 
           Size(root_2), Sum(root_2), Height(root_2), AveragePathLength(root_2));
    printf("+-----------+--------+--------------+--------+--------------+\n");

    free(sorted_arr);
    freeTree(root_1);
    freeTree(root_2);
    freeTree(root_isdp);

    return 0;
}
