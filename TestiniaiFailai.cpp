#include "StudentuFunkcijos.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <fstream>
#include <chrono>
#include <string>
using namespace std;

static random_device rd;
static mt19937 gen(rd());
static uniform_int_distribution<int>ivertinimas(0, 10);

double SukurtiTestavimoFailus(int studentuSk, int ndSk) {
    auto pradzia = chrono::high_resolution_clock::now();
    ofstream failas ("studentai" + to_string(studentuSk) + ".txt");
    failas  << left
            << setw(15) << "Vardas" 
            << setw(20) << "Pavarde" << setw(20);

    for (int nd=0; nd < ndSk; nd++){
        failas << "ND" + to_string(nd+1) << setw(20);
    }
    failas  << "Egz" << '\n';
    for (int i=0; i<studentuSk; i++){
        failas << left
            << setw(15) << "Vardas" + to_string(i+1)
            << setw(20) << "Pavarde" + to_string(i+1)<< setw(20);
        for (int j=0; j<ndSk; j++){
            int ndPazymys = ivertinimas(gen);
            failas << ndPazymys << setw(20);
        }
        int egzaminas = ivertinimas(gen);
        failas << egzaminas << endl;
    }
    failas.close();
    auto pabaiga = chrono::high_resolution_clock::now();
    return chrono::duration<double>(pabaiga - pradzia).count();
};

void SukurtiVisusTestavimoFailus() {
    const int dydziai[] = {1000, 10000, 100000, 1000000, 10000000};
    const int ndSkaicius[] = {3, 4, 5, 6, 7};
 
    cout << fixed << setprecision(6);
    for (int i = 0; i < 5; i++) {
        double FailuKurimoLaikas = SukurtiTestavimoFailus(dydziai[i], ndSkaicius[i]);
        cout << dydziai[i] << " irasu failo sukurimo laikas: " << FailuKurimoLaikas << '\n';
    }
    cout << '\n';
}
