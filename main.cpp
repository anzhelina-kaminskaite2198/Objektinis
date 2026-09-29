#include "Strukturos.h"
#include "StudentuFunkcijos.h"

#include <iostream>
using namespace std;


int main() {

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
                if (studentai.size() > 40){
                    int choice;
                    int i = 0;
                    while (i == 0){
                    
                        cout << "Sarase dabar yra " << studentai.size() << " studentu. Ar norite: \n"
                            << "1  Parodyti visus studentus\n"
                            << "2  Parodyti dali studentu" << endl;
                        
                        cin >> choice;
                        
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(100000000, '\n');
                            cout << "\n\n\033[31mKlaida: netinkamas pasirinkimas.\033[0m" << endl;
                            continue;
                        } 
                    
                        switch (choice) {

                            case 1: {
                                RodytiVisusStudentus();
                                i = 1;
                                continue;
                            }
                            case 2: {
                                RodytiDaliStudentu();
                                i = 1;
                                continue;
                            }
                            default:
                                cout << "\n\n\033[31mKlaida: netinkamas pasirinkimas.\033[0m" << endl;
                                continue;
                        }
                    }
                    
                } else {
                     RodytiVisusStudentus();
                }

                if (neteisingi.size() > 0) {
                    cout << "\n\nDel duomenu ivedimo klaidos i sarasa nebuvo ivesti sie studentai:\n";
                    for (NeteisingiDuomenys studentas: neteisingi){
                        cout << studentas.vardas << " " << studentas.pavarde << endl;
                    }
                }
                
                continue;
            }
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