#include <iostream>
#include <string>

using namespace std;

class Shop {
    private:
        string name;
        long long int phone_number;
        string address;
        int work_time;
    public:
        Shop() {
            name = "";
            phone_number = 0;
            address = "";
            work_time = 0;
        }
        Shop(string name_t, long long int phone_number_t, string address_t, int work_time_t) {
            name = name_t;
            phone_number = phone_number_t;
            address = address_t;
            work_time = work_time_t;
        }
        void set_name(string name_t) {
            name = name_t;
        }
        void set_phone(long long int phone_number_t) {
            phone_number = phone_number_t;
        }
        void set_address(string address_t) {
            address = address_t;
        }
        void set_work_time(int work_time_t) {
            work_time = work_time_t;
        }

        string get_name() {
            return name;
        }
        long long int set_phone() {
            return phone_number;
        }
        string get_address() {
            return address;
        }
        int get_work_time() {
            return work_time;
        }

        void printInfo() {
        cout << "--- Информация о магазине ---" << endl;
        cout << "Название: " << name << endl;
        cout << "Телефон: " << phone_number << endl;
        cout << "Адрес: " << address << endl;
        cout << "Время работы (ч): " << work_time << endl;
        }
};

class TradeShop : public Shop {
    private:
        string trade_type;

    public:
        TradeShop() : Shop() {
            trade_type = "";
        }

        TradeShop(string name, long long int phone_number, string address, int work_time, string trade_type_t)
            : Shop(name, phone_number, address, work_time) {
            trade_type = trade_type_t;
        }

        void set_tradeType(string trade_type_t) { 
            trade_type = trade_type_t; 
        }
        string get_tradeType() { 
            return trade_type; 
        }

        void printInfo() {
            Shop::printInfo(); 
            cout << "Тип торговли: " << trade_type << endl;
        }
};

int main() {
    cout << "Суперкласс: " << endl;
    Shop shop1; 
    shop1.printInfo();
    cout << endl;

    Shop shop2("Ашан", 88001000000, "ул. Ленина, д. 10", 12);
    shop2.printInfo();
    cout << endl;

    shop1.set_name("Леруа Мерлен");
    shop1.set_work_time(14);
    
    cout << "Новое имя: " << shop1.get_name() << endl;
    cout << "Новое время работы: " << shop1.get_work_time() << " ч." << endl;
    cout << endl;

    cout << "Дочерний класс: " << endl;

    TradeShop tradeShop1("ОптТоргСибирь", 83912003040, "ул. Северная, д. 5", 9, "Оптовая");
    tradeShop1.printInfo();
    cout << endl;

    tradeShop1.set_tradeType("Розничная");
    tradeShop1.printInfo();
}