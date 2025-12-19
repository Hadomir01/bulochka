#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char str[256] = "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariaturqqqqqqqqqqqqqqqqqqqqqqq";
    char copy_str[256] = "";  
    strcpy(copy_str, str);
    char* word;
    char* long_word;
    int len_long_word = 0;

    word = strtok(str, " ");

    while (word != NULL) {
        // printf("%s\n", word);
        int len_word = strlen(word);
        if (len_word > len_long_word) {
            len_long_word = len_word;
            long_word = word;
        }
        word = strtok(NULL, " ");
    }
    
    int word_in_str = long_word - str;
    for (int i = word_in_str; i<word_in_str+len_long_word; i++) {
        copy_str[i] = 'x';
    }

    printf("%s\n", long_word);
    printf("%s\n", copy_str);
}