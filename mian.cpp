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

double Vidurkis(Studentas studentas) {
    double suma = 0;
    for (int i = 0; i < studentas.namuDarbai.size(); i++) {
        suma += studentas.namuDarbai[i];
    }
    suma += studentas.egzaminas;
    return  round(suma / (studentas.namuDarbai.size()+1) * 100.0) / 100.0;
}

int main() {
    Studentas studentas;
    cout << "Iveskite studento varda: ";
    cin >> studentas.vardas;

    cout << "Iveskite studento pavarde: ";
    cin >> studentas.pavarde;

    int ndSkaicius = 5;

    for (int i=0; i< ndSkaicius; i++) {
        int pazymys;
        cout << " Iveskite pazymi uz " << i+1 << "-uosius namu darbus? ";
        cin >> pazymys;
        studentas.namuDarbai.push_back(pazymys);
    }

    cout << "Iveskite egzamino pazymi: ";
    cin >> studentas.egzaminas;
    
    cout << studentas.vardas << " " << studentas.pavarde << " " << Vidurkis(studentas)<< endl;

    return 0;
}