#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
extern "C" {
#include <cmocka.h>
}
#include <string>
#include <vector>
#include "anagram_utils.h"
#include "config.h"

// Слово на английском
static void test_valid_word_latin(void**) { 
    assert_true(is_valid_word(L"hello"));
    assert_true(is_valid_word(L"WORLD"));
    assert_true(is_valid_word(L"AbCdEf"));
}

// Слово на русскм
static void test_valid_word_cyrillic(void**) {
    assert_true(is_valid_word(L"привет"));
    assert_true(is_valid_word(L"МОСКВА"));
    assert_true(is_valid_word(L"ёлка"));
    assert_true(is_valid_word(L"Ёжик"));
}

// Пустое слово
static void test_invalid_word_empty(void**) {
    assert_false(is_valid_word(L""));
}

// Слово с недопустимыми символами
static void test_invalid_word_with_digits(void**) {
    assert_false(is_valid_word(L"abc1"));
    assert_false(is_valid_word(L"123"));
}

// Слово с пробелом
static void test_invalid_word_with_spaces(void**) {
    assert_false(is_valid_word(L"hello world"));
    assert_false(is_valid_word(L" "));
}

// Слово со знаком
static void test_invalid_word_with_punctuation(void**) {
    assert_false(is_valid_word(L"hello!"));
    assert_false(is_valid_word(L"test-case"));
    assert_false(is_valid_word(L"what?"));
}

// Слово из одной буквы (генерация)
static void test_anagrams_single_char(void**) {
    std::vector<std::wstring> result;
    assert_true(generate_anagrams(L"a", result));
    assert_int_equal((int)result.size(), 1);
    assert_true(result[0] == L"a");
}

// Слово с двумя буквами (генерация)
static void test_anagrams_two_chars(void**) {
    std::vector<std::wstring> result;
    assert_true(generate_anagrams(L"ab", result));
    assert_int_equal((int)result.size(), 2);
}

// Слово с тремя буквами(генерация)
static void test_anagrams_three_chars_count(void**) {
    std::vector<std::wstring> result;
    assert_true(generate_anagrams(L"abc", result));
    assert_int_equal((int)result.size(), 6);
}

// Слово с четырмя буквами (генерация)
static void test_anagrams_four_chars_count(void**) {
    std::vector<std::wstring> result;
    assert_true(generate_anagrams(L"abcd", result));
    assert_int_equal((int)result.size(), 24);
}

// Пустое слово (генерация)
static void test_anagrams_empty_word(void**) {
    std::vector<std::wstring> result;
    assert_false(generate_anagrams(L"", result));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_valid_word_latin),
        cmocka_unit_test(test_valid_word_cyrillic),
        cmocka_unit_test(test_invalid_word_empty),
        cmocka_unit_test(test_invalid_word_with_digits),
        cmocka_unit_test(test_invalid_word_with_spaces),
        cmocka_unit_test(test_invalid_word_with_punctuation),

        cmocka_unit_test(test_anagrams_single_char),
        cmocka_unit_test(test_anagrams_two_chars),
        cmocka_unit_test(test_anagrams_three_chars_count),
        cmocka_unit_test(test_anagrams_four_chars_count),
        cmocka_unit_test(test_anagrams_empty_word),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}