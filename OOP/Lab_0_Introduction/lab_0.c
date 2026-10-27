#include <stdio.h>
#include <string.h>

#define N 2

typedef struct NOTE {
    char name[32];
    long int phone_number;
    int date_of_born[3];
} NOTE_t;

void enterStructs_name(NOTE_t data_base[N], int n) {
    fgets(data_base[n].name, sizeof(data_base[n].name), stdin);
    data_base[n].name[strcspn(data_base[n].name, "\n")] = '\0';
}

void enterStructs_phone_number(NOTE_t data_base[N], int n) {
    scanf("%ld", &data_base[n].phone_number);
    while (getchar() != '\n'); 
}

void enterStructs_date(NOTE_t data_base[N], int n) {
    scanf("%d %d %d", &data_base[n].date_of_born[0], &data_base[n].date_of_born[1], &data_base[n].date_of_born[2]);
    while (getchar() != '\n'); 
}

void search_all(NOTE_t data_base[N], int question) {
    int found_count = 0;

    for (int i = 0; i < N; i++) {
        if (question == data_base[i].date_of_born[2]) {
            printf("Найдена запись: %s, Тел: %ld, Дата рождения: %02d.%02d.%d\n", 
                   data_base[i].name, 
                   data_base[i].phone_number, 
                   data_base[i].date_of_born[0], 
                   data_base[i].date_of_born[1], 
                   data_base[i].date_of_born[2]);
            found_count++;
        }
    }

    if (found_count == 0) {
        printf("Записи с таким годом рождения не найдены.\n");
    } else {
        printf("Всего найдено записей: %d\n", found_count);
    }
}

int main() {
    NOTE_t data_base[N];

    for (int i = 0; i < N; i++) {
        printf("--- Заполнение записи %d ---\n", i + 1);
        printf("Введите фамилию и имя >> ");
        enterStructs_name(data_base, i);

        printf("Введите номер телефона >> ");
        enterStructs_phone_number(data_base, i);

        printf("Введите дату рождения (день месяц год через пробел) >> ");
        enterStructs_date(data_base, i);
    }

    printf("\n============================\n");

    while (1) {
        int question;
        printf("Введите год рождения для поиска >> ");
        scanf("%d", &question);

        search_all(data_base, question); 
        
        printf("----------------------------\n");
    }

    return 0;
}
