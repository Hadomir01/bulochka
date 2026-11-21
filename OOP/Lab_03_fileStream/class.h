#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

class Employee {
    private:
        char surname[60];
        char initials[20];
        char position[60];
        char department[80];
        double salary;
    public:
        Employee() : salary(0) {
            surname[0] = initials[0] = position[0] = department[0] = '\0';
        }

        void copyStr(char* dst, const string& src, size_t size) {
            strncpy(dst, src.c_str(), size - 1);
            dst[size - 1] = '\0';
        }

        bool readFromText(istream& in) {
            string s, i, p, d;
            getline(in, s);
            getline(in, i);
            getline(in, p);
            getline(in, d);
            in >> salary;
            in.ignore(1000, '\n');
            copyStr(surname, s, sizeof(surname));
            copyStr(initials, i, sizeof(initials));
            copyStr(position, p, sizeof(position));
            copyStr(department, d, sizeof(department));
            return true;
        }

        void writeBin(ostream& out) {
            out.write((char*)(this), sizeof(Employee));
        }
        bool readBin(istream& in) {
            in.read((char*)(this), sizeof(Employee));
            return (bool)in;
        }

        double getSalary() const { 
            return salary; 
        }

        void print() const {
            cout << surname << " " << initials << " | " << position
                << " | " << department << " | " << salary << endl;
        }
};