#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define N 64

typedef struct worker {
    char name_w[64];
    int id_w;
    char lvl_w[64];
} Worker;

// На 3...
void readFile(const char *filename) {
    int file = open(filename, O_RDONLY, 0644);
    if (file == -1) {
        perror("Error opening file");
        exit(1);
    }
    char line[256];
    int pos = 0;
    char ch;
    while (read(file, &ch, 1) > 0) {
        if (ch == '\n' || pos == sizeof(line)-1) {
            line[pos] = '\0';

            char *name = strtok(line, ";");
            char *id = strtok(NULL, ";");
            char *level = strtok(NULL, ";");

            printf("| %-14s\t | %-3s\t | %-12s\t |\n", name, id, level);

            pos = 0;
            if (ch == '\n') {
                continue;
            }
        }
        line[pos++] = ch;
    }
    close(file);
}

// На 4...
int createArr(const char *filename, Worker *arr, int size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }
    char line[256];
    int c = 0;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        Worker w;
        char *name = strtok(line, ";");
        strncpy(arr[c].name_w, name, sizeof(w.name_w) - 1);

        char *id = strtok(NULL, ";");
        arr[c].id_w = atoi(id);

        char *level = strtok(NULL, ";");
        strncpy(arr[c].lvl_w, level, sizeof(w.lvl_w) - 1);
        c++;
    }
    fclose(file);
    return c;
}

void writeToDatabase(const char *filename, Worker *arr, int c) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Ошибка открытия!");
        return;
    }
    fwrite(arr, sizeof(Worker), c, file);
    fclose(file);
}

void searchWorker(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Ошибка открытия!");
        return;
    }

    while (1) {
        int search_ID;
        printf("Чтобы выйти, нажмите 0\n");
        printf("Введите ID для поиска >> ");
        scanf("%d", &search_ID);
        
        Worker tmp;
        int find = 0;

        rewind(file);

        while (fread(&tmp, sizeof(Worker), 1, file)) {
            if (tmp.id_w == search_ID) {
                printf("Сотрудник найден: \n");
                find = 1;
                printf("%s, ID: %d, Ур. доступа: %s\n", tmp.name_w, tmp.id_w, tmp.lvl_w);
                break;
            }
        }
        if (search_ID == 0) {
            break;
        }
        if (find == 0) {
            printf("Сотрудник не найден!\n");
        }
        printf("\n");
    }
    fclose(file);
}

// На 5...
long get_file_size(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Ошибка открытия!");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    
    fclose(file);
    return size;
}

void compress(const char *file_comp, const char *file_res) {
    FILE *file_input = fopen(file_comp, "rb");
    FILE *file_output = fopen(file_res, "wb");
    if (!file_input || !file_output) {
        perror("Ошибка открытия!");
        return;
    }

    int cur_byte = fgetc(file_input);
    while (cur_byte != EOF) {
        unsigned char count = 1;
        int next_byte;

        while ((next_byte = fgetc(file_input)) != EOF && next_byte == cur_byte && count < 255) {
            count++;
        }

        fputc(count, file_output);
        fputc(cur_byte, file_output);

        cur_byte = next_byte;
    }

    fclose(file_input);
    fclose(file_output);
}

void decompress(const char *file_comp, const char *file_res) {
    FILE *file_input = fopen(file_comp, "rb");
    FILE *file_output = fopen(file_res, "wb");
    if (!file_input || !file_output) {
        perror("Ошибка открытия!");
        return;
    }

    unsigned char count;
    int value;

    while (fread(&count, 1, 1, file_input) == 1) {
        value = fgetc(file_input);
        if (value == EOF) break; 
        
        for (int i = 0; i < count; i++) {
            fputc(value, file_output);
        }
    }

    fclose(file_input);
    fclose(file_output);
}


void print_report(const char *file_1, const char *file_2, const char *file_3) {
    long size_before = get_file_size(file_1);
    long size_after = get_file_size(file_2);
    long size_return = get_file_size(file_3);

    if (size_before == -1 || size_after == -1 || size_return == -1) {
        printf("Ошибка при расчете размера файлов.\n");
        return;
    }

    double kb_before = size_before / 1024.0;
    double kb_after = size_after / 1024.0;
    double kb_return = size_return / 1024.0;

    double compression_ratio = (1.0 - (double)size_after / size_before) * 100.0;

    printf("Размер до: %.2f Кб, Размер после: %.2f Кб. Сжатие: %.2f%% Размер возвращения: %.2f\n", 
           kb_before, kb_after, compression_ratio, kb_return);
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        printf("Неверное число аргументов!");
        return 1;
    }

    printf("| %s\t\t | %s\t | %s\t |\n", "Имя и Фамилия", "ID", "Уровень");
    readFile(argv[1]);

    Worker array[N] = {};
    int c = createArr(argv[1], array, N);

    writeToDatabase(argv[2], array, c);

    searchWorker(argv[2]);

    compress(argv[2], argv[3]);

    decompress(argv[3], argv[4]);

    print_report(argv[2], argv[3], argv[4]);

    return 0;
}