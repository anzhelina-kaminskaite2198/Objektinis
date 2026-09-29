#ifndef STUDENTUFUNKCIJOS_H
#define STUDENTUFUNKCIJOS_H

using namespace std;

extern vector<Studentas> studentai;
extern vector<NeteisingiDuomenys> neteisingi;

int IvedimoKlaidos (int, int);

double Vidurkis(Studentas studentas);

double Mediana(Studentas studentas);

int IvestiStudenta();

int RodytiDaliStudentu();

int RodytiVisusStudentus();

int SkaitytiIsFailo();

#endif