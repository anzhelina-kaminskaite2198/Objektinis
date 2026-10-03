

#include "StudentuFunkcijos.h"
#include "Strukturos.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <limits>
#include <stdexcept>

using namespace std;

static random_device rd;
static mt19937 gen(rd());
static uniform_real_distribution<double>dist(0.0, 10.0);

vector<NeteisingiDuomenys> neteisingi;


bool IvedimoKlaidos (int kintamasis, int pasirinkimuSk) {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(100000000, '\n');
        cout << "\n\n\033[31mKlaida: netinkamas pasirinkimas.\033[0m" << endl;
        return false;
    }
    else if (kintamasis >= 1 && kintamasis <= pasirinkimuSk) {
        return true;
    } else {
        cout << "\033[31mKlaida: netinkamas pasirinkimas.\033[0m\n" << endl;
        return false;
    }
}

int PasirinktiRusiavimoParametra() {
    int pasirinkimas;
    while (true) {
        cout << "\nPagal ka rusiuoti studentus?\n"
             << "1  Pagal varda\n"
             << "2  Pagal pavarde\n"
             << "3  Pagal galutini bala\n";
        cin >> pasirinkimas;
        if (IvedimoKlaidos(pasirinkimas, 3)) { break; }
    }
    return pasirinkimas;
}

double Vidurkis(const Studentas& studentas) {
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

double Mediana(const Studentas& studentas) {
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

int IvestiStudenta(vector<Studentas>& studentai) {

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

        if (IvedimoKlaidos(pasirinkimas_nd, 2)) { break; }
        
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
                    cout << "\033[31mKlaida: ivestas pazymys turi buti nuo 0 iki 10, bandykite dar karta.\033[0m" << endl;
                    continue;
                    }
                    studentas.namuDarbai.push_back(pazymys);

                } catch (const invalid_argument& e) {
                    cout << "\033[31mKlaida: ivestas ne skaicius, bandykite dar karta.\033[0m" << endl;
                    }
            }
            break;
        }
        case 2: {
            int ndSkaicius;
            while (true){
                cout << "Iveskite kiek namu darbu pazymiu norite sugeneruoti:";
                cin >> ndSkaicius;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(100000000, '\n');
                    cout << "\n\n\033[31mKlaida: netinkamas pasirinkimas.\033[0m" << endl;
                    continue;
                }else if (ndSkaicius < 0) {
                    cout << "\033[31mKlaida: skaicius negali buti neigiamas.\033[0m" << endl;
                    continue;
                } else {
                    break;
                }
            }
            
            for (int i=0; i < ndSkaicius; i++) {
                double ndPazymys = dist(gen);
                studentas.namuDarbai.push_back(ndPazymys);
            }
            cout << "Sugeneruoti namu darbu pazymiai: [";

            for (int i = 0; i < studentas.namuDarbai.size(); i++) {
                cout << fixed << setprecision(2) << studentas.namuDarbai[i];
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

        if (IvedimoKlaidos( pasirinkimas_egz, 2)) { break; }
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
                        cout << "\033[31mKlaida: pazymys turi buti nuo 0 iki 10.\033[0m" << endl;
                        continue;
                    }

                    studentas.egzaminas = egzoPazymys;
                    break;
                } catch (const invalid_argument& e) {
                    cout << "\033[31mKlaida: ivestas ne skaicius. Bandykite dar karta.\033[0m" << endl;
                    }
            }
            break;
        }
        case 2: {
            double egzPazymys = dist(gen);
            studentas.egzaminas = egzPazymys;
            cout << "Sugeneruotas egzamino pazymys: " << fixed << setprecision(2) << egzPazymys << endl;
            break;
        }
    }
    
    studentas.galutinisVid = Vidurkis(studentas);
    studentas.galutinisMed = Mediana(studentas);
    studentai.push_back(studentas);
 

    

    return 0;
}

double IrasytiStudentus(const vector<Studentas>& v, const string& failoVardas) {
    Laikmatis t;

    ofstream failas (failoVardas);    
    failas  << left
            << setw(15) << "Vardas"
            << setw(20) << "Pavarde"
            << setw(20) << "Galutinis (vid.)"
            << setw(20) << "Galutinis (med.)" << '\n'
            << "-----------------------------------------------------------------------" << '\n';

    failas << fixed << setprecision(2);
    for (const auto& studentas : v) {
        failas  << left 
                << setw(15) << studentas.vardas 
                << setw(20) << studentas.pavarde 
                << setw(20) << studentas.galutinisVid
                << setw(20) << studentas.galutinisMed << '\n';
    }
    failas.close();
    return t.praejo();
}

double SkaitytiIsFailo(const string& failoVardas, vector<Studentas>& studentai) {
   
    ifstream failas (failoVardas);

    if (!failas) {
        cout << "\033[31mNepavyko atidaryti failo.\033[0m" << endl;
        return -1;
    }

    neteisingi.clear();
    Laikmatis t;


    string eilute;
    getline(failas, eilute);

    while (getline(failas, eilute)) {
        stringstream ss(eilute);
        Studentas studentas;
        ss >> studentas.vardas;
        ss >> studentas.pavarde;

        string strPazymys;
        bool neteisingasPazymys = false;

        while (ss >> strPazymys) {
            try
            {
                double pazymys = stod(strPazymys);

                if ( pazymys >= 0 && pazymys <= 10) {
                    studentas.namuDarbai.push_back(pazymys);
                } else {
                    neteisingasPazymys = true; 
                    break;
                }
            }
            catch(const invalid_argument& e){
                neteisingasPazymys = true;
                break;
            }
        }
        if (neteisingasPazymys|| studentas.namuDarbai.empty()) {
            NeteisingiDuomenys blogasStudentas;
            blogasStudentas.vardas = studentas.vardas;
            blogasStudentas.pavarde = studentas.pavarde;
            neteisingi.push_back(blogasStudentas);
            continue;
        }
        studentas.egzaminas = studentas.namuDarbai.back();
        studentas.namuDarbai.pop_back();

        studentas.galutinisVid = Vidurkis(studentas);
        studentas.galutinisMed = Mediana(studentas);
        studentai.push_back(move(studentas));

    }
    
    failas.close();
    return t.praejo();
}

double DalytiStudentus(vector<Studentas>& studentai, vector<Studentas>& vargseliai, vector<Studentas>& kietuoliai) {
    Laikmatis t;
 
    for (auto& s : studentai) {
        if (s.galutinisVid < 5.0) {
            vargseliai.push_back(move(s));
        } else {
            kietuoliai.push_back(move(s));
        }
    }
    studentai.clear();
    studentai.shrink_to_fit();
 
    return t.praejo();
}

double RusiuotiStudentus(vector<Studentas>& v, int pagal) {
    Laikmatis t;
 
    switch (pagal) {
        case 1:
            sort(v.begin(), v.end(), [](const Studentas& a, const Studentas& b) { return a.vardas < b.vardas; });
            break;
        case 2:
            sort(v.begin(), v.end(), [](const Studentas& a, const Studentas& b) { return a.pavarde < b.pavarde; });
            break;
        case 3:
            sort(v.begin(), v.end(), [](const Studentas& a, const Studentas& b) { return a.galutinisVid < b.galutinisVid; });
            break;
    }
 
    return t.praejo();
}

void PaleistiTestus(int rusiavimoPasirinkimas) {
    const int dydziai[] = {1000, 10000, 100000, 1000000, 10000000};
 
    const int kartai = 3;
    cout << fixed << setprecision(6);
 
    for (int n : dydziai) {
        string failas = "studentai" + to_string(n) + ".txt";
        
        vector<double> nuskLaikai;
        vector<double> dalLaikai;
        vector<double> rusLaikai;
        vector<double> vargLaikai;
        vector<double> kietLaikai;
        vector<double> bendriLaikai;

        for (int k = 0; k < kartai; k++) {
            vector<Studentas> studentai;
            vector<Studentas> vargseliai;
            vector<Studentas> kietuoliai;

            double tNusk = SkaitytiIsFailo(failas, studentai);
            if (tNusk < 0) { break; }
            double tDal = DalytiStudentus(studentai, vargseliai, kietuoliai);
            double tRus = RusiuotiStudentus(vargseliai, rusiavimoPasirinkimas)
                  + RusiuotiStudentus(kietuoliai, rusiavimoPasirinkimas);
            double tVarg = IrasytiStudentus(vargseliai, "vargseliai" + to_string(n) + ".txt");
            double tKiet = IrasytiStudentus(kietuoliai, "kietuoliai" + to_string(n) + ".txt");
        
            double tBendras = tNusk + tDal + tRus + tVarg + tKiet;

            nuskLaikai.push_back(tNusk);
            dalLaikai.push_back(tDal);
            rusLaikai.push_back(tRus);
            vargLaikai.push_back(tVarg);
            kietLaikai.push_back(tKiet);
            bendriLaikai.push_back(tBendras);

            cout << "Failas: " << n << " studentu"
                 << " | Testas " << k + 1
                 << " | Laikas: " << tBendras << " s\n";
        }
        
         if (bendriLaikai.empty()) {
            cout << "Failas " << failas
                 << " nerastas.\n\n";
            continue;
        }

        auto VidurkisLaiku = [](const vector<double>& laikai) {
            double suma = 0;

            for (double laikas : laikai) {
                suma += laikas;
            }

            return suma / laikai.size();
        };
        cout << "\n========== "
             << n << " STUDENTU ==========\n";

        cout << "Nuskaitymo laikai:\n";
        for (double laikas : nuskLaikai)
            cout << laikas << " s\n";

        cout << "Vidurkis: "
             << VidurkisLaiku(nuskLaikai)
             << " s\n\n";


        cout << "Dalijimo laikai:\n";
        for (double laikas : dalLaikai)
            cout << laikas << " s\n";

        cout << "Vidurkis: "
             << VidurkisLaiku(dalLaikai)
             << " s\n\n";


        cout << "Rusiuavimo laikai:\n";
        for (double laikas : rusLaikai)
            cout << laikas << " s\n";

        cout << "Vidurkis: "
             << VidurkisLaiku(rusLaikai)
             << " s\n\n";

        cout << "Vargsheliu irasymo laikai:\n";
        for (double laikas : vargLaikai)
            cout << laikas << " s\n";

        cout << "Vidurkis: "
             << VidurkisLaiku(vargLaikai)
             << " s\n\n";


        cout << "Kietuoliu irasymo laikai:\n";
        for (double laikas : kietLaikai)
            cout << laikas << " s\n";

        cout << "Vidurkis: "
             << VidurkisLaiku(kietLaikai)
             << " s\n\n";


        cout << "BENDRI TESTO LAIKAI:\n";
        for (double laikas : bendriLaikai)
            cout << laikas << " s\n";

        cout << "BENDRAS VIDURKIS: "
             << VidurkisLaiku(bendriLaikai)
             << " s\n\n";
    }
}
 
