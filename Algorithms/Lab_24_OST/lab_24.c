// Approximate optimal search tree A1 and A2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define N 10
#define MAXVAL 10

typedef struct vertex {
    int data;
    int weight;
    struct vertex* left;
    struct vertex* right;
} Vertex;

typedef struct {
    int data;
    int weight;
} element_t;

void generateArray(element_t arr[N]) {
    bool used[MAXVAL+1] = { false }; 
    int count = 0;

    while (count < N) {
        int num = rand() % N + 1; 
        
        if (!used[num]) {
            used[num] = true;
            arr[count].data = num;
            arr[count].weight = num;
            count++;
        }
    }
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

int SumWeight(Vertex *root) {
    if (root == NULL) return 0;
    return root->weight + SumWeight(root->left) + SumWeight(root->right);
}


int SumWeightedPath(Vertex *root, int L) {
    if (root == NULL) return 0;
    return L * root->weight + 
           SumWeightedPath(root->left, L + 1) + 
           SumWeightedPath(root->right, L + 1);
}

void quickSort_key(element_t array[], int l, int r) {
    while (l < r) {
        element_t x = array[l];
        int i = l, j = r;
        while (i <= j) {
            while (array[i].data < x.data) { i++; }
            while (array[j].data > x.data) { j--; }
            if (i <= j) {
                element_t tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
                i++;
                j--;
            }
        }
        if ((j - l) < (r - i)) {
            quickSort_key(array, l, j);
            l = i;
        } else {
            quickSort_key(array, i, r);
            r = j;
        }
    }
}

void Add(Vertex **p, int data, int weight) {
    if (*p == NULL) {
        *p = (Vertex*)malloc(sizeof(Vertex));
        (*p)->data = data;
        (*p)->weight = weight;
        (*p)->left = NULL;
        (*p)->right = NULL;
    } else if (data < (*p)->data) {
        Add(&(*p)->left, data, weight);
    } else if (data > (*p)->data) {
        Add(&(*p)->right, data, weight);
    }
}

void Create_AW(int AW[N + 1][N + 1], element_t arr[], int n) {
    for (int i = 0; i <= n; i++) {
        AW[i][i] = 0;
        for (int j = i + 1; j <= n; j++) {
            AW[i][j] = AW[i][j - 1] + arr[j - 1].weight;
        }
    }
}

void Create_AP_AR(int AW[N + 1][N + 1], int AP[N + 1][N + 1], int AR[N + 1][N + 1], int n) {
    for (int i = 0; i <= n; i++) {
        AP[i][i] = 0;
        AR[i][i] = 0;
    }

    for (int i = 0; i <= n - 1; i++) {
        int j = i + 1;
        AP[i][j] = AW[i][j];
        AR[i][j] = j;
    }

    for (int h = 2; h <= n; h++) {
        for (int i = 0; i <= n - h; i++) {
            int j = i + h;
            int m = AR[i][j - 1];
            int min = AP[i][m - 1] + AP[m][j];
            
            for (int k = m + 1; k <= AR[i + 1][j]; k++) {
                int x = AP[i][k - 1] + AP[k][j];
                if (x < min) {
                    m = k;
                    min = x;
                }
            }
            AP[i][j] = min + AW[i][j];
            AR[i][j] = m;
        }
    }
}

void Create_tree(Vertex **root, element_t arr[], int AR[N + 1][N + 1], int L, int R) {
    if (L < R) {
        int k = AR[L][R];
        Add(root, arr[k - 1].data, arr[k - 1].weight);
        Create_tree(root, arr, AR, L, k - 1);
        Create_tree(root, arr, AR, k, R);
    }
}

void quickSort_weight(element_t array[], int l, int r) {
    while (l < r) {
        element_t x = array[l];
        int i = l, j = r;
        while (i <= j) {
            while (array[i].weight > x.weight) { i++; }
            while (array[j].weight < x.weight) { j--; }
            
            if (i <= j) {
                element_t tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
                i++;
                j--;
            }
        }
        if ((j - l) < (r - i)) {
            quickSort_weight(array, l, j);
            l = i;
        } else {
            quickSort_weight(array, i, r);
            r = j;
        }
    }
}

Vertex* OST_A1(element_t *arr, int n) {
    Vertex *root = NULL;
    for (int i = 0; i < n; i++) {
        Add(&root, arr[i].data, arr[i].weight);
    }
    return root;
}

void OST_A2(Vertex **p, element_t *arr, int L, int R) {
    if (L <= R) {
        int w = 0;
        for (int i = L; i <= R; i++) {
            w += arr[i].weight;
        }
        int sum = 0;
        int k = L;
        for (int i = L; i <= R; i++) {
            if ((sum < w/2) && ((sum + arr[i].weight) >= w/2)) {
                k = i;
                break;
            }
            sum += arr[i].weight;
        }
        Add(p, arr[k].data, arr[k].weight);
        OST_A2(p, arr, L, k - 1);
        OST_A2(p, arr, k + 1, R);
    }

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
    int n = N;
    element_t arr[N];
    element_t arr_copy[N];

    generateArray(arr);
    for (int i = 0; i < n; i++) {
        arr_copy[i] = arr[i];
    }

    quickSort_weight(arr_copy, 0, n - 1);
    Vertex *root_a1 = OST_A1(arr_copy, n);

    quickSort_key(arr, 0, n - 1);
    Vertex *root_a2 = NULL;
    OST_A2(&root_a2, arr, 0, n - 1);

    int AW[N + 1][N + 1] = {0};
    int AP[N + 1][N + 1] = {0};
    int AR[N + 1][N + 1] = {0};

    Create_AW(AW, arr, n);
    Create_AP_AR(AW, AP, AR, n);

    Vertex *root_dop = NULL;
    Create_tree(&root_dop, arr, AR, 0, n);

    printf("Обход точное ДОП:\n");
    getRound_L_R(root_dop);
    printf("\n\n");

    printf("Проверка ДОП: AP[0][n]/AW[0][n] = %.4f, h_срв дерева = %.4f\n\n",
           (double)AP[0][n] / AW[0][n],
           (double)SumWeightedPath(root_dop, 1) / SumWeight(root_dop));

    printf("|-------------------------------------------------------------------------|\n");
    printf("| n = %-3d | Размер      | Контр. Сумма | Высота      | Средневзвеш.высота |\n", n);
    printf("|-------------------------------------------------------------------------|\n");
    printf("| ДОП     | %-11d | %-12d | %-11d | %-18.2f |\n",
        Size(root_dop), Sum(root_dop), Height(root_dop), (double)SumWeightedPath(root_dop, 1) / SumWeight(root_dop));
    printf("|-------------------------------------------------------------------------|\n");
    printf("| A1      | %-11d | %-12d | %-11d | %-18.2f |\n",
        Size(root_a1), Sum(root_a1), Height(root_a1), (double)SumWeightedPath(root_a1, 1) / SumWeight(root_a1));
    printf("| A2      | %-11d | %-12d | %-11d | %-18.2f |\n",
        Size(root_a2), Sum(root_a2), Height(root_a2), (double)SumWeightedPath(root_a2, 1) / SumWeight(root_a2));
    printf("|-------------------------------------------------------------------------|\n");
    
    freeTree(root_dop);
    freeTree(root_a1);
    freeTree(root_a2);

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            printf("%2d ",AR[i][j]);
        }
        printf("\n");
    }

    return 0;
}
