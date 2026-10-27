#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Узел односвязного списка теперь хранит int вместо char
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node** table;
    int size;
} HashTable;

HashTable* createTable(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->table = (Node**)malloc(size * sizeof(Node*));
    for (int i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

// Хеш-функция принимает целочисленный ключ
int hashFunction(int key, int size) {
    return key % size;
}

void insert(HashTable* ht, int key) {
    int index = hashFunction(key, ht->size);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = key;
    newNode->next = NULL;

    if (ht->table[index] == NULL) {
        ht->table[index] = newNode;
    } else {
        Node* current = ht->table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int countCollisions(HashTable* ht) {
    int collisions = 0;
    for (int i = 0; i < ht->size; i++) {
        Node* current = ht->table[i];
        int count = 0;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        if (count > 1) {
            collisions += (count - 1);
        }
    }
    return collisions;
}

int min_size_table(int n) {
    if (n <= 2) return 1;
    double lg = log2((double)n);
    int m = (int)ceil((double)n/ (2 * (lg - 1)));
    return m < 1 ? 1 : m;
}

void printTable(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        printf("Список [%d]: ", i);
        Node* current = ht->table[i];
        if (current == NULL) {
            printf("пусто\n");
        } else {
            while (current != NULL) {
                printf("%d", current->data);
                if (current->next != NULL) printf(" -> ");
                current = current->next;
            }
            printf("\n");
        }
    }
}

void freeTable(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        Node* current = ht->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

int main() {
    srand(time(NULL));

    int n = 20;
    int source_numbers[20];
    for (int i = 0; i < n; i++) {
        source_numbers[i] = 10 + (rand() % 90);
    }

    printf("=== ЗАДАНИЕ 2 ===\n");
    printf("Количество чисел (n): %d\n", n);

    int opt = min_size_table(n);
    int size = opt;
    
    while (1) {
        int is_prime = 1;
        for (int i = 2; i * i <= size; i++) {
            if (size % i == 0) { is_prime = 0; break; }
        }
        if (is_prime) break;
        size++;
    }
    printf("Теоретический минимальный размер m: %d\n", opt);
    printf("Выбранный размер таблицы (ближайшее простое число): %d\n\n", size);

    HashTable* ht2 = createTable(size);
    for (int i = 0; i < n; i++) {
        insert(ht2, source_numbers[i]);
    }

    printf("Построенные списки хеш-таблицы:\n");
    printTable(ht2);
    printf("\nФактическое количество коллизий Кф: %d\n\n", countCollisions(ht2));
    freeTable(ht2);

    printf("=== ЗАДАНИЕ 3 ===\n");
    int prime_sizes[10] = {11, 13, 19, 31, 43, 53, 61, 73, 89, 101};

    printf("-----------------------------------------------------------------\n");
    printf("| %-18s | %-18s | %-18s |\n", "Размер хеш-таблицы", "Количество чисел", "Кол-во коллизий");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < 10; i++) {
        HashTable* ht3 = createTable(prime_sizes[i]);
        for (int j = 0; j < n; j++) {
            insert(ht3, source_numbers[j]);
        }
        int collisions = countCollisions(ht3);
        printf("| %-18d | %-16d | %-15d |\n", prime_sizes[i], n, collisions);
        freeTable(ht3);
    }
    printf("-----------------------------------------------------------------\n");

    return 0;
}
