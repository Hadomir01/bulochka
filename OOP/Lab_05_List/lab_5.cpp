#include <iostream>
#include <string>
#include <list>

using namespace std;

class Toy {
    private:
        string name;
        int price;
        string shop;
    public:
        Toy() {
            name = "";
            price = 0;
            shop = "";
        }

        Toy(string n, int p, string sh) {
            name = n;
            price = p;
            shop = sh;
        }

        void setName(string n) { name = n; }
        void setPrice(int p) { price = p; }
        void setShop(string sh) { shop = sh; }

        string getName() const { return name; }
        int getPrice() const { return price; }
        string getShop() const { return shop; }

        virtual void printAll() const {
            cout << "Название: " << name << endl;
            cout << "Стоимость: " << price << endl;
            cout << "Магазин: " << shop << endl;
        }
};

int main() {
    list<Toy> toy_list;
    int N;
    cout << "Сколько игрушек запишем >> ";
    cin >> N;
    cin.ignore(100, '\n');

    for (int i = 0; i < N; i++) {
        string name, shop;
        int price;

        cout << "\nИгрушка №" << i + 1 << endl;

        cout << "Введите название: ";
        getline(cin, name);

        cout << "Введите стоимость: ";
        cin >> price;
        cin.ignore(100, '\n');

        cout << "Введите название магазина: ";
        getline(cin, shop);

        toy_list.push_back(Toy(name, price, shop));
    }

    bool found = false;
    while (!found) {
        string check;
        cout << "\nВведите название для проверки: ";
        getline(cin, check); 

        for (const auto& i : toy_list) {
            if (i.getName() == check) {
                cout << "===== Найдено! =====" << endl;
                i.printAll();
                found = true;
            }
        }

        if (!found) {
            cout << "Такой игрушки нет!" << endl;
        }
    }
}