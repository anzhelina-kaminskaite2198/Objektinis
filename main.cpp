#include "Strukturos.h"
#include "StudentuFunkcijos.h"

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;


int main() {

    ofstream varg ("vargseliai.txt");
    ofstream kiet ("kietuoliai.txt");

    varg << left
            << setw(15) << "Vardas" 
            << setw(20) << "Pavarde"
            << setw(20) << "Galutinis (vid.)"
            << setw(20) << "Galutinis (med.)" << endl
            << "-----------------------------------------------------------------------" << endl;

        
        kiet << left
            << setw(15) << "Vardas" 
            << setw(20) << "Pavarde"
            << setw(20) << "Galutinis (vid.)"
            << setw(20) << "Galutinis (med.)" << endl
            << "-----------------------------------------------------------------------" << endl;

    varg.close();
    kiet.close();

    int pasirinkimas;
    
    while (true) {
        cout << "\n              MENIU\n"
        << "-----------------------------------\n"
        << "1  Ivesti nauja studenta\n"
        << "2  Nuskaityti duomenis is failo\n"
        << "3  Rodyti studentus\n"
        << "4  Iseiti\n\n"
        << "Pasirinkite veiksma:";
    
        cin >> pasirinkimas;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(100000000, '\n');
            cout << "\n\n\033[31mKlaida: netinkamas pasirinkimas.\033[0m" << endl;
            continue;
        }
        
        switch (pasirinkimas) {
        
            case 1: {
                IvestiStudenta();
                continue;
            }
            case 2: {
                SkaitytiIsFailo();
                continue;
            }
            case 3: {
                
                IrasytiStudentus();
                }
                    
                if (neteisingi.size() > 0) {
                    cout << "\n\nDel duomenu ivedimo klaidos i sarasa nebuvo ivesti sie studentai:\n";
                    for (NeteisingiDuomenys studentas: neteisingi){
                        cout << studentas.vardas << " " << studentas.pavarde << endl;
                    }
                }
                
                continue;
            
            case 4:{
                return 0;;
            }
            default:
                cout << "\n\n\033[31mKlaida: netinkamas pasirinkimas.\033[0m" << endl;
                continue;
        }

    }
        return 0;
}