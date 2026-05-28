#include "anagram_utils.h"
#include "logger.h"
#include <algorithm>

static bool is_valid_char(wchar_t ch) { // Проверка символа на корректность
    if ((ch >= L'a' && ch <= L'z') || (ch >= L'A' && ch <= L'Z')) {
        return true;
    }
    if ((ch >= L'а' && ch <= L'я') || (ch >= L'А' && ch <= L'Я') || 
         ch == L'ё' || ch == L'Ё') {
        return true;
    }
    return false; 
}

bool is_valid_word(const std::wstring& word) { // Проверка слова
    if (word.empty()) {
        return false;
    }
    
    for (size_t i = 0; i < word.length(); ++i) {
        if (!is_valid_char(word[i])) {
            return false;
        }
    }
    return true;
}

static void generate_recursive(const std::wstring& prefix,
                                const std::wstring& remaining,
                                std::vector<std::wstring>& result) { // === Генератор анаграмм === 
    if (remaining.empty()) {
        result.push_back(prefix);
        return;
    }
    
    for (size_t i = 0; i < remaining.length(); ++i) {
        generate_recursive(
            prefix + remaining[i],
            remaining.substr(0, i) + remaining.substr(i + 1),
            result
        );
    }
}

bool generate_anagrams(const std::wstring& word, std::vector<std::wstring>& anagrams) { // Формируем слово и рекурсивно генерируем анаграммы
    anagrams.clear();
    
    if (word.empty()) {
        log_error("Empty word");
        return false;
    }
    
    generate_recursive(L"", word, anagrams);
    
    log_info("Generated " + std::to_string(anagrams.size()) + " anagrams");
    return true;
}