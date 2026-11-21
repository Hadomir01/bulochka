#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class Pharmacy {
    private:
        string name;
        string address;
        int work_time;
    public:
        Pharmacy() {
            name = "";
            address = "";
            work_time = 0;
        }

        Pharmacy(string n, string a, int wt) {
            name = n;
            address = a;
            work_time = wt;
        }

        void setName(string n) { name = n; }
        void setAddress(string a) { address = a; }
        void setTime(int wt) { work_time = wt; }

        string getName() { return name; }
        string getAddress() { return address; }
        int getTime() { return work_time; }

        virtual void printAll() {
            cout << "Название: " << name << endl;
            cout << "Адрес: " << address << endl;
            cout << "Время работы: " << work_time << endl;
        }
};

class Internet_Pharmacy : public Pharmacy {
    private:
        int num_of_orders;
    public:
        Internet_Pharmacy() : Pharmacy() {
            num_of_orders = 0;
        }
        Internet_Pharmacy(string n, string a, int wt,
            int num) : Pharmacy(n, a, wt) {
            num_of_orders = num;
        }

        void setOrders(int num) { num_of_orders = num; }

        int getOrders() { return num_of_orders; }

        void printAll() override {
            Pharmacy::printAll();
            cout << "Среднесуточное число заказов " << num_of_orders << endl;
        }
};

auto is_desc = [](Pharmacy &a, Pharmacy &b){
    return a.getName() < b.getName();
};

int main() {
    int n, k;
    cout << "Введите число динамических объектов N >> ";
    cin >> n;
    cout << "Введите число статических объектов K >> ";
    cin >> k;

    ifstream file("apteka.txt");
    if (!file.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл apteka.txt" << endl;
        return 1;
    }

    Pharmacy* static_objects = new Pharmacy[k];
    Pharmacy** dynamic_objects = new Pharmacy*[n];
    vector<Pharmacy> until24;

    int count = 0;

    for (int i = 0; i < k; i++) {
        string name, address;
        int work_time;

        if (file >> name >> address >> work_time) {
            static_objects[i].setName(name);
            static_objects[i].setAddress(address);
            static_objects[i].setTime(work_time);
        }
        if (static_objects[i].getTime() == 24) {
            count++;
            until24.push_back(static_objects[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        string name, address;
        int work_time;
        if (file >> name >> address >> work_time) {
            dynamic_objects[i] = new Pharmacy(name, address, work_time);
        } else {
            dynamic_objects[i] = new Pharmacy();
        }
        if (dynamic_objects[i]->getTime() == 24) {
            count++;
            until24.push_back(*dynamic_objects[i]);
        }
    }
    file.close();

    cout << "\nСтатические" << endl;
    for (int i = 0; i < k; i++) {
        static_objects[i].printAll();
        cout << endl;
    }

    cout << "\nДинамические" << endl;
    for (int i = 0; i < n; i++) {
        if (dynamic_objects[i] != NULL) {
            dynamic_objects[i]->printAll();
            cout << endl;
        }
    }

    cout << "\nКоличество аптек, работающих до 24.00: " << count << "\n" << endl;

    sort(until24.begin(), until24.end(), is_desc);

    cout << "===== Отсортированные аптеки (24 часа) =====" << endl;
    for (auto i = until24.begin(); i != until24.end(); i++){
        i->printAll();
        cout << endl;
    }

    
}