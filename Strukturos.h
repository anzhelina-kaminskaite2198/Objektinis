#ifndef STRUKTUROS_H
#define STRUKTUROS_H

#include <string>
#include <vector>
#include <chrono>
using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<double> namuDarbai;
    double egzaminas;
    double galutinisVid;
    double galutinisMed;
};

struct NeteisingiDuomenys {
    string vardas;
    string pavarde;
};

struct Laikmatis {
    chrono::high_resolution_clock::time_point pradzia = chrono::high_resolution_clock::now();
    double PraejesLaikas() const {
        return chrono::duration<double>(chrono::high_resolution_clock::now() - pradzia).count();
    }
};

#endif