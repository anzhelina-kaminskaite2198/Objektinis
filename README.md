# Studentų pažymių skaičiavimo programa

Objektinio programavimo kurso darbas. Programa leidžia surinkti studentų namų darbų ir egzamino
pažymius (įvedant ranka, sugeneruojant atsitiktinai arba nuskaitant iš failo) ir apskaičiuoja
galutinį balą dviem būdais – pagal namų darbų **vidurkį** ir pagal jų **medianą**.
Nuo v0.2 programa taip pat skirsto studentus į dvi grupes, rūšiuoja juos, rašo į failus ir
matuoja, kiek laiko užtrunka kiekvienas veiksmas su dideliais duomenų failais.


Galutinio balo formulės:

```
galutinis (vid.) = 0.4 * namų darbų vidurkis + 0.6 * egzaminas
galutinis (med.) = 0.4 * namų darbų mediana + 0.6 * egzaminas
```

Galutinis balas suapvalinamas iki dviejų skaitmenų po kablelio.

---

## Turinys

- [Reikalavimai ir paleidimas](#reikalavimai-ir-paleidimas)
- [Projekto failai](#projekto-failai)
- [Naudojimas](#naudojimas)
- [Duomenų failo formatas](#duomenų-failo-formatas)
- [Versijos (releases)](#versijos-releases)
  - [v.pradinė](#vpradinė)
  - [v0.1](#v01)
  - [v0.2](#v02)
  
---

## Reikalavimai ir paleidimas

Reikia C++ kompiliatoriaus, palaikančio C++11 ar naujesnį standartą (`g++`, `clang++`, MSVC).
Nuo v0.2 programa sudaryta iš kelių `.cpp` failų, todėl kompiliuojant reikia nurodyti **visus tris**:

```bash
git clone https://github.com/anzhelina-kaminskaite2198/Objektinis.git
cd Objektinis
git checkout v0.2
 
g++ -std=c++17 -O2 main.cpp StudentuFunkcijos.cpp TestiniaiFailai.cpp -o studentai
./studentai
```

Windows (MinGW):

```powershell
g++ -std=c++17 -O2 main.cpp StudentuFunkcijos.cpp TestiniaiFailai.cpp -o studentai.exe
.\studentai.exe
```

> **Pastaba apie kompiliavimą.** Jeigu kompiliuojamas tik vienas failas (pvz.
> `g++ TestiniaiFailai.cpp`), rodo klaidą `undefined reference to WinMain` – taip yra todėl, kad
> tame faile nėra `main()`. Jeigu pamirštamas `TestiniaiFailai.cpp`, rodo klaidą
> `undefined reference to SukurtiVisusTestavimoFailus()`.

> **Pastaba.** Programa klaidoms paryškinti naudoja ANSI spalvų kodus (`\033[31m`). Windows
> terminale `cmd.exe` jie gali būti rodomi kaip nesuprantami simboliai – rekomenduojama naudoti
> Windows Terminal, PowerShell 7 arba Git Bash.

> **Pastaba apie laiką.** Matuojant laiką rekomenduojama kompiliuoti su `-O2`, nes be optimizacijų
> rezultatai su dideliais failais būna gerokai lėtesni.


---

## Projekto failai
 
| Failas | Kas jame yra |
|---|---|
| `Strukturos.h` | Struktūros `Studentas` (vardas, pavardė, namų darbai, egzaminas, galutinis pagal vidurkį ir pagal medianą) ir `NeteisingiDuomenys` |
| `StudentuFunkcijos.h` | Funkcijų deklaracijos ir laiko matavimo struktūra `Laikmatis` |
| `StudentuFunkcijos.cpp` | Pagrindinės funkcijos: įvedimas, skaičiavimas, skaitymas iš failo, dalijimas, rūšiavimas, įrašymas, testų paleidimas |
| `TestiniaiFailai.cpp` | Atsitiktinių testinių failų kūrimas |
| `main.cpp` | Meniu ir programos eiga |
 
---

## Naudojimas

Paleidus programą rodomas meniu:

```
              MENIU
-----------------------------------
1  Ivesti nauja studenta
2  Nuskaityti duomenis is failo
3  Padalinti, surusiuoti ir irasyti studentus i failus
4  Sukurti testavimo failus (5 failai)
5  Paleisti testavimus (5 failai)
6  Iseiti
```

1. **Įvesti naują studentą** – prašoma vardo ir pavardės, po to galima pasirinkti, ar namų darbų
   pažymius įvesti ranka (įvedimas baigiamas paspaudus ENTER tuščioje eilutėje), ar juos
   sugeneruoti atsitiktinai(tuomet reikia nurodyti, kiek pažymių sugeneruoti). Tas pats pasirinkimas galioja ir egzamino pažymiui.Jeigu egzamino pažymys įvedamas ranka ir paspaudžiamas
   tik ENTER, egzaminas laikomas lygiu 0.
2. **Nuskaityti duomenis iš failo** – prašoma failo pavadinimo (pvz. `kursiokai.txt`).
   Paskutinis eilutės skaičius laikomas egzamino pažymiu, visi prieš jį – namų darbais.
   Po nuskaitymo parodomas nuskaitymo laikas, o jeigu buvo blogų įrašų – ir jų sąrašas.
3. **Padalinti, surūšiuoti ir įrašyti studentus į failus** – pirmiausia reikia pasirinkti,
   pagal ką rūšiuoti (pagal vardą, pagal pavardę arba pagal galutinį balą). Tada studentai
   padalinami į dvi grupes, kiekviena grupė surūšiuojama ir įrašoma į atskirą failą.
   Programa parodo kiekvieno žingsnio trukmę.
4. **Sukurti testavimo failus** – sukuria 5 atsitiktinių duomenų failus (žr. [žemiau](#testiniai-failai)).
5. **Paleisti testavimus** – pasirinkus rūšiavimo būdą, kiekvienam iš 5 failų atliekamas
   skaitymas, dalijimas, rūšiavimas ir įrašymas, o laikai išvedami į ekraną.
6. **Išeiti**.

### Studentų skirstymas į grupes
 
Studentai skirstomi pagal galutinį balą, apskaičiuotą pagal **vidurkį**:
 
- galutinis < 5.0 – **vargšeliai** (įrašomi į `vargseliai.txt`)
- galutinis ≥ 5.0 – **kietuoliai** (įrašomi į `kietuoliai.txt`)
Dalijant studentai ne kopijuojami, o perkeliami (`std::move`) iš pradinio sąrašo į vieną iš
dviejų naujų sąrašų. Todėl **po 3 meniu punkto pradinis studentų sąrašas tampa tuščias** – jei
reikia pakartoti veiksmą, duomenis reikia nuskaityti iš naujo.
 
Jeigu 3 punktas pasirenkamas kai sąrašas tuščias, parodomas pranešimas, kad pirmiausia reikia
įvesti arba nuskaityti studentus.
 
Rezultatų failo pavyzdys (`vargseliai.txt` / `kietuoliai.txt`):

```
Vardas         Pavarde             Galutinis (vid.)    Galutinis (med.)
-----------------------------------------------------------------------
Vardas1        Pavarde1            4.60                4.20
Vardas2        Pavarde2            3.80                4.00
```

### Laiko matavimas
 
Laikas matuojamas su `std::chrono` (struktūra `Laikmatis`). Po 3 punkto išvedami keturi laikai:
 
```
Dalijimo i dvi grupes laikas: X.XXXXXX s
Rusiavimo laikas: X.XXXXXX s
Vargseliu irasymo i faila laikas: X.XXXXXX s
Kietuoliu irasymo i faila laikas: X.XXXXXX s
```
 
Rūšiavimo laikas yra abiejų grupių rūšiavimo laikų suma.
 
### Testiniai failai
 
4 meniu punktas sukuria šiuos failus:
 
| Failas | Studentų skaičius | Namų darbų (ND) stulpelių |
|---|---|---|
| `studentai1000.txt` | 1 000 | 3 |
| `studentai10000.txt` | 10 000 | 4 |
| `studentai100000.txt` | 100 000 | 5 |
| `studentai1000000.txt` | 1 000 000 | 6 |
| `studentai10000000.txt` | 10 000 000 | 7 |
 
Vardai ir pavardės sugeneruojami pagal šabloną `Vardas1`, `Pavarde1`, `Vardas2`, ... ,
o pažymiai – atsitiktiniai sveikieji skaičiai nuo 0 iki 10. Programa išveda, kiek laiko užtruko
sukurti kiekvieną failą.
 
> Didžiausias failas (10 mln. įrašų) kuriamas ir apdorojamas ilgai ir užima daug vietos diske.
 
### Testavimas (5 meniu punktas)
 
Kiekvienam iš 5 failų testas kartojamas **3 kartus**. Kiekvieno karto metu:
 
1. nuskaitomas failas `studentaiN.txt`,
2. studentai padalinami į vargšelius ir kietuolius,
3. abi grupės surūšiuojamos pasirinktu būdu,
4. grupės įrašomos į `vargseliaiN.txt` ir `kietuoliaiN.txt`.
Išvedama kiekvieno karto bendra trukmė, o po 3 kartų – kiekvieno etapo laikai ir jų vidurkiai:
nuskaitymo, dalijimo, rūšiavimo, vargšelių įrašymo, kietuolių įrašymo ir bendras.
 
```
Failas: 1000 studentu | Testas 1 | Laikas: X.XXXXXX s
 
========== 1000 STUDENTU ==========
Nuskaitymo laikai:
X.XXXXXX s
...
Vidurkis: X.XXXXXX s
...
BENDRAS VIDURKIS: X.XXXXXX s
```
 
Jeigu reikiamo `studentaiN.txt` failo nėra, programa tai praneša ir pereina prie kito dydžio –
todėl pirmiausia reikia paleisti 4 meniu punktą.

### Įvesties tikrinimas

- Netinkamas meniu pasirinkimas (raidė vietoj skaičiaus, neegzistuojantis punktas) – srautas
  išvalomas (`cin.clear()`, `cin.ignore()`) ir meniu rodomas iš naujo, programa nenulūžta.
  Ta pati tikrinimo funkcija (`IvedimoKlaidos()`) naudojama visuose pasirinkimuose.
- Pažymys turi būti skaičius intervale **[0; 10]**; kitaip rodoma klaida ir prašoma įvesti iš naujo.
- Tekstas vietoj skaičiaus gaudomas per `stod()` metamą `std::invalid_argument` išimtį.
- Generuojamų namų darbų skaičius negali būti neigiamas.
- Neegzistuojantis failas – rodomas pranešimas, grįžtama į meniu.
- Failo eilutės su blogais pažymiais į pagrindinį sąrašą nepatenka, o yra surenkamos į atskirą
  `neteisingi` vektorių ir parodomos vartotojui.

---

## Duomenų failo formatas

Pirma failo eilutė – antraštė (ji praleidžiama). Toliau kiekviena eilutė aprašo vieną studentą:

```
Vardas        Pavarde        ND1   ND2   ND3   ND4   ND5   Egz.
Vardas1        Pavarde1       8     9     7     3     3     10
Vardas2        Pavarde2       7     6    10     5     8      9
```

Namų darbų pažymių skaičius iš anksto nėra žinomas – skaitomi visi eilutėje esantys skaičiai,
o **paskutinis** iš jų priskiriamas egzaminui. Stulpelių skaičius skirtingose eilutėse gali
skirtis, skiriamieji simboliai – bet koks tarpų kiekis.

Programos sukurti testiniai failai (`studentaiN.txt`) turi tokį patį formatą, todėl juos taip pat
galima nuskaityti per 2 meniu punktą.

---

## Versijos (releases)

Kiekviena versija turi atskirą žymą (tag) ir atskirą release'ą GitHub'e.

| Versija | Šaka | Trumpai |
|---|---|---|
| [`v.pradinė`](https://github.com/anzhelina-kaminskaite2198/Objektinis/releases) | `v.pradine` | Duomenų įvedimas ranka ir generavimas, vidurkis ir mediana, rezultatų lentelė |
| [`v0.1`](https://github.com/anzhelina-kaminskaite2198/Objektinis/releases) | `v0.1` | Skaitymas iš failo, blogų įrašų atmetimas, dalinė didelių sąrašų išvestis |
| [`v0.2`](https://github.com/anzhelina-kaminskaite2198/Objektinis/releases) | `v0.2` | Studentų dalijimas į dvi grupes, rūšiavimo pasirinkimas, rašymas į failus, testiniai failai ir laiko matavimas |

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

### v0.2
 
Šioje versijoje programa pritaikyta darbui su dideliais duomenų kiekiais ir jų apdorojimo
spartos matavimui.
 
**Kas nauja, palyginti su `v0.1`**
 
- **Kodas išskaidytas į kelis failus**: struktūros perkeltos į `Strukturos.h`, funkcijos į
  `StudentuFunkcijos.h/.cpp`, testinių failų kūrimas – į `TestiniaiFailai.cpp`, o `main.cpp`
  liko tik meniu. Dabar programą reikia kompiliuoti iš visų `.cpp` failų.
- **Studentų dalijimas į dvi grupes** (`DalytiStudentus()`): studentai, kurių galutinis balas
  (pagal vidurkį) mažesnis nei 5, patenka į „vargšelius", likusieji – į „kietuolius".
  Studentai perkeliami (`std::move`), o ne kopijuojami, o pradinis sąrašas po dalijimo
  išvalomas.
- **Rūšiavimo pasirinkimas** (`PasirinktiRusiavimoParametra()`, `RusiuotiStudentus()`):
  galima rūšiuoti pagal vardą, pavardę arba galutinį balą (pagal vidurkį). Naudojamas
  `std::sort` su lambda funkcijomis.
- **Rezultatų rašymas į failus** (`IrasytiStudentus()`): vargšeliai įrašomi į `vargseliai.txt`,
  kietuoliai – į `kietuoliai.txt`, abu su sulygiuotomis stulpelių antraštėmis.
- **Testinių failų kūrimas** (`SukurtiTestavimoFailus()`, `SukurtiVisusTestavimoFailus()`):
  sugeneruojami failai su 1 tūkst., 10 tūkst., 100 tūkst., 1 mln. ir 10 mln. įrašų.
- **Spartos testavimas** (`PaleistiTestus()`): kiekvienas failas apdorojamas 3 kartus, o
  nuskaitymo, dalijimo, rūšiavimo ir įrašymo laikai bei jų vidurkiai išvedami į ekraną.
- **Laiko matavimas** su `std::chrono` – struktūra `Laikmatis` naudojama visose funkcijose,
  kurios grąžina savo vykdymo trukmę sekundėmis.
- **Galutiniai balai skaičiuojami vieną kartą**: struktūroje `Studentas` pridėti laukai
  `galutinisVid` ir `galutinisMed`, kurie užpildomi nuskaitant arba įvedant studentą, tad
  rūšiuojant ir rašant į failus nebereikia skaičiuoti iš naujo.
- **Atsitiktiniai skaičiai** generuojami su `mt19937` ir `uniform_real_distribution`
  vietoje `rand()`.
- **Viena klaidų tikrinimo funkcija** `IvedimoKlaidos()` naudojama visuose meniu pasirinkimuose.
**Kas pasikeitė**
 
- Pašalintas meniu punktas „Rodyti studentus" ir dalinė išvestis (`RodytiDaliStudentu()`):
  rezultatai dabar rašomi į failus, o ne spausdinami į ekraną. Dėl šios priežasties nebereikalingas
  ir rūšiavimas pagal vardą prieš išvedimą – rūšiavimo būdą pasirenka pats vartotojas.

---
