#include <iostream>
#include <string>
#include <list>

using namespace std;

class File_System {
    private:
        string name;
        int date[3];
        int access_count;
    public:
        File_System() {
            name = "";
            date[0] = 0; date[1] = 0; date[2] = 0;
            access_count = 0;
        }

        File_System(string n, int d, int m, int y, int c) {
            name = n;
            date[0] = d;
            date[1] = m;
            date[2] = y;
            access_count = c;
        }

        void setName(string n) { name = n; }
        void setDate(int d, int m, int y) { date[0] = d; date[1] = m; date[2] = y; }
        void setCount(int sh) { access_count = sh; }

        string getName() const { return name; }
        int getDay() const { return date[0]; }
        int getMonth() const { return date[1]; }
        int getYear() const { return date[2]; }
        int getCount() const { return access_count; }

        virtual void printAll() const {
            cout << "Название: " << name << endl;
            cout << "Дата создания: " << date[0] << "." << date[1] << "." << date[2] << endl;
            cout << "Количество обращений: " << access_count << endl;
        }
};

void addFile(list<File_System>& catalog) {
    string name;
    int date[3];
    int access_count;

    cout << "Введите название: ";
    getline(cin, name);

    cout << "Введите Дату (дд мм гггг): ";
    cin >> date[0] >> date[1] >> date[2];
    cin.ignore(100, '\n');

    cout << "Введите количество обращений: ";
    cin >> access_count;
    cin.ignore(100, '\n');

    catalog.push_back(File_System(name, date[0], date[1], date[2], access_count));
}

void printCatalog(const list<File_System>& catalog) {
    if (catalog.empty()) {
        cout << "Каталог пуст!" << endl;
        return;
    }
    cout << " ===== Текущий каталог файлов =====" << endl;
    for (const auto& file : catalog) {
        file.printAll();
        cout << endl;
    }
}

void deleteFile(list<File_System>& catalog) {
    if (catalog.empty()) {
        cout << "Каталог пуст" << endl;
        return;
    }
    int d, m, y;
    cout << "Введите граничную дату для удаления (дд мм гггг)\n>> ";
    cin >> d >> m >> y;
    cin.ignore(100, '\n');

    auto it = catalog.begin();
    while (it != catalog.end()) {
        bool is_older = false;
        if (it->getYear() < y) {
            is_older = true;
        } else if (it->getYear() == y && it->getMonth() < m) {
            is_older = true;
        } else if (it->getYear() == y && it->getMonth() == m && it->getDay() < d) {
            is_older = true;
        }

        if (is_older) {
            it = catalog.erase(it);
        } else {
            ++it;
        }
    } 
}

void findMostAccessedFile(const list<File_System>& catalog) {
    if (catalog.empty()) {
        cout << "Каталог пуст!" << endl;
        return;
    }

    auto max_it = catalog.begin();
    for (auto it = catalog.begin(); it != catalog.end(); ++it) {
        if (it->getCount() > max_it->getCount()) {
            max_it = it;
        }
    }

    cout << "\n===== Файл с наибольшим количеством обращений =====" << endl;
    max_it->printAll();
}

int main() {
    list<File_System> system_list;

    while (1) {
        int choice;
        cout << "1 - добавить файл\n" 
        << "2 - вывести каталог\n"
        << "3 - удалить файл\n"
        << "4 - найти файл с самым большим числом обращений\n"
        << ">> ";
        
        cin >> choice;
        cin.ignore(100, '\n');

        if (choice == 1) {
            addFile(system_list);
        } else if (choice == 2) {
            printCatalog(system_list);
        } else if (choice == 3) {
            deleteFile(system_list);
        } else if (choice == 4) {
            findMostAccessedFile(system_list);
        } else if (choice == 0) {
            cout << "Завершение работы" << endl;
            break;
        } 
    }
}