#include "journal.h"

Journal::Journal(std::string file_path) : filename(file_path) {
    log_file.open(filename, std::ios::binary | std::ios::app);
}

Journal::~Journal() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

void Journal::append_transaction(const Transaction& tx) {
    if (log_file.is_open()) {
        log_file.write(reinterpret_cast<const char*>(&tx), sizeof(Transaction));
        log_file.flush(); // Гарантия записи на диск на случай краша
    }
}
