#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class UK {
    private:
        string district;
        int number;
        string address; 

    public:
        UK() {
            district = "";
            number = 0;
            address = "";
        }

        UK(string district, int number, string address) {
            this->district = district;
            this->number = number;
            this->address = address;
        }

        void setDistrict(string district) { this->district = district; }
        void setNumber(int number) { this->number = number; }
        void setAddress(string address) { this->address = address; }

        string getDistrict() { return district; }
        int getNumber() { return number; }
        string getAddress() { return address; }

        void print() {
            cout << "Район: " << district << endl;
            cout << "Номер УК: " << number << endl;
            cout << "Юридический адрес: " << address << endl;
        }
};

class ZHEU : public UK {
    private:
        int zheuNumber;
        int housesCount; 
        int residentsCount; 
        double payment; 
        int paidCount; 

    public:
        ZHEU() : UK() {
            zheuNumber = 0;
            housesCount = 0;
            residentsCount = 0;
            payment = 0;
            paidCount = 0;
        }

        ZHEU(string district, int number, string address,
            int zheuNumber, int housesCount, int residentsCount,
            double payment, int paidCount)
            : UK(district, number, address) {
            this->zheuNumber = zheuNumber;
            this->housesCount = housesCount;
            this->residentsCount = residentsCount;
            this->payment = payment;
            this->paidCount = paidCount;
        }

        void setZheuNumber(int v) { zheuNumber = v; }
        void setHousesCount(int v) { housesCount = v; }
        void setResidentsCount(int v) { residentsCount = v; }
        void setPayment(double v) { payment = v; }
        void setPaidCount(int v) { paidCount = v; }

        int getZheuNumber() { return zheuNumber; }
        int getHousesCount() { return housesCount; }
        int getResidentsCount() { return residentsCount; }
        double getPayment() { return payment; }
        int getPaidCount() { return paidCount; }

        double calcDebt() {
            return (residentsCount - paidCount) * payment;
        }

        void print() {
            UK::print();
            cout << "Номер ЖЭУ: " << zheuNumber << endl;
            cout << "Число обслуживаемых домов: " << housesCount << endl;
            cout << "Число жильцов: " << residentsCount << endl;
            cout << "Оплата за месяц: " << payment << endl;
            cout << "Число оплативших: " << paidCount << endl;
            cout << "Общая задолженность: " << calcDebt() << endl;
        }
};

int main() {
    int n;
    cout << "Введите N: ";
    cin >> n;

    ifstream file("Pravim.txt");
    if (!file.is_open()) {
        cout << "Не удалось открыть файл Pravim.txt" << endl;
        return 1;
    }

    UK* arr = new UK[n];

    for (int i = 0; i < n; i++) {
        string district, address;
        int number;

        getline(file, district);
        file >> number;
        file.ignore();
        getline(file, address);

        arr[i].setDistrict(district);
        arr[i].setNumber(number);
        arr[i].setAddress(address);
    }
    file.close();

    string search;
    cin.ignore();
    cout << "Введите название района для поиска: ";
    getline(cin, search);

    bool found = false;
    for (int i = 0; i < n; i++) {
        if (arr[i].getDistrict() == search) {
            cout << endl;
            arr[i].print();
            found = true;
        }
    }
    if (!found) {
        cout << "УК в районе \"" << search << "\" не найдена" << endl;
    }

    delete[] arr;
    return 0;
}