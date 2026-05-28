#pragma once
#include "card.h"
#include <unordered_map>
#include <string>

class FileStorage {
private:
    std::string cards_filename;

public:
    FileStorage(std::string cards_file);
    std::unordered_map<std::string, Card> load_cards();
    void save_cards(const std::unordered_map<std::string, Card>& cards);
};
