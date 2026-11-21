#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
        void output() const {
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
        string get_category() const {
            return category;
        }
        string get_country() const {
            return country;
        }
        int get_id() const {
            return id;
        }

};

bool sort_by_id(const Product& a, const Product& b) {
    return a.get_id() < b.get_id();
}

int main() {
    int count_objects;
    cout << "Введите количество объектов >> ";
    cin >> count_objects;
    cin.ignore(1000, '\n');
    
    vector<Product> Watch;
    vector<Product> Wrist_Watch;

    for (int i = 0; i < count_objects; i++) {
        string new_category;
        string new_country;
        int new_id;
        cout << "Введите категорию часов >> ";
        getline(cin, new_category);
        cout << "Введите страну-производителя >> ";
        getline(cin, new_country);
        cout << "Введите id часов >> ";
        cin >> new_id;
        cin.ignore(1000, '\n');
        Watch.push_back(Product(new_category, new_country, new_id));
    }

    cout << "Вектор из всех часов\n" << endl; 
    for (const auto& product : Watch) {
        product.output();
    }

    cout << endl;

    for (const auto& product : Watch) {
        if (product.get_category() == "Наручные" || product.get_category() == "наручные") {
            Wrist_Watch.push_back(product);
        }
    }

    cout << "Вектор из наручных часов\n" << endl; 
    for (const auto& product : Wrist_Watch) {
        product.output();
    }

    cout << endl;

    if (!Wrist_Watch.empty()) {
        cout << "=== Вектор наручных часов не пуст! ===" << endl; 
        cout << "Проведем сортировку (по id)" << endl;
        sort(Wrist_Watch.begin(), Wrist_Watch.end(), sort_by_id);
        cout << endl;
    }

    for (const auto& product : Wrist_Watch) {
        product.output();
    }
    cout << endl;

    cout << "=== Добавим новый объект ===\n" << endl;

    Product new_wrist_watch("Наручные", "Япония", 45);

    auto it = upper_bound(Wrist_Watch.begin(), Wrist_Watch.end(), new_wrist_watch, sort_by_id);
    Wrist_Watch.insert(it, new_wrist_watch);

    for (const auto& product : Wrist_Watch) {
        product.output();
    }

    return 0;
}