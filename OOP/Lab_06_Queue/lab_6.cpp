#include <iostream>
#include <string>
#include <algorithm>
#include <deque>

using namespace std;

class Questionnaire {
    private:
        string name;
        int age;
        string gender;
        string education;
        bool answer;
    public:
        Questionnaire(string n, int a, string g, string ed, bool ans) 
            : name(n), age(a), gender(g), education(ed), answer(ans) {}

        string getName() const { return name; }
        int getAge() const { return age; }
        string getGender() const { return gender; }
        string getEducation() const { return education; }
        bool getAnswer() const { return answer; }

        void printAll() const {
            cout << "ФИО: " << name 
                << " | Возраст: " << age 
                << " | Пол: " << gender 
                << " | Образование: " << education 
                << " | Ответ: " << (answer ? "ДА" : "НЕТ") << "\n";
        }
};

bool sortQ(const Questionnaire& a, const Questionnaire& b) {
    return a.getName() < b.getName();
}

int main() {
    deque<Questionnaire> dataBase;

    int count_objects;
    cout << "Введите количество объектов >> ";
    cin >> count_objects;
    cin.ignore(1000, '\n');

    for (int i = 0; i < count_objects; i++) {
        string name;
        int age;
        string gender;
        string education;
        string t;
        bool answer;

        cout << "Введите ФИО >> ";
        getline(cin, name);
        cout << "Введите возраст >> ";
        cin >> age;
        cin.ignore(1000, '\n');
        cout << "Введите пол >> ";
        getline(cin, gender);
        cout << "Введите ур. образования >> ";
        getline(cin, education);
        cout << "Введите ответ (да/нет) >> ";
        getline(cin, t);
        answer = (t == "да") ? true : false;

        dataBase.push_back(Questionnaire(name, age, gender, education, answer));
    }

    sort(dataBase.begin(), dataBase.end(), sortQ);

    int count_AnsA = 0;
    int count_AnsB = 0;
    int count_AnsC = 0;

    for (const auto& curr : dataBase) {
        curr.printAll();

        string g = curr.getGender();
        string ed = curr.getEducation();
        int a = curr.getAge();
        bool ans = curr.getAnswer();

        if (g == "муж" && a > 40 && ed == "высшее" && ans) {
            count_AnsA++;
        }
        if (g == "жен" && a < 30 && ed == "среднее" && !ans) {
            count_AnsB++;
        }
        if (g == "муж" && a < 25 && ed == "начальное" && ans) {
            count_AnsC++;
        }
    }

    cout << "Вопрос А: " << count_AnsA 
        << " \nВопрос B: " << count_AnsB
        << " \nВопрос C: " << count_AnsC << endl;
}