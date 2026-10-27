// AVL - tree 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define N 500

typedef struct vertex {
    int data;
    struct vertex* left;
    struct vertex* right;
    int balance;
} Vertex;

void generateArray(int array[N]) {
    bool used[1000] = { false };
    int count = 0;
    
    while (count < N) {
        int num = rand() % 1000;
        if (!used[num]) { 
            used[num] = true;
            array[count] = num;
            count++;
        }
    }
}

void LL_rotation(Vertex** p) {
    Vertex* q = (*p)->left;
    (*p)->balance = 0;
    q->balance = 0;
    (*p)->left = q->right;
    q->right = *p;
    *p = q;
}

void RR_rotation(Vertex** p) {
    Vertex* q = (*p)->right;
    (*p)->balance = 0;
    q->balance = 0;
    (*p)->right = q->left;
    q->left = *p;
    *p = q;
}

void LR_rotation(Vertex** p) {
    Vertex* q = (*p)->left;
    Vertex* r = q->right;
    if (r->balance < 0) {
        (*p)->balance = 1;
    } else {
        (*p)->balance = 0;
    }
    if (r->balance > 0) {
        q->balance = -1;
    } else {
        q->balance = 0;
    }
    r->balance = 0;
    q->right = r->left;
    (*p)->left = r->right;
    r->left = q;
    r->right = *p;
    *p = r;
}

void RL_rotation(Vertex** p) {
    Vertex* q = (*p)->right;
    Vertex* r = q->left;
    if (r->balance < 0) {
        (*p)->balance = -1;
    } else {
        (*p)->balance = 0;
    }
    if (r->balance > 0) {
        q->balance = 1;
    } else {
        q->balance = 0;
    }
    r->balance = 0;
    q->left = r->right;
    (*p)->right = r->left;
    r->right = q;
    r->left = *p;
    *p = r;
}

void add_To_AVL(int data, Vertex** p, bool* grow) {
    if (*p == NULL) {
        *p = (Vertex*)malloc(sizeof(Vertex));
        (*p)->data = data;
        (*p)->left = NULL;
        (*p)->right = NULL;            
        (*p)->balance = 0;
        *grow = true;

    } else if ((*p)->data > data) {
        add_To_AVL(data, &((*p)->left), grow);
        if (*grow == true) {
            if ((*p)->balance > 0) {
                (*p)->balance = 0;
                *grow = false;
            } else if ((*p)->balance == 0) {
                (*p)->balance = -1;
                *grow = true;
            } else {
                if ((*p)->left->balance < 0) {
                    LL_rotation(p);
                    *grow = false;
                } else {
                    LR_rotation(p);
                    *grow = false;
                }
            }
        }

    } else if ((*p)->data < data) {
        add_To_AVL(data, &((*p)->right), grow);
        if (*grow == true) {
            if ((*p)->balance < 0) {
                (*p)->balance = 0;
                *grow = false;
            } else if ((*p)->balance == 0) {
                (*p)->balance = 1;
                *grow = true;
            } else {
                if ((*p)->right->balance > 0) {
                    RR_rotation(p);
                    *grow = false;
                } else {
                    RL_rotation(p);
                    *grow = false;
                }
            }
        }
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
        p->balance = 0;
        p->left = PBST(L, m-1, array);
        p->right = PBST(m+1, R, array);
        return p;
    }
}

int treeToArray(Vertex* root, int* arr, int index) {
    if (root == NULL) return index;
    index = treeToArray(root->left, arr, index);
    arr[index++] = root->data;
    return treeToArray(root->right, arr, index);
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
    bool grow = false;

    for (int i = 0; i < N; i++) {
        add_To_AVL(arr[i], &root, &grow);
    }

    getRound_L_R(root);

    int unique_size = Size(root);
    int* sorted_arr = (int*)malloc(unique_size * sizeof(int));
    treeToArray(root, sorted_arr, 0);
    
    Vertex* root_isdp = PBST(0, unique_size - 1, sorted_arr);

    printf("+-----------+--------+--------------+--------+--------------+\n");
    printf("| n = %-5d | Размер | Контр. сумма | Высота | Средн.высота |\n", N);
    printf("+-----------+--------+--------------+--------+--------------+\n");
    printf("| ИСДП      | %-6d | %-12d | %-6d | %-12.2f |\n", 
           Size(root_isdp), Sum(root_isdp), Height(root_isdp), AveragePathLength(root_isdp));
    printf("+-----------+--------+--------------+--------+--------------+\n");
    printf("| АВЛ       | %-6d | %-12d | %-6d | %-12.2f |\n", 
           Size(root), Sum(root), Height(root), AveragePathLength(root));
    printf("+-----------+--------+--------------+--------+--------------+\n");


    free(sorted_arr);
    freeTree(root);
    freeTree(root_isdp);

    return 0;
}