#ifndef CONFIG_H
#define CONFIG_H

#include <string>

// Загружаем конфиг из файла
bool config_load(const std::string& filename);

// Получаем значение по ключу (с дефолтом)
std::string config_get(const std::string& key, const std::string& default_value = "");

// Проверяем наличие ключа
bool config_has(const std::string& key);

// Устанавливаем значение
void config_set(const std::string& key, const std::string& value);

// Очищаем все настройки
void config_clear();

#endif