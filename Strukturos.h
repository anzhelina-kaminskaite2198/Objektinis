#ifndef STRUKTUROS_H
#define STRUKTUROS_H

#include <string>
#include <vector>
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



#endif