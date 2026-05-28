#include "card.h"

Card::Card(std::string num, std::string p, bool blocked, int attempts)
    : card_number(num), pin(p), is_blocked(blocked), pin_attempts(attempts) {}

bool Card::check_pin(const std::string& input_pin) {
    if (is_blocked) return false;
    if (pin == input_pin) {
        pin_attempts = 0;
        return true;
    }
    pin_attempts++;
    if (pin_attempts >= 3) {
        is_blocked = true;
    }
    return false;
}
