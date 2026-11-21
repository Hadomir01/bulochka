#include "class.h"

int main() {
    ifstream File("dataBase.bin", ios::binary);

    Employee temp;

    double maxSalary = 0;
    cout << "Содержимое файла:" << endl;
    while (temp.readBin(File)) {
        temp.print();
        if (temp.getSalary() > maxSalary) maxSalary = temp.getSalary();
    }

    File.clear();
    File.seekg(0, ios::beg);
    int count = 0;
    cout << "\nСотрудники с максимальной зарплатой (" << maxSalary << "):" << endl;
    while (temp.readBin(File)) {
        if (temp.getSalary() == maxSalary) {
            temp.print();
            count++;
        }
    }
    File.close();

    cout << "\nКоличество сотрудников с максимальной зарплатой: " << count << endl;
    return 0;
}