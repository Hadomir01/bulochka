#pragma once
#include "card.h"
#include "account.h"
#include "journal.h"
#include "file_storage.h"
#include <unordered_map>
#include <memory>

class ATMEngine {
private:
    std::unordered_map<std::string, Card> cards;
    std::unordered_map<std::string, Account> accounts;
    std::unique_ptr<Journal> journal;
    std::unique_ptr<FileStorage> storage;
    
    std::string current_card_num;
    bool is_authenticated;

    const double MAX_SINGLE_WITHDRAWAL = 10000.0;
    const double MAX_DAILY_WITHDRAWAL = 50000.0;

public:
    ATMEngine(std::string journal_file, std::string cards_file);
    
    bool insert_card(const std::string& card_num);
    bool enter_pin(const std::string& pin);
    void logout();

    double check_balance() const;
    bool deposit(double amount);
    int withdraw(double amount, double& calculated_fee); 
    // Возвращает коды ошибок: 0 - успех, 1 - превышен лимит за раз, 2 - суточный лимит, 3 - мало денег
    
    void show_history() const;
    bool has_session() const { return is_authenticated; }
    bool is_current_card_blocked() const;
};
