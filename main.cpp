#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>

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

    int pasirinkimas_nd;
    while (true) {
        cout << "1  Ivesti namu darbu pazymius\n" 
            << "2  Sugeneruoti namu daru pazymius\n";
        cin >> pasirinkimas_nd;
        if (pasirinkimas_nd == 1 || pasirinkimas_nd == 2) {
            break;
        } else {
            cout << "Klaida: netinkamas pasirinkimas.\n" << endl;
        }
    }
    cin.ignore();

    switch (pasirinkimas_nd) {
        case 1: {

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
            break;
        }
        case 2: {
            int ndSkaicius;
            cout << "Iveskite kiek namu darbu pazymiu norite sugeneruoti:";
            cin >> ndSkaicius;
            for (int i=0; i < ndSkaicius; i++) {
                double ndPazymys = rand() % 11;
                studentas.namuDarbai.push_back(ndPazymys);
            }
            cout << "Sugeneruoti namu darbu pazymiai: [";

            for (int i = 0; i < studentas.namuDarbai.size(); i++) {
                cout << studentas.namuDarbai[i];
                if (i < studentas.namuDarbai.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "]" << endl;
            break;
        }
    } 


    int pasirinkimas_egz;
    while (true) {
        cout << "1  Ivesti egzamino pazymi\n" 
             << "2  Sugeneruoti egzamino pazymi\n";
        cin >> pasirinkimas_egz;
        if (pasirinkimas_egz == 1 || pasirinkimas_egz == 2) {
            break;
        } else {
            cout << "\nKlaida: netinkamas pasirinkimas.\n" << endl;
        }
    }
    cin.ignore(); 

    switch (pasirinkimas_egz) {
        case 1: {
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
            break;
        }
        case 2: {
            double egzPazymys = rand() % 11;
            studentas.egzaminas = egzPazymys;
            cout << "Sugeneruotas egzamino pazymys: " << egzPazymys << endl;
            break;
        }
    }
    
    studentai.push_back(studentas);

    return 0;
}

int ParodytiStudentus() {
    cout << left
         << setw(15) << "Vardas" 
         << setw(20) << "Pavarde"
         << setw(20) << "Galutinis (vid.)"
         << setw(20) << "Galutinis (med.)" << endl
         << "---------------------------------------------------------------" << endl;

    for (Studentas studentas : studentai) {
        cout << left 
             << setw(15) << studentas.vardas 
             << setw(20) << studentas.pavarde 
             << setw(20) << fixed << setprecision(2) << Mediana(studentas) 
             << setw(20) << fixed << setprecision(2) << Vidurkis(studentas) << endl;
    }

    return 0;
}

int SkaitytiIsFailo() {
    ifstream failas ("kursiokai.txt");

    if (!failas) {
        cout << "Nepavyko atidaryti failo." << endl;
        return 0;
    }

    string eilute;
    getline(failas, eilute);

    while (getline(failas, eilute)) {
        stringstream ss(eilute);
        Studentas studentas;
        ss >> studentas.vardas;
        ss >> studentas.pavarde;

        string strPazymys;
        ss >> strPazymys;
        try
        {
            double pazymys = stod(strPazymys);

            if ( pazymys >= 0 && pazymys <= 10) {
                studentas.namuDarbai.push_back(pazymys);
            } 
        }
        catch(const invalid_argument& e){
        }
        
        studentas.egzaminas = studentas.namuDarbai.back();
        studentas.namuDarbai.pop_back();

        studentai.push_back(studentas);
    }
    
    failas.close();
    return 0;
}

int main() {

    int pasirinkimas;
    
    while (true) {
        cout << "\n              MENIU\n"
        << "-----------------------------------\n"
        << "1  Ivesti nauja studenta\n"
        << "2  Nuskaityti duomenis is failo\n"
        << "3  Rodyti visus studentus\n"
        << "4  Iseiti\n\n"
        << "Pasirinkite veiksma:";
    
        cin >> pasirinkimas;
        

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100000000, '\n');
            cout << "\n\nKlaida: netinkamas pasirinkimas." << endl;
            continue;
        }
        

        switch (pasirinkimas) {
        
            case 1: {
                IvestiStudenta();
                continue;
            }
            case 2: {
                SkaitytiIsFailo();
                cout << "Failas sekmingai nuskaitytas!" << endl;
                continue;
            }
            case 3: {
                ParodytiStudentus();
                continue;
            }
            case 4:{
                return 0;;
            }
            default:
                cout << "\n\nKlaida: netinkamas pasirinkimas." << endl;
                continue;
        }

    }
        return 0;
}