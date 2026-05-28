#pragma once
#include "transaction.h"
#include <string>
#include <fstream>

class Journal {
private:
    std::string filename;
    std::ofstream log_file;

public:
    Journal(std::string file_path);
    ~Journal();
    void append_transaction(const Transaction& tx);
};
