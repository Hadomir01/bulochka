#include "config.h"
#include <fstream>
#include <algorithm>
#include <unordered_map>

static std::unordered_map<std::string, std::string> g_config;

static std::string trim(const std::string& s) { // Удаляем невидимые символы (табы, пробелы, переводы строки)
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

bool config_load(const std::string& filename) { // Загружаем конфиг из файла
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    
    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;
        
        size_t pos = line.find('=');
        if (pos == std::string::npos) continue;
        
        std::string key = trim(line.substr(0, pos));
        std::string value = trim(line.substr(pos + 1));
        
        if (!key.empty()) {
            g_config[key] = value;
        }
    }
    return true;
}

std::string config_get(const std::string& key, const std::string& default_value) { // Получаем значение по ключу (с дефолтом)
    auto it = g_config.find(key);
    return (it != g_config.end()) ? it->second : default_value;
}

bool config_has(const std::string& key) { // Проверяем наличие ключа
    return g_config.find(key) != g_config.end();
}

void config_set(const std::string& key, const std::string& value) { // Устанавливаем значение
    g_config[key] = value;
}

void config_clear() { // Очищаем все настройки
    g_config.clear();
}