#ifndef ANAGRAM_UTILS_H
#define ANAGRAM_UTILS_H

#include <string>
#include <vector>

// Проверяем, состоит ли слово только из допустимых символов
bool is_valid_word(const std::wstring& word);

// Генератор анаграмм
bool generate_anagrams(const std::wstring& word, std::vector<std::wstring>& anagrams);

#endif