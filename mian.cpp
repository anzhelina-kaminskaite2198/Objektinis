#include <iostream>
#include <vector>
#include <string>
using namespace std;

// string tipo: studento vardą ir pavardę;
// int tipo: namų darbų tarpiniai rezultatai ir egzamino rezultatą;

struct Studentas {
        string vardas;
        string pavarde;
        vector<int> namuDarbai;
        int egzaminas;
    };

int main() {
    Studentas studentas;
    cout << "Iveskite studento varda: ";
    cin >> studentas.vardas;

    cout << "Iveskite studento pavarde: ";
    cin >> studentas.pavarde;

    int ndSkaicius;
    cout << "Kiek namu darbu pazymiu vesite? ";
    cin >> ndSkaicius;

    for (int i=0; i< ndSkaicius; i++) {
        int pazymys;
        cout << " Iveskite pazymi uz " << i+1 << "-uosius namu darbus? ";
        cin >> pazymys;
        studentas.namuDarbai.push_back(pazymys);
    }
    
    cout << studentas.vardas << " " << studentas.pavarde << " ";

    for (int i = 0; i < studentas.namuDarbai.size(); i++) {
        cout << studentas.namuDarbai[i] << " ";
    }

    cout << studentas.egzaminas;

    return 0;
}