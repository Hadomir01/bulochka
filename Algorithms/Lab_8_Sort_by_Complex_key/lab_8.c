#include <stdio.h>
#include <string.h>

typedef struct {
    char surname[50];
    char name[50];
    char phone[20];
    int age;
} Contact;

int less_Name(Contact *a, Contact *b) {
    int res = strcmp(a->surname, b->surname);
    if (res != 0) {
        return res;
    }
    return strcmp(a->name, b->name);
}

int less_Age(Contact *a, Contact *b) {
    return a->age - b->age;
}

void selectSort(Contact *idx[], int n, int (*cmp)(Contact*, Contact*)) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (cmp(idx[j], idx[min]) < 0) {
                min = j;
            }
        }
        Contact *tmp = idx[min];
        idx[min] = idx[i];
        idx[i] = tmp;
    }
}

void printByPointers(Contact *idx[], int n, const char *title) {
    printf("--- %s ---\n", title);
    printf("%-15s\t %-15s\t %-10s\t %s\t\n", "Фамилия", "Имя", "Телефон", "Возраст");
    for (int i = 0; i < n; i++) {
        printf("%-15s\t %-15s\t %-10s\t %d\t\n", idx[i]->surname, idx[i]->name, idx[i]->phone, idx[i]->age);
    }
    printf("\n");
}

int binSearchSurname(Contact *idx[], int n, char *key) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int res = strcmp(idx[mid]->surname, key);
        if (res == 0) return mid;
        if (res < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int binSearchAge(Contact *idx[], int n, int key) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int res = idx[mid]->age - key;
        if (res == 0) return mid;
        if (res < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    Contact book[5] = {
        {"Фильченков", "Роман", "555-10-20", 30},
        {"Окунев", "Сергей", "555-30-40", 25},
        {"Сидоров", "Алексей", "555-50-60", 40},
        {"Иванов", "Иван", "555-70-80", 22},
        {"Окунев", "Данил", "555-90-00", 35}
    };
    int n = 5;

    Contact *idx_name[5];
    Contact *idx_age[5];

    for (int i = 0; i < n; i++) {
        idx_name[i] = &book[i];
        idx_age[i] = &book[i];
    }

    selectSort(idx_name, n, less_Name);
    selectSort(idx_age, n, less_Age);

    printByPointers(idx_name, n, "Сортировка по фамилии");
    printByPointers(idx_age, n, "Сортировка по возрасту");

    printf("=== Исходный массив ===\n");
    for (int i = 0; i < n; i++) {
        printf("Адрес %p: %-15s %-15s\n", (void*)&book[i], book[i].surname, book[i].name);
    }

    printf("\n=== Массив указателей (сортировка по фамилии/имени) ===\n");
    for (int i = 0; i < n; i++) {
        printf("idx_name[%d] -> указывает на %p: %-15s\n", i, (void*)idx_name[i], idx_name[i]->surname);
    }

    printf("\n=== Массив указателей (сортировка по возрасту) ===\n");
    for (int i = 0; i < n; i++) {
        printf("idx_name[%d] -> указывает на %p: %-15s\t %d\n", i, (void*)idx_age[i], idx_age[i]->surname, idx_age[i]->age);
    }
    printf("------------------------------------------------------------\n\n");

    char key[] = "Сидоров";
    int pos = binSearchSurname(idx_name, n, key);
    
    if (pos != -1) {
        printf("Результат поиска '%s': %s %s, тел: %s\n", 
                key, idx_name[pos]->surname, idx_name[pos]->name, idx_name[pos]->phone);
    } else {
        printf("Запись '%s' не найдена.\n", key);
    }

    int key_age = 25;
    int pos_age = binSearchAge(idx_age, n, key_age);
    
    if (pos_age != -1) {
        printf("Результат поиска '%s': %s %s, тел: %s\n", 
                key, idx_age[pos]->surname, idx_age[pos]->name, idx_age[pos]->phone);
    } else {
        printf("Запись '%s' не найдена.\n", key);
    }
    return 0;
}
