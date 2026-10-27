#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int *table;
    int size;
    int collisions;
    bool is_quadratic;
} HashTable;

HashTable create_table(int size, bool is_quadratic) {
    HashTable ht;
    ht.size = size;
    ht.collisions = 0;
    ht.is_quadratic = is_quadratic;
    ht.table = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        ht.table[i] = -1; 
    }
    return ht;
}

void free_table(HashTable *ht) {
    free(ht->table);
}

int hash_func(int number, int size) {
    return number % size;
}

bool insert(HashTable *ht, int number) {
    int home_bucket = hash_func(number, ht->size);

    if (ht->table[home_bucket] == -1) {
        ht->table[home_bucket] = number;
        return true;
    }
    
    int i = 1;
    while (i < ht->size) {
        ht->collisions++;
        int next_bucket;
        
        if (!ht->is_quadratic) {
            next_bucket = (home_bucket + i) % ht->size;
        } else {
            next_bucket = (home_bucket + i * i) % ht->size;
        }
        
        if (ht->table[next_bucket] == -1) {
            ht->table[next_bucket] = number;
            return true;
        }
        i++;
    }
    return false;
}

void print_table(HashTable *ht, const char *name) {
    printf("%s (Кф = %d): [", name, ht->collisions);
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i] == -1) printf(" _");
        else printf(" %d", ht->table[i]);
    }
    printf(" ]\n");
}

int main() {
    srand(time(NULL));

    printf("=== ЗАДАНИЕ 2 ===\n");
    int m2 = 11;
    int test_numbers[] = {12, 23, 34, 12, 45, 56, 67};
    int num_elements = sizeof(test_numbers) / sizeof(test_numbers[0]);

    HashTable ht_lin2 = create_table(m2, false);
    HashTable ht_quad2 = create_table(m2, true);

    for (int i = 0; i < num_elements; i++) {
        insert(&ht_lin2, test_numbers[i]);
        insert(&ht_quad2, test_numbers[i]);
    }

    print_table(&ht_lin2, "Линейные пробы   ");
    print_table(&ht_quad2, "Квадратичные пробы");
    printf("\n");

    free_table(&ht_lin2);
    free_table(&ht_quad2);

    printf("=== ЗАДАНИЕ 3 ===\n");
    int primes[10] = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43}; 
    int num_numbers = 20;
    
    int *random_numbers = (int *)malloc(num_numbers * sizeof(int));
    for (int j = 0; j < num_numbers; j++) {
        random_numbers[j] = 10 + (rand() % 90);
    }

    printf("Общий массив чисел для всех тестов: [");
    for (int j = 0; j < num_numbers; j++) {
        printf(" %d", random_numbers[j]);
    }
    printf(" ]\n\n");

    printf("%-12s | %-15s | %-15s | %-15s\n", 
           "Размер ХТ", "Кол-во чисел", "Линейные пробы", "Квадратичные пробы");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < 10; i++) {
        int size = primes[i];

        HashTable ht_lin3 = create_table(size, false);
        HashTable ht_quad3 = create_table(size, true);

        for (int j = 0; j < num_numbers; j++) {
            insert(&ht_lin3, random_numbers[j]);
            insert(&ht_quad3, random_numbers[j]);
        }

        printf("%-12d | %-15d | %-15d | %-15d\n", 
               size, num_numbers, ht_lin3.collisions, ht_quad3.collisions);

        free_table(&ht_lin3);
        free_table(&ht_quad3);
    }
    printf("-----------------------------------------------------------------\n");

    free(random_numbers);

    return 0;
}
