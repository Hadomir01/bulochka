#pragma once
#include "account.h"
#include <unordered_map>
#include <string>

class Recovery {
public:
    static void restore_state(const std::string& journal_path, std::unordered_map<std::string, Account>& accounts);
};
