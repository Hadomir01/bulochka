#include "class.h"

int main() {
    ifstream Filein("dataBase.txt");

    ofstream Fileout("dataBase.bin", ios::binary);

    int n;
    Filein >> n;
    Filein.ignore(1000, '\n');

    int written = 0;
    for (int k = 0; k < n; k++) {
        Employee temp;
        if (!temp.readFromText(Filein)) break;
        temp.writeBin(Fileout);
        written++;
    }
    Filein.close();
    Fileout.close();
    cout << "Записано сотрудников в dataBase.bin: " << written << endl;
    return 0;
}