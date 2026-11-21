#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 256

void caesar_cipher(char text[N], char result[N], int shift) {
    if (shift < 0) {
        shift = 26 + shift;
    }
    for (int i = 0; i<strlen(text); i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            result[i] = ((text[i] - 'A' + shift) % 26) + 'A';
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            result[i] = ((text[i] - 'a' + shift) % 26) + 'a';
        } else {
            result[i] = text[i];
        }
    }
    result[strlen(text)] = '\0';
}

void caesar_decipher(char text[N], char result[N], int shift) {
    if (shift < 0) {
        shift = 26 + shift;
    }
    for (int i = 0; i<strlen(text); i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            result[i] = ((text[i] - 'A' - shift + 26) % 26) + 'A';
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            result[i] = ((text[i] - 'a' - shift + 26) % 26) + 'a';
        } else {
            result[i] = text[i];
        }
    }
    result[strlen(text)] = '\0';
}

int main() {
    char text[N];
    char result[N];
    char sign;
    int shift;

    printf("Введите текст > ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;
    printf("+ если шифруем |- если дешифруем > ");
    scanf("%c", &sign);
    printf("На сколько смещаем? > ");
    scanf("%d", &shift);

    if (sign == '+') {
        caesar_cipher(text, result, shift);
        printf("%s\n", result);
    } else {
        caesar_decipher(text, result, shift);
        printf("%s\n", result);
    }
}