#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

// string tipo: studento vardą ir pavardę;
// int tipo: namų darbų tarpiniai rezultatai ir egzamino rezultatą;

struct Studentas {
        string vardas;
        string pavarde;
        vector<int> namuDarbai;
        int egzaminas;
    };

vector<Studentas> studentai;

double Vidurkis(Studentas studentas) {
    double suma = 0;
    for (int i = 0; i < studentas.namuDarbai.size(); i++) {
        suma += studentas.namuDarbai[i];
    }
    double ndVidurkis = suma / studentas.namuDarbai.size();
    double galutinis = (ndVidurkis * 0.4) + (studentas.egzaminas * 0.6);
    return  round(galutinis * 100.0) / 100.0;
}

int main() {
    string a = "Taip";
    while (a == "Taip") {
        cout << "Ar norite ivesti nauja studenta? (Taip/Ne) ";
        cin >> a;
        if (a == "Taip") {
            Studentas studentas;

            cout << "Studento vardas: ";
            cin >> studentas.vardas;

            cout << "Studento pavarde: ";
            cin >> studentas.pavarde;

            int ndSkaicius = 5;

            for (int i=0; i< ndSkaicius; i++) {
                int pazymys;
                cout << " Pazymys uz " << i+1 << "-uosius namu darbus? ";
                cin >> pazymys;
                studentas.namuDarbai.push_back(pazymys);
            }

            cout << "Egzamino pazymys: ";
            cin >> studentas.egzaminas;

            studentai.push_back(studentas);
        }
    
    for ( Studentas studentas : studentai) {
        cout << studentas.vardas << " " 
             << studentas.pavarde << " " 
             << fixed << setprecision(2) << Vidurkis(studentas) << endl;
    }
    }

    return 0;
}