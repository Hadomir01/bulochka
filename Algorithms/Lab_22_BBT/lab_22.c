// Binary Bayer's tree

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define N 100
#define MAXVAL 1000

typedef struct vertex {
    int data;
    struct vertex* left;
    struct vertex* right;
    int balance;
} Vertex;

void generateArray(int array[N]) {
    bool used[MAXVAL] = { false };
    int count = 0;
    
    while (count < N) {
        int num = rand() % MAXVAL;
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
    if (r->balance > 0) {
        (*p)->balance = -1;
    } else {
        (*p)->balance = 0;
    }
    if (r->balance < 0) {
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

void add_to_BBT(int data, Vertex** p, int* horizon, int* vertical) {
    if (*p == NULL) {
        *p = (Vertex*)malloc(sizeof(Vertex));
        (*p)->data = data;
        (*p)->left = NULL;
        (*p)->right = NULL;            
        (*p)->balance = 0;
        *vertical = 1;
        *horizon = 0;
    } else if ((*p)->data > data) {
        add_to_BBT(data, &((*p)->left), horizon, vertical);
        if (*vertical == 1) {
            if ((*p)->balance == 0) {
                Vertex* q = (*p)->left;
                (*p)->left = q->right;
                q->right = *p;
                *p = q;
                (*p)->balance = 1;
                *vertical = 0;
                *horizon = 1;
            } else {
                (*p)->balance = 0;
                *vertical = 1;
                *horizon = 0;
            }
        } else {
            *horizon = 0;
        }
    } else if ((*p)->data < data) {
        add_to_BBT(data, &((*p)->right), horizon, vertical);
        if (*vertical == 1) {
            (*p)->balance = 1;
            *horizon = 1;
            *vertical = 0;
        } else if (*horizon == 1) {
            if ((*p)->balance == 1) {
                Vertex* q = (*p)->right;
                (*p)->balance = 0;
                q->balance = 0;
                (*p)->right = q->left;
                q->left = *p;
                *p = q;
                *vertical = 1;
                *horizon = 0;
            } else {
                *horizon = 0;
            }
        }
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

int HeightBBT(Vertex* root) {
    int h = 0;
    while (root != NULL) {
        h++;
        root = root->left;
    }
    return h;
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

    Vertex* root_AVL = NULL;
    bool grow = false;

    for (int i = 0; i < N; i++) {
        add_To_AVL(arr[i], &root_AVL, &grow);
    }

    Vertex* root_BBT = NULL;
    int hor = 1; 
    int ver = 1;

    for (int i = 0; i < N; i++) {
        add_to_BBT(arr[i], &root_BBT, &hor, &ver);
    }

    printf("АВЛ (обход слева направо):\n");
    getRound_L_R(root_AVL);
    printf("\n\nДБД (обход слева направо):\n");
    getRound_L_R(root_BBT);
    printf("\n\n");

    printf("+-----------+--------+--------------+--------+--------------+\n");
    printf("| n = %-5d | Размер | Контр. сумма | Высота | Средн.высота |\n", N);
    printf("+-----------+--------+--------------+--------+--------------+\n");
    printf("| ДБД       | %-6d | %-12d | %-6d | %-12.2f |\n", 
       Size(root_BBT), Sum(root_BBT), HeightBBT(root_BBT), AveragePathLength(root_BBT));
    printf("+-----------+--------+--------------+--------+--------------+\n");
    printf("| АВЛ       | %-6d | %-12d | %-6d | %-12.2f |\n", 
           Size(root_AVL), Sum(root_AVL), Height(root_AVL), AveragePathLength(root_AVL));
    printf("+-----------+--------+--------------+--------+--------------+\n");


    freeTree(root_BBT);
    freeTree(root_AVL);

    return 0;
}