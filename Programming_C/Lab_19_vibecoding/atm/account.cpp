#include "account.h"
#include <chrono>

Account::Account() : balance(0.0), daily_withdrawn_amount(0.0), last_withdrawal_day(0) {}

int64_t Account::get_current_day_timestamp() const {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    return seconds / 86400; // Количество дней с эпохи
}

void Account::reset_daily_limit_if_needed(int64_t current_ts) {
    int64_t current_day = current_ts / 86400;
    if (current_day > last_withdrawal_day) {
        daily_withdrawn_amount = 0.0;
        last_withdrawal_day = current_day;
    }
}

void Account::deposit(double amount, int64_t ts) {
    balance += amount;
}

bool Account::withdraw(double amount, double fee, int64_t ts) {
    int64_t current_ts = (ts == 0) ? std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() : ts;
    reset_daily_limit_if_needed(current_ts);

    if (balance >= (amount + fee)) {
        balance -= (amount + fee);
        daily_withdrawn_amount += amount;
        return true;
    }
    return false;
}

void Account::add_transaction_to_history(const Transaction& tx) {
    if (history.size() >= 5) {
        history.erase(history.begin());
    }
    history.push_back(tx);
}
