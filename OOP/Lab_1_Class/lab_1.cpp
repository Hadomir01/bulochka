#include <iostream>
#include <string>

using namespace std;

class Product {
    private:
        string category;
        string country;
        int id;
    public:
        Product(string ctg, string ctr, int id_prod) {
            category = ctg;
            country = ctr;
            id = id_prod;
        }
        void output() {
            cout << "Категория товара: " << category << endl;
            cout << "Страна-производитель: " << country << endl;
            cout << "ID товара: " << id << endl;
        }
        void set_category(string ctg) {
            category = ctg;
        }
        void set_country(string ctr) {
            country = ctr;
        }
        void set_id(int id_prod) {
            id = id_prod;
        }
        string get_category() {
            return category;
        }
        string get_country() {
            return country;
        }
        int get_id() const {
            return id;
        }

};

int main() {
    Product *Clock = new Product("Часы наручные", "Россия", 0003);

    Clock->output();

    cout << "Категория товара: " << Clock->get_category() << endl;
    cout << "Страна-производитель: " << Clock->get_country() << endl;
    cout << "ID товара: " << Clock->get_id() << endl;

    Clock->set_category("Часы настенные");
    Clock->set_country("Швейцария");
    Clock->set_id(0004);

    Clock->output();

    delete Clock;

    return 0;
}