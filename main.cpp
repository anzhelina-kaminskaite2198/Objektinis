#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

struct Studentas {
        string vardas;
        string pavarde;
        vector<double> namuDarbai;
        double egzaminas;
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
    vector<double> ndPazymiai = studentas.namuDarbai;
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

int IvestiStudenta() {

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

            if (pazymys < 0 || pazymys > 10) {
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
        } catch (const invalid_argument& e) {
            cout << "Klaida: ivestas ne skaicius. Bandykite dar karta." << endl;
            }
    }

    studentai.push_back(studentas);

    return 0;
}

int ParodytiStudentus() {
    cout << "Vardas" << setw(15) 
         << "Pavarde" << setw(20) 
         << "Galutinis (vid.)" << setw(20) 
         << "Galutinis (med.)" << endl
         << "---------------------------------------------------------------" << endl;

    for (Studentas studentas : studentai) {
        cout << studentas.vardas << setw(15) 
             << studentas.pavarde << setw(20) 
             << fixed << setprecision(2) << Mediana(studentas) << setw(20) 
             << fixed << setprecision(2) << Vidurkis(studentas) << endl;
    }

    return 0;
}

int main() {

    int pasirinkimas;
    
    while (true) {
        cout << "              MENIU\n"
        << "-----------------------------------\n"
        << "1  Ivesti nauja studenta\n"
        << "2  Rodyti visus studentus\n"
        << "3  Iseiti\n\n"
        << "Pasirinkite veiksma:";
    
        cin >> pasirinkimas;
        switch (pasirinkimas) {
        
            case 1: {
                IvestiStudenta();
                continue;
            }

            case 2: {
                ParodytiStudentus();
                continue;
            }
            case 3:{
                return 0;;
            }
            default:
                cout << "Klaida: netinkamas pasirinkimas." << endl;
                return 0;
        }

    }
        return 0;
}