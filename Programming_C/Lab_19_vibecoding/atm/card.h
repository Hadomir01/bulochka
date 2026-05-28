#pragma once
#include <string>

class Card {
private:
    std::string card_number;
    std::string pin;
    bool is_blocked;
    int pin_attempts;

public:
    Card(std::string num, std::string p, bool blocked = false, int attempts = 0);
    
    std::string get_number() const { return card_number; }
    bool check_pin(const std::string& input_pin);
    bool blocked() const { return is_blocked; }
    void block() { is_blocked = true; }
    int get_attempts() const { return pin_attempts; }
    void reset_attempts() { pin_attempts = 0; }
};
