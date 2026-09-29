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
};

struct NeteisingiDuomenys {
    string vardas;
    string pavarde;
};

#endif