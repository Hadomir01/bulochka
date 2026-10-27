// delete from randomly search tree

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define N 10

typedef struct vertex {
    int data;
    struct vertex* left;
    struct vertex* right;
} Vertex;

void generateArray(int array[N]) {
    bool used[10] = { false };
    int count = 0;
    
    while (count < N) {
        int num = rand() % 10;
        if (!used[num]) { 
            used[num] = true;
            array[count] = num;
            count++;
        }
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

void getRound_L_R(Vertex *root) {
    if (root == NULL) return;
    
    getRound_L_R(root->left);
    printf("%d ", root->data);
    getRound_L_R(root->right);
}

void DeleteVertex(int data, Vertex **root) {
    Vertex **p = root;
    Vertex *q, *r, *s;

    while (*p != NULL) {
        if (data < (*p)->data) {
            p = &((*p)->left);
        } else if (data > (*p)->data) {
            p = &((*p)->right);
        } else {
            break;
        }
    }

    if (*p != NULL) {
        q = *p;
        if (q->left == NULL) {
            *p = q->right;
        } else if (q->right == NULL) {
            *p = q->left;
        } else {
            r = q->left, s = q;
            if (r->right == NULL) {
            r->right = q->right;
            *p = r;
        } else {
            while (r->right != NULL) {
                s = r, r = r->right;
            }
            s->right = r->left;
            r->left = q->left;
            r->right = q->right;
            *p = r;
            }
        } 
    }
    free(q);
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


int main() {
    srand(time(NULL));
    
    int arr[N];
    generateArray(arr);
    
    printf("Исходный массив:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    Vertex* root = NULL; 
    for (int i = 0; i < N; i++) {
        root = RST_recursion(arr[i], root); 
    }

    printf("Обход дерева перед удалением (->): ");
    getRound_L_R(root);
    printf("\n\n");

    for (int i = 0; i < N; i++) {
        DeleteVertex(arr[i], &root);
        printf("Обход дерева после удаления вершины [%d] (->): ", arr[i]);
        getRound_L_R(root);
        printf("\n\n");
    }

    freeTree(root);

    return 0;
}
