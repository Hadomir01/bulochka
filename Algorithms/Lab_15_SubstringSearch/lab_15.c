#include <stdio.h>
#include <string.h>

#define d 256
#define q 1023

void LinearSearch(const char* haystack, const char* needle) {
    int n = strlen(haystack);
    int m = strlen(needle);
    int comparisons = 0;

    printf("\n--- 1. Прямой поиск ---\n");
    printf("Текст: \"%s\"\n", haystack);
    printf("Подстрока: \"%s\"\n", needle);
    printf("Индексы вхождений: ");

    int found_count = 0;
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            comparisons++;
            if (haystack[i + j] != needle[j]) {
                break;
            }
        }
        if (j == m) {
            printf("%d ", i);
            found_count++;
        }
    }

    if (found_count == 0) {
        printf("не найдены");
    }
    printf("\nКоличество посимвольных сравнений: %d\n", comparisons);
}

void rabinKarpSearch(const char* haystack, const char* needle) {
    int n = strlen(haystack);
    int m = strlen(needle);
    int comparisons = 0;
    
    int hash_haystack = 0;
    int hash_needle = 0;
    int h = 1;

    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (int i = 0; i < m; i++) {
        hash_needle = (d * hash_needle + needle[i]) % q;
        hash_haystack = (d * hash_haystack + haystack[i]) % q;
    }

    printf("\n--- 2. Метод Рабина-Карпа ---\n");
    printf("Текст: \"%s\"\n", haystack);
    printf("Подстрока: \"%s\"\n", needle);
    printf("Индексы вхождений: ");

    int found_count = 0;
    for (int i = 0; i <= n - m; i++) {
        if (hash_needle == hash_haystack) {
            int j;
            for (j = 0; j < m; j++) {
                comparisons++;
                if (haystack[i + j] != needle[j]) {
                    break;
                }
            }
            if (j == m) {
                printf("%d ", i);
                found_count++;
            }
        }

        if (i < n - m) {
            hash_haystack = (d * (hash_haystack - haystack[i] * h) + haystack[i + m]) % q;
            if (hash_haystack < 0) {
                hash_haystack = (hash_haystack + q);
            }
        }
    }

    if (found_count == 0) {
        printf("не найдены");
    }
    printf("\nКоличество посимвольных сравнений: %d\n", comparisons);
}

int main() {
    const char haystack[] = "Although the enigmatic archaeologist had dedicated his entire adult life to uncovering the deeply buried secrets of the ancient civilization, he was still utterly astonished when, after months of meticulous excavation under the scorching desert sun, he finally discovered an intricately carved stone tablet that contained the exact, unmistakable pattern written in a forgotten dialect, prompting him to immediately contact his colleagues at the university so they could begin the arduous process of deciphering the cryptic message before the fast-approaching sandstorm could obliterate the historic site forever.";
    const char pattern[] = "archaeologist";

    LinearSearch(haystack, pattern);
    rabinKarpSearch(haystack, pattern);

    return 0;
}