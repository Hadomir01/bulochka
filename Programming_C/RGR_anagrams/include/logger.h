#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

enum LogLevel { LOG_INFO, LOG_WARNING, LOG_ERROR };

inline static std::ofstream g_log_file;
inline static LogLevel g_min_level = LOG_INFO;
inline static bool g_console_output = true;

inline std::string timestamp() { // Получение времени и его форматирование
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

inline const char* level_str(LogLevel level) { // Ур. логирования в строку
    switch (level) {
        case LOG_INFO:    return "INFO";
        case LOG_WARNING: return "WARNING";
        case LOG_ERROR:   return "ERROR";
        default:          return "UNKNOWN";
    }
}

inline void log(LogLevel level, const std::string& message) { // Формирование сообщений 
    if (level < g_min_level) return;
    
    std::string line = timestamp() + " [" + level_str(level) + "] " + message;
    
    if (g_log_file.is_open()) {
        g_log_file << line << std::endl;
        g_log_file.flush();
    }
    
    if (g_console_output) {
        if (level == LOG_ERROR) {
            std::cerr << line << std::endl;
        } else {
            std::cout << line << std::endl;
        }
    }
}

inline void log_info(const std::string& msg) { log(LOG_INFO, msg); }
inline void log_warning(const std::string& msg) { log(LOG_WARNING, msg); }
inline void log_error(const std::string& msg) { log(LOG_ERROR, msg); }

inline void logger_init(const std::string& filename) { // Открытие файла с логами
    if (!filename.empty()) {
        g_log_file.open(filename, std::ios::out | std::ios::app);
    }
}

inline void logger_set_level(LogLevel level) { // Устанавливанм минимальный уровень
    g_min_level = level;
}

inline void logger_set_console(bool enabled) { // Вывод в консоль (да/нет)
    g_console_output = enabled;
}

inline void logger_close() { // Закрываем файл с логами
    if (g_log_file.is_open()) {
        g_log_file.close();
    }
}

#endif