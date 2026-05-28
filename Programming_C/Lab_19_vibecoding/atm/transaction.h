#pragma once
#include <string>
#include <cstdint>

enum class TransactionType : uint8_t {
    DEPOSIT = 0,
    WITHDRAWAL = 1
};

struct Transaction {
    char card_number[17];
    TransactionType type;
    double amount;
    double fee;
    int64_t timestamp; // Unix time
};
