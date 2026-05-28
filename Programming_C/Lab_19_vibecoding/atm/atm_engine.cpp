#include "atm_engine.h"
#include "recovery.h"
#include <iostream>
#include <chrono>
#include <cstring>
#include <algorithm>

ATMEngine::ATMEngine(std::string journal_file, std::string cards_file) 
    : is_authenticated(false), current_card_num("") {
    storage = std::make_unique<FileStorage>(cards_file);
    cards = storage->load_cards();
    
    // Пересоздаем состояние аккаунтов на базе бинарного лога (Crash Recovery)
    Recovery::restore_state(journal_file, accounts);
    
    journal = std::make_unique<Journal>(journal_file);
}

bool ATMEngine::insert_card(const std::string& card_num) {
    if (cards.find(card_num) != cards.end()) {
        current_card_num = card_num;
        return true;
    }
    return false;
}

bool ATMEngine::is_current_card_blocked() const {
    auto it = cards.find(current_card_num);
    if (it != cards.end()) {
        return it->second.blocked();
    }
    return true;
}

bool ATMEngine::enter_pin(const std::string& pin) {
    auto& card = cards.at(current_card_num);
    if (card.check_pin(pin)) {
        is_authenticated = true;
        storage->save_cards(cards);
        return true;
    }
    storage->save_cards(cards);
    return false;
}

void ATMEngine::logout() {
    is_authenticated = false;
    current_card_num = "";
}

double ATMEngine::check_balance() const {
    if (!is_authenticated) return 0.0;
    if (accounts.find(current_card_num) == accounts.end()) return 0.0;
    return accounts.at(current_card_num).get_balance();
}

bool ATMEngine::deposit(double amount) {
    if (!is_authenticated || amount <= 0) return false;
    
    int64_t ts = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
        
    Transaction tx;
    std::strncpy(tx.card_number, current_card_num.c_str(), 16);
    tx.card_number[16] = '\0';
    tx.type = TransactionType::DEPOSIT;
    tx.amount = amount;
    tx.fee = 0.0;
    tx.timestamp = ts;

    accounts[current_card_num].deposit(amount, ts);
    accounts[current_card_num].add_transaction_to_history(tx);
    journal->append_transaction(tx);
    return true;
}

int ATMEngine::withdraw(double amount, double& calculated_fee) {
    if (!is_authenticated || amount <= 0) return 4;
    if (amount > MAX_SINGLE_WITHDRAWAL) return 1;

    int64_t ts = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();

    auto& acc = accounts[current_card_num];
    acc.reset_daily_limit_if_needed(ts);

    if (acc.get_daily_withdrawn() + amount > MAX_DAILY_WITHDRAWAL) return 2;

    calculated_fee = amount * 0.01;
    if (calculated_fee < 30.0) calculated_fee = 30.0;

    if (!acc.withdraw(amount, calculated_fee, ts)) return 3;

    Transaction tx;
    std::strncpy(tx.card_number, current_card_num.c_str(), 16);
    tx.card_number[16] = '\0';
    tx.type = TransactionType::WITHDRAWAL;
    tx.amount = amount;
    tx.fee = calculated_fee;
    tx.timestamp = ts;

    acc.add_transaction_to_history(tx);
    journal->append_transaction(tx);
    return 0;
}

void ATMEngine::show_history() const {
    if (!is_authenticated) return;
    if (accounts.find(current_card_num) == accounts.end() || accounts.at(current_card_num).get_history().empty()) {
        std::cout << "История операций пуста.\n";
        return;
    }

    const auto& history = accounts.at(current_card_num).get_history();
    // Выводим в обратном порядке (сначала свежие)
    for (auto it = history.rbegin(); it != history.rend(); ++it) {
        std::cout << "[" << it->timestamp << "] "
                  << (it->type == TransactionType::DEPOSIT ? "Пополнение: +" : "Снятие: -")
                  << it->amount << " руб. (Комиссия: " << it->fee << " руб.)\n";
    }
}
