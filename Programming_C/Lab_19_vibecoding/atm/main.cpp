#include "atm_engine.h"
#include <iostream>
#include <string>
#include <limits>  // для numeric_limits

void show_menu() {
    std::cout << "\n=== МЕНЮ БАНКОМАТА ===\n"
              << "1. Проверить баланс\n"
              << "2. Пополнить счет\n"
              << "3. Снять наличные\n"
              << "4. История операций (последние 5)\n"
              << "5. Вернуть карту\n"
              << "Выберите действие: ";
}

// Функция для безопасного ввода целого числа
int safe_get_int() {
    int value;
    while (!(std::cin >> value)) {
        std::cin.clear();  // сбрасываем флаг ошибки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // очищаем буфер
        std::cout << "Ошибка! Введите число: ";
    }
    return value;
}

// Функция для безопасного ввода вещественного числа
double safe_get_double() {
    double value;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка! Введите число: ";
    }
    return value;
}

int main() {
    // Вайбкодинг-симуляция логов и хранилища в рабочей папке
    ATMEngine atm("atm_journal.bin", "cards_db.txt");
    std::cout << "[Система] Инициализация успешна. Данные восстановлены из бинарного лога.\n";

    while (true) {
        if (!atm.has_session()) {
            std::cout << "\nВведите номер карты (16 цифр) или 'exit' для выключения банкомата: ";
            std::string card_num;
            std::cin >> card_num;
            
            if (card_num == "exit") break;

            if (!atm.insert_card(card_num)) {
                std::cout << "Карта не найдена в системе!\n";
                continue;
            }

            if (atm.is_current_card_blocked()) {
                std::cout << "Эта карта ЗАБЛОКИРОВАНА. Обратитесь в банк.\n";
                atm.logout();
                continue;
            }

            bool auth_success = false;
            for (int i = 0; i < 3; ++i) {
                std::cout << "Введите PIN (Попытка " << i + 1 << " из 3): ";
                std::string pin;
                std::cin >> pin;

                if (atm.enter_pin(pin)) {
                    auth_success = true;
                    break;
                } else {
                    std::cout << "Неверный PIN!\n";
                    if (atm.is_current_card_blocked()) {
                        std::cout << "Превышено количество попыток! Карта заблокирована.\n";
                        break;
                    }
                }
            }
            if (!auth_success) {
                atm.logout();
                continue;
            }
        }

        show_menu();
        int choice = safe_get_int();  // используем безопасный ввод

        if (choice == 1) {
            std::cout << "Ваш баланс: " << atm.check_balance() << " руб.\n";
        } 
        else if (choice == 2) {
            std::cout << "Введите сумму пополнения: ";
            double amt = safe_get_double();  // безопасный ввод для double
            if (amt > 0 && atm.deposit(amt)) {
                std::cout << "Успешно зачислено!\n";
            } else {
                std::cout << "Ошибка операции. Сумма должна быть положительной.\n";
            }
        } 
        else if (choice == 3) {
            std::cout << "Введите сумму для снятия (Макс. 10 000 за раз): ";
            double amt = safe_get_double();
            if (amt <= 0) {
                std::cout << "Неверная сумма.\n";
                continue;
            }
            double fee = 0;
            int res = atm.withdraw(amt, fee);
            if (res == 0) {
                std::cout << "Успешно! Снято: " << amt << " руб. Комиссия: " << fee << " руб.\n";
            } else if (res == 1) {
                std::cout << "Ошибка: Превышен лимит на однократное снятие (10 000 руб).\n";
            } else if (res == 2) {
                std::cout << "Ошибка: Превышен суточный лимит снятия (50 000 руб).\n";
            } else if (res == 3) {
                std::cout << "Ошибка: Недостаточно средств на балансе (с учетом комиссии).\n";
            } else {
                std::cout << "Неверная сумма.\n";
            }
        } 
        else if (choice == 4) {
            atm.show_history();
        } 
        else if (choice == 5) {
            std::cout << "Сессия завершена. Заберите карту.\n";
            atm.logout();
        } 
        else {
            std::cout << "Неверный пункт меню. Выберите 1-5.\n";
        }
    }

    return 0;
}