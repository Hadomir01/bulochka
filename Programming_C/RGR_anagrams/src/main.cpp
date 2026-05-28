#include "config.h"
#include "logger.h"
#include "anagram_utils.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <locale>
#include <codecvt>
#include <algorithm>

std::string wstring_to_utf8(const std::wstring& wstr) {
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    try {
        return conv.to_bytes(wstr);
    } catch (...) {
        return "[Error]";
    }
}

LogLevel parse_log_level(const std::string& level) {
    std::string upper = level;
    std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    if (upper == "ERROR") return LOG_ERROR;
    if (upper == "WARNING") return LOG_WARNING;
    return LOG_INFO;
}

int main(int argc, char* argv[]) {
    std::locale::global(std::locale(""));
    
    // Загрузка конфига (если указан)
    std::string config_file = "config.conf";
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--config" && i + 1 < argc) {
            config_file = argv[++i];
            break;
        }
    }
    
    config_load(config_file);
    
    // Аргументы командной строки имеют приоритет
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg.find('=') != std::string::npos) {
            size_t pos = arg.find('=');
            config_set(arg.substr(0, pos), arg.substr(pos + 1));
        }
    }
    
    // Инициализация логгера из конфига
    std::string log_file = config_get("LOG_FILE", "app.log");
    std::string log_level = config_get("LOG_LEVEL", "INFO");
    bool console_log = config_get("CONSOLE_LOG", "true") == "true";
    
    logger_init(log_file);
    logger_set_level(parse_log_level(log_level));
    logger_set_console(console_log);
    
    // Проверка входного файла
    std::string input_file;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-' && std::string(argv[i]).find('=') == std::string::npos) {
            input_file = argv[i];
            break;
        }
    }
    
    if (input_file.empty()) {
        log_error("No input file specified");
        std::cout << "Usage: " << argv[0] << " <input_file> [--config file.conf] [KEY=VALUE]\n";
        logger_close();
        return 1;
    }
    
    log_info("=== Anagram Generator ===");
    log_info("Config file: " + config_file);
    log_info("Input file: " + input_file);
    
    // Чтение слова
    std::wifstream f(input_file);
    if (!f.is_open()) {
        log_error("Cannot open: " + input_file);
        logger_close();
        return 1;
    }
    
    std::wstring word;
    f >> word;
    f.close();
    
    if (word.empty()) {
        log_error("Empty file");
        logger_close();
        return 1;
    }
    
    std::cout << "=== Анагарммы === " << std::endl;
    std::cout << "Слово: " << wstring_to_utf8(word) << "\n\n";

    if (word.length() > 10) {
        log_error("Too long word");
        logger_close();
        return 1;
    }

    if (!is_valid_word(word)) {
        log_error("Word contains invalid characters");
        logger_close();
        return 1;
    }
    
    // Генерация анаграмм
    auto start = std::chrono::steady_clock::now();
    std::vector<std::wstring> anagrams;
    
    if (!generate_anagrams(word, anagrams)) {
        log_error("Generation failed");
        logger_close();
        return 1;
    }
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start);
    
    // Результаты
    size_t total = anagrams.size();
    int max_display = std::stoi(config_get("MAX_DISPLAY", "100"));
    size_t display = std::min(total, (size_t)max_display);
    
    std::cout << "Создано: " << total << " анаграмм\n";
    std::cout << "Время работы: " << duration.count() << " мс\n";
    
    if (total > 0) {
        std::cout << "\n";
        if (total <= (size_t)max_display) {
            std::cout << "Все анаграммы:\n";
        } else {
            std::cout << "Первые " << display << " анаграмм (из " << total << "):\n";
        }
        
        for (size_t i = 0; i < display; i++) {
            std::cout << "  " << wstring_to_utf8(anagrams[i]) << "\n";
        }
        
        if (total > display) {
            std::cout << "  ... (и ещё " << (total - display) << ")\n";
        }
    }
    
    // Сохранение в файл
    std::string output_file = config_get("OUTPUT_FILE", "output.txt");
    std::wofstream out(output_file);
    
    if (out.is_open()) {
        for (const auto& a : anagrams) {
            out << a << L"\n";
        }
        out.close();
        std::cout << "\nСохранено в: " << output_file << "\n";
        log_info("Saved to " + output_file);
    } else {
        log_warning("Cannot save to " + output_file);
    }
    
    log_info("Finished");
    logger_close();
    return 0;
}