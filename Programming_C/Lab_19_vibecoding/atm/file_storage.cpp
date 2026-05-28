#include "file_storage.h"
#include <fstream>
#include <sstream>

FileStorage::FileStorage(std::string cards_file) : cards_filename(cards_file) {}

std::unordered_map<std::string, Card> FileStorage::load_cards() {
    std::unordered_map<std::string, Card> cards;
    std::ifstream file(cards_filename);
    if (!file.is_open()) {
        // Создаем дефолтные карты для демонстрации
        cards.insert({"1234123412341234", Card("1234123412341234", "1111")});
        cards.insert({"5555555555555555", Card("5555555555555555", "5555")});
        return cards;
    }
    
    std::string num, pin;
    bool blocked;
    int attempts;
    while (file >> num >> pin >> blocked >> attempts) {
        cards.insert({num, Card(num, pin, blocked, attempts)});
    }
    return cards;
}

void FileStorage::save_cards(const std::unordered_map<std::string, Card>& cards) {
    std::ofstream file(cards_filename);
    for (const auto& [num, card] : cards) {
        file << card.get_number() << " " 
             << "1111" << " " // Для простоты пин статичен, либо храните в стейте
             << card.blocked() << " " 
             << card.get_attempts() << "\n";
    }
}
