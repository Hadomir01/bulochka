#pragma once
#include "transaction.h"
#include <vector>
#include <string>

class Account {
private:
    double balance;
    std::vector<Transaction> history;
    double daily_withdrawn_amount;
    int64_t last_withdrawal_day;

    int64_t get_current_day_timestamp() const;

public:
    Account();
    
    double get_balance() const { return balance; }
    void deposit(double amount, int64_t ts = 0);
    bool withdraw(double amount, double fee, int64_t ts = 0);
    
    void add_transaction_to_history(const Transaction& tx);
    const std::vector<Transaction>& get_history() const { return history; }
    
    double get_daily_withdrawn() const { return daily_withdrawn_amount; }
    void reset_daily_limit_if_needed(int64_t current_ts);
};
