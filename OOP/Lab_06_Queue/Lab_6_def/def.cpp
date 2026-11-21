#include <iostream>
#include <string>
#include <deque>

using namespace std;

class FlightTicket {
    private:
        string destination;
        int flightNumber;
        string passengerName;
        string departureDate;

    public:
        FlightTicket(string dest, int flightNum, string name, string date)
            : destination(dest), flightNumber(flightNum), passengerName(name), departureDate(date) {}

        void printInfo() const {
            cout << "Пассажир: " << passengerName 
                << " | Номер рейса: " << flightNumber 
                << " | Пункт назначения: " << destination 
                << " | Дата вылета: " << departureDate << "\n";
        }
};

void addTicket(deque<FlightTicket>& q) {
    string dest, name, date;
    int flightNum;

    cout << "\n--- Ввод новой заявки ---\n";
    cout << "Введите ФИО пассажира: ";
    getline(cin, name);
    cout << "Введите пункт назначения: ";
    getline(cin, dest);
    cout << "Введите номер рейса: ";
    cin >> flightNum;
    cin.ignore(1000, '\n'); 
    cout << "Введите желаемую дату вылета: ";
    getline(cin, date);

    q.push_back(FlightTicket(dest, flightNum, name, date));
}

void deleteTicket(deque<FlightTicket>& q) {
    if (q.empty()) {
        cout << "\nОчередь пуста!\n";
        return;
    }

    q.pop_front(); 
    cout << "Заявка удалена\n";
}

void printAllTickets(const deque<FlightTicket>& q) {
    if (q.empty()) {
        cout << "\nОчередь пуста\n";
        return;
    }

    cout << "\n--- Список всех заявок в очереди: ---\n";
    int index = 1;
    for (const auto& ticket : q) {
        cout << index++ << ". ";
        ticket.printInfo();
    }
}

int main() {
    deque<FlightTicket> ticketsQueue; 
    int choice = -1; 
    
    while (choice != 0) {
        cout << "\n1 - Добавить новую заявку\n";
        cout << "2 - Удалить текущую заявку\n";
        cout << "3 - Вывести все заявки на экран\n";
        cout << "0 - Выйти из программы\n";
        cout << ">> ";
        
        if (!(cin >> choice)) {
            cout << "Некорректный ввод!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        cin.ignore(1000, '\n');

        if (choice == 1) {
            addTicket(ticketsQueue);
        } else if (choice == 2) {
            deleteTicket(ticketsQueue);
        } else if (choice == 3) {
            printAllTickets(ticketsQueue);
        } else if (choice == 0) {
            cout << "Программа завершена\n";
        } else {
            cout << "Неверный пункт меню\n";
        }

    }
}