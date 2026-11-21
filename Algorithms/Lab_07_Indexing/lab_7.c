#include <stdio.h>
#include <string.h>

typedef struct {
    char surname[50];
    char name[50];
    char phone[20];
    int age;
} Contact;

int less(Contact a, Contact b) {
    int res = strcmp(a.surname, b.surname);
    if (res < 0) return 1;
    if (res > 0) return 0;
    return strcmp(a.name, b.name) < 0;
}

void selectSort(Contact arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (less(arr[j], arr[min_idx])) {
                min_idx = j;
            }
        }
        Contact temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void printContacts(Contact arr[], int n) {
    printf("%-15s\t %-15s\t %-10s\t %s\t\n", "Фамилия", "Имя", "Телефон", "Возраст");
    for (int i = 0; i < n; i++) {
        printf("%-15s\t %-15s\t %-10s\t %d\t\n", arr[i].surname, arr[i].name, arr[i].phone, arr[i].age);
    }
    printf("------------------------------------------------------------\n\n");
}

int binarySearch(Contact arr[], int n, char *target) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int res = strcmp(arr[mid].surname, target);
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

    printf("Исходный справочник:\n");
    printContacts(book, n);

    selectSort(book, n);

    printf("Отсортированный справочник (по Фамилии и Имени):\n");
    printContacts(book, n);

    char searchKey[128] = "Сидоров";
    printf("Поиск по фамилии '%s':\n", searchKey);
    int index = binarySearch(book, n, searchKey);

    if (index != -1) {
        printf("Найдено: %s %s, тел: %s\n", book[index].surname, book[index].name, book[index].phone);
    } else {
        printf("Запись не найдена.\n");
    }

    return 0;
}
