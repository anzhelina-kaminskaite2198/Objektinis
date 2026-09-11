#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <algorithm>
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
    double ndVidurkis;
    if (studentas.namuDarbai.size() == 0) {
        ndVidurkis = 0;
    } else {
        ndVidurkis = suma / studentas.namuDarbai.size();
    }
    double galutinis = (ndVidurkis * 0.4) + (studentas.egzaminas * 0.6);
    return  round(galutinis * 100.0) / 100.0;
}

double Mediana(Studentas studentas) {
    vector<int> ndPazymiai = studentas.namuDarbai;
    sort(ndPazymiai.begin(), ndPazymiai.end());
    double mediana;
    int n = ndPazymiai.size();
    if (n == 0) {
        mediana = 0;
    } else if (n % 2 == 0) {
        mediana = (ndPazymiai[n / 2 - 1] + ndPazymiai[n / 2]) / 2.0;
    } else {
        mediana = ndPazymiai[n / 2];
    }
    double galutinis = (mediana * 0.4) + (studentas.egzaminas * 0.6);
    return round(galutinis * 100.0) / 100.0;
}

int main() {
    string a ; 
    while (true) {
        cout << "Ar norite ivesti nauja studenta? (Taip/Ne) ";
        cin >> a;
        if (a != "Taip" && a != "taip" && a != "Ne" && a != "ne") {
            cout << "Klaida: iveskite 'Taip' arba 'Ne'." << endl;
            continue;
        } else if (a == "Ne" || a == "ne") {
            break;
        } 
        if (a == "Taip"|| a == "taip") {
            Studentas studentas;

            cout << "Studento vardas: ";
            cin >> studentas.vardas;

            cout << "Studento pavarde: ";
            cin >> studentas.pavarde;
            cin.ignore();

            string ivertinimas;
            cout << "\nKad baigti namu darbu ivedima paskauskite ENTER 2 kartus\n ";

            while (true) {
                cout  << "Iveskite namu darbu pazymi:";
                getline(cin, ivertinimas);

                if ( ivertinimas.empty() ) {
                    break;
                }

                try {
                    double pazymys = stod(ivertinimas);

                    if (stod(ivertinimas) < 0 || stod(ivertinimas) > 10) {
                    cout << "Klaida: ivestas pazymys turi buti nuo 0 iki 10, bandykite dar karta." << endl;
                    continue;
                    }
                    studentas.namuDarbai.push_back(pazymys);
                } catch (const invalid_argument& e) {
                    cout << "Klaida: ivestas ne skaicius, bandykite dar karta." << endl;
                    }
            }

            string exam;
            
           while (true) {
                cout << "Egzamino pazymys: ";
                getline(cin, exam);

                if (exam.empty()) {
                    exam = "0";
                }

                try {
                    double egzoPazymys = stod(exam);

                    if (egzoPazymys < 0 || egzoPazymys > 10) {
                        cout << "Klaida: pazymys turi buti nuo 0 iki 10." << endl;
                        continue;
                    }

                    studentas.egzaminas = egzoPazymys;
                    break;
                }
                catch (const invalid_argument& e) {
                    cout << "Klaida: ivestas ne skaicius. Bandykite dar karta." << endl;
                }
            }

            studentai.push_back(studentas);
        }
    }
    cout << "\nAr norite gauti galutini rezultata pagal vidurki (1) ar mediana(2)? (1/2) ";
    int pasirinkimas;
    cin >> pasirinkimas;
    cin.ignore();

    if (pasirinkimas == 2) {
        for (Studentas studentas : studentai) {
            cout << studentas.vardas << " " 
                 << studentas.pavarde << " " 
                 << fixed << setprecision(2) << Mediana(studentas) << endl;
        }
    } else {
        for (Studentas studentas : studentai) {
            cout << studentas.vardas << " " 
                 << studentas.pavarde << " " 
                 << fixed << setprecision(2) << Vidurkis(studentas) << endl;
        }
    }

    return 0;
}