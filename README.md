# Studentų pažymių skaičiavimo programa

Objektinio programavimo kurso darbas. Programa leidžia surinkti studentų namų darbų ir egzamino
pažymius (įvedant ranka, sugeneruojant atsitiktinai arba nuskaitant iš failo) ir apskaičiuoja
galutinį balą dviem būdais – pagal namų darbų **vidurkį** ir pagal jų **medianą**.

Galutinio balo formulės:

```
galutinis (vid.) = 0.4 * namų darbų vidurkis + 0.6 * egzaminas
galutinis (med.) = 0.4 * namų darbų mediana + 0.6 * egzaminas
```

---

## Turinys

- [Reikalavimai ir paleidimas](#reikalavimai-ir-paleidimas)
- [Naudojimas](#naudojimas)
- [Duomenų failo formatas](#duomenų-failo-formatas)
- [Versijos (releases)](#versijos-releases)
  - [v.pradinė](#vpradinė)
  - [v0.1](#v01)
  
---

## Reikalavimai ir paleidimas

Reikia C++ kompiliatoriaus, palaikančio C++11 ar naujesnį standartą (`g++`, `clang++`, MSVC).

```bash
git clone https://github.com/anzhelina-kaminskaite2198/Objektinis.git
cd Objektinis
git checkout v0.1

g++ -std=c++17 -O2 main.cpp -o studentai
./studentai
```

Windows (MinGW):

```powershell
g++ -std=c++17 -O2 main.cpp -o studentai.exe
.\studentai.exe
```

> **Pastaba.** Programa klaidoms paryškinti naudoja ANSI spalvų kodus (`\033[31m`). Windows
> terminale `cmd.exe` jie gali būti rodomi kaip nesuprantami simboliai – rekomenduojama naudoti
> Windows Terminal, PowerShell 7 arba Git Bash.

---

## Naudojimas

Paleidus programą rodomas meniu:

```
              MENIU
-----------------------------------
1  Ivesti nauja studenta
2  Nuskaityti duomenis is failo
3  Rodyti studentus
4  Iseiti
```

1. **Įvesti naują studentą** – prašoma vardo ir pavardės, po to galima pasirinkti, ar namų darbų
   pažymius įvesti ranka (įvedimas baigiamas paspaudus ENTER tuščioje eilutėje), ar juos
   sugeneruoti atsitiktinai. Tas pats pasirinkimas galioja ir egzamino pažymiui.
2. **Nuskaityti duomenis iš failo** – prašoma failo pavadinimo (pvz. `kursiokai.txt`).
   Paskutinis eilutės skaičius laikomas egzamino pažymiu, visi prieš jį – namų darbais.
3. **Rodyti studentus** – sąrašas surikiuojamas pagal vardą ir išvedamas lentele. Jeigu sąraše
   yra daugiau nei 40 studentų, siūloma išvesti arba visą sąrašą, arba tik jo dalį
   (pirmi 20 ir paskutiniai 20 įrašų). Pabaigoje parodomi studentai, kurių duomenys buvo
   atmesti dėl klaidų faile.
4. **Išeiti**.

Išvesties pavyzdys:

```
Vardas         Pavarde             Galutinis (vid.)    Galutinis (med.)
-----------------------------------------------------------------------
Anzhelina      Kaminskaite         8.40                8.40
Vardenis       Pavardenis          8.32                8.20

Del duomenu ivedimo klaidos i sarasa nebuvo ivesti sie studentai:
Vardas1  Pavarde1
Vardas2  Pavarde2
```

### Įvesties tikrinimas

- Netinkamas meniu pasirinkimas (raidė vietoj skaičiaus, neegzistuojantis punktas) – srautas
  išvalomas (`cin.clear()`, `cin.ignore()`) ir meniu rodomas iš naujo, programa nenulūžta.
- Pažymys turi būti skaičius intervale **[0; 10]**; kitaip rodoma klaida ir prašoma įvesti iš naujo.
- Tekstas vietoj skaičiaus gaudomas per `stod()` metamą `std::invalid_argument` išimtį.
- Neegzistuojantis failas – rodomas pranešimas, grįžtama į meniu.
- Failo eilutės su blogais pažymiais į pagrindinį sąrašą nepatenka, o yra surenkamos į atskirą
  `neteisingi` vektorių ir parodomos vartotojui.

---

## Duomenų failo formatas

Pirma failo eilutė – antraštė (ji praleidžiama). Toliau kiekviena eilutė aprašo vieną studentą:

```
Vardas        Pavarde        ND1   ND2   ND3   ND4   ND5   Egz.
Anzhelina     Kaminskaite      8     9     7     3     3     10
Vardenis      Pavardenis       7     6    10     5     8      9
```

Namų darbų pažymių skaičius iš anksto nėra žinomas – skaitomi visi eilutėje esantys skaičiai,
o **paskutinis** iš jų priskiriamas egzaminui. Stulpelių skaičius skirtingose eilutėse gali
skirtis, skiriamieji simboliai – bet koks tarpų kiekis.

Repozitorijoje esantis `kursiokai.txt` sąmoningai turi ir blogų įrašų (pažymys `17`, simbolis `s`),
kad būtų galima pademonstruoti klaidų apdorojimą.

---

## Versijos (releases)

Kiekviena versija turi atskirą žymą (tag) ir atskirą release'ą GitHub'e.

| Versija | Šaka | Trumpai |
|---|---|---|
| [`v.pradinė`](https://github.com/anzhelina-kaminskaite2198/Objektinis/releases) | `v.pradine` | Duomenų įvedimas ranka ir generavimas, vidurkis ir mediana, rezultatų lentelė |
| [`v0.1`](https://github.com/anzhelina-kaminskaite2198/Objektinis/releases) | `v0.1` | Skaitymas iš failo, blogų įrašų atmetimas, dalinė didelių sąrašų išvestis |

### v.pradinė

Pirmoji veikianti programos versija.

**Funkcionalumas**

- Struktūra `Studentas` (vardas, pavardė, `vector<double> namuDarbai`, egzaminas) ir globalus
  `vector<Studentas> studentai`.
- Namų darbų pažymių skaičius nėra žinomas iš anksto – jis nustatomas įvedimo metu, įvedimas
  baigiamas tuščia eilute.
- Galimybė atsitiktinai sugeneruoti tiek namų darbų, tiek egzamino pažymius (`rand()`).
- Galutinio balo skaičiavimas pagal vidurkį (`Vidurkis()`) ir pagal medianą (`Mediana()`),
  rezultatas suapvalinamas iki dviejų skaitmenų po kablelio.
- Rezultatų išvedimas sulygiuota lentele naudojant `<iomanip>` (`setw`, `left`, `fixed`,
  `setprecision`).
- Įvesties klaidų tikrinimas (ne skaičius, pažymys ne intervale [0; 10], netinkamas meniu punktas).
- Funkcijos suskirstytos pagal atsakomybes: `IvestiStudenta()`, `ParodytiStudentus()`,
  `Vidurkis()`, `Mediana()`.

**Apribojimai**

- Duomenis galima įvesti tik ranka arba sugeneruoti – failų skaitymo nėra.
- Visas sąrašas visada išvedamas iš karto, todėl su dideliu kiekiu studentų išvestis
  tampa neperskaitoma.

### v0.1

**Kas nauja, palyginti su `v.pradinė`**

- **Duomenų skaitymas iš failo** (`SkaitytiIsFailo()`): vartotojas pats nurodo failo pavadinimą,
  tad programa nėra pririšta prie vieno konkretaus failo. Eilutė skaidoma per `stringstream`,
  paskutinis skaičius traktuojamas kaip egzaminas.
- **Blogų įrašų atmetimas**: pridėta struktūra `NeteisingiDuomenys` ir vektorius `neteisingi`.
  Studentas, kurio eilutėje yra netinkamas pažymys, į skaičiavimus nepatenka, bet jo vardas ir
  pavardė parodomi vartotojui – duomenys nėra tyliai prarandami.
- **Dalinė išvestis** (`RodytiDaliStudentu()`): kai sąraše daugiau nei 40 studentų, siūloma
  išvesti tik pirmus 20 ir paskutinius 20 įrašų. Tai atsirado būtent po efektyvumo tyrimų su
  dideliais failais, kai pilnos lentelės spausdinimas į terminalą užtruko ilgiau nei patys
  skaičiavimai.
- **Rikiavimas pagal vardą** prieš išvedimą (`std::sort` su lambda funkcija).
- Pridėtas `.gitignore` (kompiliuoti failai, bandomieji `.cpp`, dideli sugeneruoti duomenų failai).
- Pridėtas testinis failas `kursiokai.txt` su specialiai įterptomis klaidomis.
- Ištaisytos įvedimo klaidos: srauto valymas po `cin.fail()`, nebelieka „prašokamų" `getline()`
  kvietimų po `cin >>`.

---
