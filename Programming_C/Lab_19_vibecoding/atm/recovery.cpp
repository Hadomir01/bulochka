#include "recovery.h"
#include <fstream>

void Recovery::restore_state(const std::string& journal_path, std::unordered_map<std::string, Account>& accounts) {
    std::ifstream file(journal_path, std::ios::binary);
    if (!file.is_open()) return;

    Transaction tx;
    while (file.read(reinterpret_cast<char*>(&tx), sizeof(Transaction))) {
        std::string card_num(tx.card_number);
        Account& acc = accounts[card_num];

        if (tx.type == TransactionType::DEPOSIT) {
            acc.deposit(tx.amount, tx.timestamp);
        } else if (tx.type == TransactionType::WITHDRAWAL) {
            acc.withdraw(tx.amount, tx.fee, tx.timestamp);
        }
        acc.add_transaction_to_history(tx);
    }
}
