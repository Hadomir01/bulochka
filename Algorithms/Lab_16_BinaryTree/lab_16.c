// binary tree

#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
    int data;
    struct vertex *left;
    struct vertex *right;
} Vertex;

void Obhod1(Vertex *root) {
    if (root == NULL) return;

    printf("%d ", root->data);
    Obhod1(root->left);
    Obhod1(root->right); 
}

void Obhod2(Vertex *root) {
    if (root == NULL) return;
    
    Obhod2(root->left);
    printf("%d ", root->data);
    Obhod2(root->right);
}

void Obhod3(Vertex *root) {
    if (root == NULL) return;
    
    Obhod3(root->left);
    Obhod3(root->right);
    printf("%d ", root->data);
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

int main() {
    Vertex *root;
    int n_size;
    
    root = (Vertex*)malloc(sizeof(Vertex));
    root->data = 1;
    
    root->left = (Vertex*)malloc(sizeof(Vertex));
    root->left->data = 2;
    
    root->right = (Vertex*)malloc(sizeof(Vertex));
    root->right->data = 3;
    root->right->right = NULL;

    root->right->left = (Vertex*)malloc(sizeof(Vertex));
    root->right->left->data = 7;
    root->right->left->left = NULL;
    root->right->left->right = NULL;
    
    root->left->left = (Vertex*)malloc(sizeof(Vertex));
    root->left->left->data = 4;
    
    root->left->left->left = (Vertex*)malloc(sizeof(Vertex));
    root->left->left->left->data = 5;
    root->left->left->left->left = NULL;
    root->left->left->left->right = NULL;
    
    root->left->left->right = (Vertex*)malloc(sizeof(Vertex));
    root->left->left->right->data = 6;
    root->left->left->right->left = NULL;
    root->left->left->right->right = NULL;

    printf("Обход Сверху вниз: ");
    Obhod1(root);
    printf("\n");

    printf("Обход Слева направо: ");
    Obhod2(root);
    printf("\n");
    
    printf("Обход Снизу вверх: ");
    Obhod3(root);
    printf("\n");

    printf("===================================\n");

    printf("Размер дерева: %d\n", Size(root));
    printf("Контрольная сумма: %d\n", Sum(root));
    
    printf("Высота дерева: %d\n", Height(root));
    printf("Средняя длина : %f\n", AveragePathLength(root));

    return 0;
}
