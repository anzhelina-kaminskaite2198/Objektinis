#ifndef STUDENTUFUNKCIJOS_H
#define STUDENTUFUNKCIJOS_H

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

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<double>dist(0.0, 10.0);

vector<Studentas> studentai;
vector<NeteisingiDuomenys> neteisingi;

int IvedimoKlaidos (int kintamasis, int pasirinkimuSk) {
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
                }else {
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
    
    studentai.push_back(studentas);

    return 0;
}

int RodytiDaliStudentu() {

    sort(studentai.begin(), studentai.end(), [](Studentas a, Studentas b){
         return a.vardas < b.vardas;});
         
    cout << left
         << setw(15) << "Vardas" 
         << setw(20) << "Pavarde"
         << setw(20) << "Galutinis (vid.)"
         << setw(20) << "Galutinis (med.)" << endl
         << "-----------------------------------------------------------------------" << endl;

    for (int i = 0; i < 20; i++){
        Studentas studentas = studentai[i];
        cout << left 
            << setw(15) << studentas.vardas 
            << setw(20) << studentas.pavarde 
            << setw(20) << fixed << setprecision(2) << Vidurkis(studentas)
            << setw(20) << fixed << setprecision(2) << Mediana(studentas)  << endl;
    }

    cout << left 
            << setw(15) << "..." 
            << setw(20) << "..." 
            << setw(20) << "..."
            << setw(20) << "..." << endl ;
    
    for (int i = studentai.size()-20; i < studentai.size(); i++){
        Studentas studentas = studentai[i];
        cout << left 
            << setw(15) << studentas.vardas 
            << setw(20) << studentas.pavarde 
            << setw(20) << fixed << setprecision(2) << Vidurkis(studentas)
            << setw(20) << fixed << setprecision(2) << Mediana(studentas)  << endl;
    }
    return 0;
}

int RodytiVisusStudentus() {

    sort(studentai.begin(), studentai.end(), [](Studentas a, Studentas b){
         return a.vardas < b.vardas;});
    
    cout << left
        << setw(15) << "Vardas" 
        << setw(20) << "Pavarde"
        << setw(20) << "Galutinis (vid.)"
        << setw(20) << "Galutinis (med.)" << endl
        << "-----------------------------------------------------------------------" << endl;

    for (Studentas studentas : studentai) {
        cout << left 
            << setw(15) << studentas.vardas 
            << setw(20) << studentas.pavarde 
            << setw(20) << fixed << setprecision(2) << Vidurkis(studentas)
            << setw(20) << fixed << setprecision(2) << Mediana(studentas)  << endl;
    }
    return 0;
}

int SkaitytiIsFailo() {
    string file;
    cout << "Is kokio failo noretumet nuskaityti studentu duomenis?\n"
         << "pvz: kursiokai.txt" << endl;
    cin >> file;
    ifstream failas (file);

    if (!failas) {
        cout << "\033[31mNepavyko atidaryti failo.\033[0m" << endl;
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
            }
        }
        if (neteisingasPazymys) {
            NeteisingiDuomenys blogasStudentas;
            blogasStudentas.vardas = studentas.vardas;
            blogasStudentas.pavarde = studentas.pavarde;
            neteisingi.push_back(blogasStudentas);
            continue;
        }
        studentas.egzaminas = studentas.namuDarbai.back();
        studentas.namuDarbai.pop_back();

        studentai.push_back(studentas);
    }
    
    failas.close();
    cout << "\033[32mFailas sekmingai nuskaitytas!\033[0m" << endl;
    return 0;
}

int SukurtiFaila(string pavadinimas){
    ofstream failas (pavadinimas);
    
}

#endif