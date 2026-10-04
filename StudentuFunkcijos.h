#ifndef STUDENTUFUNKCIJOS_H
#define STUDENTUFUNKCIJOS_H

#include "Strukturos.h"
#include <vector>
#include <string>
#include <chrono>

using namespace std;

extern vector<NeteisingiDuomenys> neteisingi;

struct Laikmatis {
    chrono::high_resolution_clock::time_point pradzia = chrono::high_resolution_clock::now();
    double PraejesLaikas() const {
        return chrono::duration<double>(chrono::high_resolution_clock::now() - pradzia).count();
    }
};


bool IvedimoKlaidos (int, int);

int PasirinktiRusiavimoParametra();

double Vidurkis(const Studentas& studentas);

double Mediana(const Studentas& studentas);

int IvestiStudenta(vector<Studentas>& studentai);

double IrasytiStudentus(const vector<Studentas>& v, const string& failoVardas);

double SkaitytiIsFailo(const string& failoVardas, vector<Studentas>& studentai);

double DalytiStudentus(vector<Studentas>& studentai, vector<Studentas>& vargseliai, vector<Studentas>& kietuoliai);

double RusiuotiStudentus(vector<Studentas>& v, int pagal);

void PaleistiTestus(int rusiavimoPasirinkimas);

double SukurtiTestavimoFailus(int studentuSk, int ndSk);
void SukurtiVisusTestavimoFailus();


#endif