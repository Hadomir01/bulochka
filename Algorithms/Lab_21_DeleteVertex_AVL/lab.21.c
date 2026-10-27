// delete from AVL 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define N 10

typedef struct vertex {
    int data;
    struct vertex* left;
    struct vertex* right;
    int balance;
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

void LL_rotation(Vertex** p) {
    Vertex* q = (*p)->left;
    (*p)->balance = 0;
    q->balance = 0;
    (*p)->left = q->right;
    q->right = *p;
    *p = q;
}

void LL1_rotation(Vertex** p, bool* shrink) {
    Vertex* q = (*p)->left;
    if (q->balance == 0) {
        q->balance = 1;
        (*p)->balance = -1;
        *shrink = false;
    } else {
        q->balance = 0;
        (*p)->balance = 0;
    }
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

void RR1_rotation(Vertex** p, bool* shrink) {
    Vertex* q = (*p)->right;
    if (q->balance == 0) {
        q->balance = -1;
        (*p)->balance = 1;
        *shrink = false;
    } else {
        q->balance = 0;
        (*p)->balance = 0;
    }
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

void Balanced_L(Vertex** p, bool* shrink) {
    if ((*p)->balance == -1) {
        (*p)->balance = 0;
    } else if ((*p)->balance == 0) {
        (*p)->balance = 1;
        *shrink = false;
    } else {
        if ((*p)->right->balance >= 0) {
            RR1_rotation(p, shrink);
        } else {
            RL_rotation(p);
        }
    }
}

void Balanced_R(Vertex** p, bool* shrink) {
    if ((*p)->balance == 1) {
        (*p)->balance = 0;
    } else if ((*p)->balance == 0) {
        (*p)->balance = -1;
        *shrink = false;
    } else {
        if ((*p)->left->balance <= 0) {
            LL1_rotation(p, shrink);
        } else {
            LR_rotation(p);
        }
    }
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
        if (*grow) {
            if ((*p)->balance > 0) {
                (*p)->balance = 0;
                *grow = false;
            } else if ((*p)->balance == 0) {
                (*p)->balance = -1;
            } else {
                if ((*p)->left->balance < 0) {
                    LL_rotation(p);
                } else {
                    LR_rotation(p);
                }
                *grow = false;
            }
        }

    } else if ((*p)->data < data) {
        add_To_AVL(data, &((*p)->right), grow);
        if (*grow) {
            if ((*p)->balance < 0) {
                (*p)->balance = 0;
                *grow = false;
            } else if ((*p)->balance == 0) {
                (*p)->balance = 1;
            } else {
                if ((*p)->right->balance > 0) {
                    RR_rotation(p);
                } else {
                    RL_rotation(p);
                }
                *grow = false;
            }
        }
    } else {
        *grow = false;
    }
}

void DELETE(Vertex** r, Vertex* q, bool* shrink) {
    if ((*r)->right != NULL) {
        DELETE(&((*r)->right), q, shrink);
        if (*shrink) {
            Balanced_R(r, shrink);
        }
    } else {
        Vertex* tmp = *r;
        q->data = tmp->data;
        *r = tmp->left;
        *shrink = true;
        free(tmp);
    }
}

void DeleteVertex(int data, Vertex** p, bool* shrink) {
    if (*p == NULL) {
        *shrink = false;
        return;
    }
    if (data < (*p)->data) {
        DeleteVertex(data, &((*p)->left), shrink);
        if (*shrink) {
            Balanced_L(p, shrink);
        }
    } else if (data > (*p)->data) {
        DeleteVertex(data, &((*p)->right), shrink);
        if (*shrink) {
            Balanced_R(p, shrink);
        }
    } else {
        Vertex* q = *p;
        if (q->left == NULL) {
            *p = q->right;
            *shrink = true;
            free(q);
        } else if (q->right == NULL) {
            *p = q->left;
            *shrink = true;
            free(q);
        } else {
            DELETE(&(q->left), q, shrink);
            if (*shrink) {
                Balanced_L(p, shrink);
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

void getRound_L_R(Vertex* root) {
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

    printf("Обход дерева перед удалением (->): ");
    getRound_L_R(root);
    printf("\n\n");

    bool shrink = false;
    for (int i = 0; i < N; i++) {
        DeleteVertex(arr[i], &root, &shrink);
        printf("Обход дерева после удаления вершины [%d] (->): ", arr[i]);
        getRound_L_R(root);
        printf("\n\n");
    }

    freeTree(root);

    return 0;
}