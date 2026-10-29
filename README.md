# Studentų pažymių skaičiavimo programa

Objektinio programavimo kurso darbas. Programa leidžia surinkti studentų namų darbų ir egzamino
pažymius (įvedant ranka, sugeneruojant atsitiktinai arba nuskaitant iš failo) ir apskaičiuoja
galutinį balą dviem būdais – pagal namų darbų **vidurkį** ir pagal jų **medianą**.

- **v0.2** – studentų skirstymas į dvi grupes, rūšiavimas, rašymas į failus, laiko matavimas.
- **v0.3** – visos funkcijos veikia ir su `std::vector`, ir su `std::list`; konteinerių palyginimas.
- **v1.0** – trys studentų dalijimo strategijos (+ papildoma „Mano“), efektyvūs STL algoritmai, `CMakeLists.txt`.

Galutinio balo formulės:

```
galutinis (vid.) = 0.4 * namų darbų vidurkis + 0.6 * egzaminas
galutinis (med.) = 0.4 * namų darbų mediana + 0.6 * egzaminas
```

Galutinis balas suapvalinamas iki dviejų skaitmenų po kablelio.

---

## Turinys

- [Diegimas ir paleidimas](#diegimas-ir-paleidimas)
- [Projekto failai](#projekto-failai)
- [Naudojimo instrukcija](#naudojimo-instrukcija)
- [Duomenų failo formatas](#duomenų-failo-formatas)
- [Dalijimo strategijos (v1.0)](#dalijimo-strategijos-v10)
- [Konteinerių palyginimas: vector ir list](#konteinerių-palyginimas-vector-ir-list)
- [Versijos (releases)](#versijos-releases)

---

## Diegimas ir paleidimas

**Reikalavimai:** C++17 palaikantis kompiliatorius (`g++`, `clang++` arba MSVC) ir CMake ≥ 3.10.
C++17 reikalingas dėl `if constexpr` ir `is_same_v`, naudojamų šablonuose.

### Su CMake (rekomenduojama)

```
git clone https://github.com/anzhelina-kaminskaite2198/Objektinis.git
cd Objektinis

cmake -S . -B build
cmake --build build
```

Paleidimas:

| Aplinka | Komanda |
|---|---|
| Linux / macOS / MinGW | `./build/studentai` |
| Windows (Visual Studio generatorius) | `cmake --build build --config Release`, tada `build\Release\studentai.exe` |

Pagal nutylėjimą kompiliuojama **Release** režimu (su optimizacijomis), nes tik tokiu būdu laiko
matavimai turi prasmę. Jei Windows sistemoje CMake nerodo kompiliatoriaus (`nmake` klaida),
nurodykite generatorių: `cmake -S . -B build -G "MinGW Makefiles"`.

### Be CMake (tik g++)

```
g++ -std=c++17 -O2 main.cpp TestiniaiFailai.cpp -o studentai
./studentai
```

> **Pastaba apie spalvas.** Programa klaidoms paryškinti naudoja ANSI spalvų kodus (`\033[31m`).
> Windows `cmd.exe` jie gali būti rodomi kaip nesuprantami simboliai – rekomenduojama naudoti
> Windows Terminal, PowerShell 7 arba Git Bash.
>
> **Pastaba apie kompiliavimą.** Jei pamirštamas `TestiniaiFailai.cpp`, rodoma klaida
> `undefined reference to SukurtiVisusTestavimoFailus()`.

---

## Projekto failai

| Failas | Kas jame yra |
|---|---|
| `CMakeLists.txt` | Projekto surinkimo aprašas (C++17, Release pagal nutylėjimą) |
| `Strukturos.h` | Struktūros `Studentas`, `NeteisingiDuomenys` ir laiko matavimo struktūra `Laikmatis` |
| `StudentuFunkcijos.h` | Visos studentų funkcijos: įvedimas, skaičiavimas, skaitymas iš failo, dalijimo strategijos, rūšiavimas, įrašymas, testų paleidimas (daugelis – šablonai) |
| `TestiniaiFailai.cpp` | Atsitiktinių testinių failų kūrimas |
| `main.cpp` | Meniu ir programos eiga |

---

## Naudojimo instrukcija

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

**Rekomenduojama eiga tyrimui:** `4` (sukuria testinius failus vieną kartą) → `5` (paleidžia testus) → `6`.

1. **Įvesti naują studentą** – prašoma vardo ir pavardės, tada pasirenkama, ar namų darbų pažymius
   įvesti ranka (baigiama paspaudus ENTER tuščioje eilutėje), ar sugeneruoti atsitiktinai. Tas pats
   pasirinkimas galioja egzaminui; jei egzaminas įvedamas ranka ir paspaudžiamas tik ENTER, jis laikomas 0.
   Išvedamas ir studento objekto adresas atmintyje (`&studentai.back()`).
2. **Nuskaityti duomenis iš failo** – prašoma failo pavadinimo (pvz. `kursiokai.txt`). Paskutinis
   eilutės skaičius laikomas egzamino pažymiu, visi prieš jį – namų darbais. Parodomas nuskaitymo
   laikas ir, jei buvo blogų įrašų, jų sąrašas.
3. **Padalinti, surūšiuoti ir įrašyti** – pasirenkama, pagal ką rūšiuoti (vardą, pavardę ar galutinį
   balą); studentai padalinami į dvi grupes (naudojama greičiausia strategija – `Optimizuota`),
   kiekviena grupė surūšiuojama ir įrašoma į `vargseliai.txt` / `kietuoliai.txt`.
   **Po šio žingsnio pradinis sąrašas tampa tuščias** – norint kartoti, duomenis reikia nuskaityti iš naujo.
4. **Sukurti testavimo failus** – žr. [Testiniai failai](#testiniai-failai).
5. **Paleisti testavimus** – kiekvienai strategijai, kiekvienam konteineriui (`vector`, `list`) ir
   kiekvienam iš 5 failų atliekamas skaitymas, dalijimas, rūšiavimas ir įrašymas (3 kartai), išvedami laikų vidurkiai.
6. **Išeiti**.

### Testiniai failai

| Failas | Studentų skaičius | ND stulpelių |
|---|---|---|
| `studentai1000.txt` | 1 000 | 3 |
| `studentai10000.txt` | 10 000 | 4 |
| `studentai100000.txt` | 100 000 | 5 |
| `studentai1000000.txt` | 1 000 000 | 6 |
| `studentai10000000.txt` | 10 000 000 | 7 |

Vardai ir pavardės: `Vardas1`, `Pavarde1`, ...; pažymiai – atsitiktiniai sveikieji nuo 0 iki 10.
Failai sukuriami **vieną kartą** ir naudojami visiems testams, kad palyginimas būtų sąžiningas.
Didžiausias failas (10 mln. įrašų) užima daug vietos diske ir daug RAM apdorojant (ypač S1 strategija, kuri
laiko dvi studentų kopijas).

### Įvesties tikrinimas

- Netinkamas meniu pasirinkimas – srautas išvalomas ir meniu rodomas iš naujo (`IvedimoKlaidos()`).
- Pažymys turi būti skaičius intervale **[0; 10]**; tekstas vietoj skaičiaus gaudomas per `std::invalid_argument`.
- Generuojamų namų darbų skaičius negali būti neigiamas.
- Neegzistuojantis failas – parodomas pranešimas, grįžtama į meniu.
- Eilutės su blogais pažymiais į sąrašą nepatenka, o surenkamos į `neteisingi` ir parodomos vartotojui.

---

## Duomenų failo formatas

Pirma eilutė – antraštė (praleidžiama). Toliau kiekviena eilutė – vienas studentas:

```
Vardas        Pavarde        ND1   ND2   ND3   ND4   ND5   Egz.
Vardas1       Pavarde1       8     9     7     3     3     10
```

Namų darbų skaičius iš anksto nežinomas – skaitomi visi eilutės skaičiai, **paskutinis** priskiriamas
egzaminui. Stulpelių skaičius eilutėse gali skirtis, skirtukai – bet koks tarpų kiekis.

---

## Dalijimo strategijos (v1.0)

Studentai skirstomi pagal galutinį balą (pagal vidurkį): **< 5.0 – „vargšeliai“**, **≥ 5.0 – „kietuoliai“**.

| Strategija | Aprašymas | `vector` | `list` |
|---|---|---|---|
| **S1** | Bendras konteineris skaidomas į du **naujus** konteinerius, studentai **kopijuojami** (`partition_copy`). Studentas yra dviejuose konteineriuose (bendrame ir naujame) – didžiausias atminties naudojimas. | `partition_copy` | `partition_copy` |
| **S2** | Naudojamas tik vienas naujas konteineris („vargšeliai“); vargšeliai perkeliami į jį ir **ištrinami** iš bendro, kuriame lieka kietuoliai. | Rūšiavimas pagal balą ir `pop_back()` vargšelių | `erase` ciklu |
| **Mano** | Vienas praėjimas, kiekvienas studentas **perkeliamas** (ne kopijuojamas) į vieną iš dviejų naujų konteinerių. | `count_if` + `reserve` + `partition_copy` su `move_iterator` | `splice` į abu konteinerius |
| **Optimizuota (S3)** | Greičiausios strategijos (S1/S2) variantas su efektyviais STL algoritmais. | `copy_if` + `remove_if` (judinami elementai) | `splice` tik vargšelių, likęs konteineris perimamas per `move` |

**Naudoti algoritmai:** `std::partition_copy`, `std::copy_if`, `std::remove_if`, `std::count_if`, `std::sort`
(`vector`), `std::list::sort`, `std::list::splice`, `std::make_move_iterator`.

### Metodika

- Failai: `studentai1000.txt` ... `studentai10000000.txt`, sugeneruoti vieną kartą.
- Kompiliavimas: **Release** (`-O2`), C++17.
- Kiekvienam failui, konteineriui ir strategijai testas kartojamas **3 kartus**, pateikiamas **vidurkis** (sekundėmis).
- Matuojamas **dalijimo** laikas (nuskaitymas, rūšiavimas ir rašymas nuo strategijos nepriklauso).
- Rūšiavimo kriterijus: pagal galutinį balą.

### Dalijimo laikai pagal strategijas (s, 3 testų vidurkis)

Lyginamas tik **dalijimo į dvi grupes** laikas. Greičiausia strategija kiekvienoje eilutėje pažymėta **paryškintai**.

**`std::vector`**

| Studentų sk. | S1 | S2 | Mano | Optimizuota |
|---|---|---|---|---|
| 1 000 | 0.000167 | 0.000204 | 0.000045 | **0.000044** |
| 10 000 | 0.002262 | 0.001675 | 0.000562 | **0.000473** |
| 100 000 | 0.014464 | 0.020619 | 0.007101 | **0.005614** |
| 1 000 000 | 0.168173 | 0.247601 | 0.062488 | **0.043173** |
| 10 000 000 | 1.989825 | 2.971660 | 0.746052 | **0.511777** |

**`std::list`**

| Studentų sk. | S1 | S2 | Mano | Optimizuota |
|---|---|---|---|---|
| 1 000 | 0.000137 | **0.000041** | 0.000122 | 0.000209 |
| 10 000 | 0.001318 | **0.000481** | 0.001303 | 0.001450 |
| 100 000 | 0.012416 | **0.005032** | 0.012993 | 0.015464 |
| 1 000 000 | 0.139732 | **0.049388** | 0.140800 | 0.168690 |
| 10 000 000 | 1.789229 | **0.500971** | 2.040563 | 2.085997 |

### Bendras testo laikas pagal strategijas (s)

Bendras laikas = nuskaitymas + dalijimas + rūšiavimas + abiejų grupių įrašymas. Kadangi nuskaitymas ir įrašymas
nuo strategijos nepriklauso ir sudaro didžiąją dalį laiko, skirtumai čia gerokai mažesni nei dalijimo lentelėse.

**`std::vector`**

| Studentų sk. | S1 | S2 | Mano | Optimizuota |
|---|---|---|---|---|
| 1 000 | **0.011822** | 0.014239 | 0.013661 | 0.014501 |
| 10 000 | 0.054115 | **0.035557** | 0.037854 | 0.051473 |
| 100 000 | 0.405343 | 0.340702 | 0.338912 | **0.326282** |
| 1 000 000 | 4.230574 | 3.929955 | 3.555266 | **3.358187** |
| 10 000 000 | 41.879435 | 37.919924 | 35.638512 | **35.160701** |

**`std::list`**

| Studentų sk. | S1 | S2 | Mano | Optimizuota |
|---|---|---|---|---|
| 1 000 | 0.014958 | 0.013238 | 0.014065 | **0.011979** |
| 10 000 | 0.036970 | **0.036139** | 0.040744 | 0.041223 |
| 100 000 | **0.351997** | 0.363446 | 0.352645 | 0.367507 |
| 1 000 000 | **3.890260** | 3.906703 | 3.975971 | 4.009171 |
| 10 000 000 | 46.434895 | **44.811199** | 46.141458 | 46.556903 |

### Atminties naudojimas (S1 ir S2)

Atminties kiekis šiame tyrime **nebuvo matuojamas**, todėl skaičių nepateikiama. Teoriškai:

- **S1** kopijuoja kiekvieną studentą į naują konteinerį, o bendras konteineris lieka nepakeistas, todėl dalijimo metu
  kiekvienas studentas egzistuoja dviem kopijomis (vardas, pavardė, `vector<double>` su namų darbais) – maždaug dvigubas atminties poreikis.
- **S2**, **Mano** ir **Optimizuota** studentus perkelia (`std::move`) arba perjungia rodykles (`splice`), todėl papildomos
  atminties beveik nereikia.

### Strategijų išvados

- **`vector`:** nuo 1 000 iki 10 000 000 įrašų greičiausia dalijimo strategija – **Optimizuota** (`copy_if` su `move_iterator` +
  `remove_if`): 10 mln. įrašų ji užtrunka 0,51 s, **Mano** – 0,75 s, S1 – 1,99 s, S2 – 2,97 s. Optimizuota apie 3,9 karto greitesnė už S1 ir apie 5,8 karto už S2.
- **`vector`, S2:** lėčiausia nuo 100 000 įrašų. Mūsų S2 realizacija prieš dalijimą visą vektorių surūšiuoja, todėl dalijimo laikas apima ir rūšiavimą.
  Dėl to vėlesnio rūšiavimo laikas S2 atveju yra mažesnis (10 mln.: 1,85 s prieš ~2,3–2,7 s), nes elementai jau beveik surūšiuoti –
  tai ne konteinerio, o duomenų išdėstymo pasekmė.
- **`list`:** greičiausia dalijimo strategija – **S2** (`erase` ciklu su `push_back(move(...))`): 10 mln. įrašų 0,50 s, o S1 – 1,79 s, Mano – 2,04 s, Optimizuota – 2,09 s.
  Tai prieštarauja lūkesčiui, kad `splice` (tik rodyklių perjungimas) bus greičiausias. Šio rezultato priežasties čia neišsiaiškinome;
  tikėtina, kad įtakos turi mazgų išsidėstymas atmintyje ir talpyklos (cache) praleidimai, bet tai reikėtų patikrinti profiliuojant.
- **Bendras laikas:** `vector` atveju Optimizuota geriausia nuo 100 000 įrašų (10 mln.: 35,16 s prieš 41,88 s su S1, t. y. ~16 % greičiau).
  `list` atveju skirtumai tarp strategijų yra 1–4 % (10 mln.: 44,8–46,6 s), todėl jie panašūs į matavimo paklaidą.
- **Rekomendacija:** `vector` + **Optimizuota** yra greičiausias derinys (10 mln. įrašų – 35,16 s); jei būtinas `list`, verta naudoti **S2**.

---

## Konteinerių palyginimas: vector ir list

Tyrimo tikslas – išmatuoti, kaip keičiasi sparta, kai studentams saugoti vietoje `std::vector` naudojamas `std::list`.
Visos funkcijos – šablonai, naudojami tie patys failai ir tas pats rūšiavimo kriterijus (pagal galutinį balą).
Rūšiavimas: `vector` – `std::sort`, `list` – `std::list::sort`. Metodika aprašyta skyriuje
[Dalijimo strategijos](#dalijimo-strategijos-v10).

Lyginamos **visų etapų** trukmės (nuskaitymas, dalijimas, rūšiavimas, abiejų grupių įrašymas) su **Optimizuota** strategija,
nes ją programa naudoja realiai (3 meniu punktas).

### Rezultatai (s, 3 testų vidurkis)

**`std::vector`**

| Studentų sk. | Nuskaitymas | Dalijimas | Rūšiavimas | Vargšelių įrašymas | Kietuolių įrašymas | Bendras |
|---|---|---|---|---|---|---|
| 1 000 | 0.001881 | 0.000044 | 0.000130 | 0.010742 | 0.001704 | 0.014501 |
| 10 000 | 0.021001 | 0.000473 | 0.001228 | 0.019679 | 0.009091 | 0.051473 |
| 100 000 | 0.157542 | 0.005614 | 0.014289 | 0.076373 | 0.072466 | 0.326282 |
| 1 000 000 | 1.923079 | 0.043173 | 0.192033 | 0.590214 | 0.609687 | 3.358187 |
| 10 000 000 | 20.968560 | 0.511777 | 2.286842 | 5.678227 | 5.715295 | 35.160701 |

**`std::list`**

| Studentų sk. | Nuskaitymas | Dalijimas | Rūšiavimas | Vargšelių įrašymas | Kietuolių įrašymas | Bendras |
|---|---|---|---|---|---|---|
| 1 000 | 0.001987 | 0.000209 | 0.000068 | 0.008262 | 0.001452 | 0.011979 |
| 10 000 | 0.016906 | 0.001450 | 0.000871 | 0.012275 | 0.009721 | 0.041223 |
| 100 000 | 0.175251 | 0.015464 | 0.024357 | 0.077817 | 0.074619 | 0.367507 |
| 1 000 000 | 1.973327 | 0.168690 | 0.560189 | 0.662862 | 0.644103 | 4.009171 |
| 10 000 000 | 22.041852 | 2.085997 | 9.885684 | 6.236710 | 6.306659 | 46.556903 |

### Palyginimas (list laikas / vector laikas)

Reikšmė > 1 reiškia, kad `list` lėtesnis, < 1 – greitesnis.

| Studentų sk. | Nuskaitymas | Dalijimas | Rūšiavimas | Vargšelių įrašymas | Kietuolių įrašymas | Bendras |
|---|---|---|---|---|---|---|
| 1 000 | 1.06 | 4.75 | 0.52 | 0.77 | 0.85 | 0.83 |
| 10 000 | 0.81 | 3.07 | 0.71 | 0.62 | 1.07 | 0.80 |
| 100 000 | 1.11 | 2.75 | 1.70 | 1.02 | 1.03 | 1.13 |
| 1 000 000 | 1.03 | 3.91 | 2.92 | 1.12 | 1.06 | 1.19 |
| 10 000 000 | 1.05 | 4.08 | 4.32 | 1.10 | 1.10 | 1.32 |

### Palyginimas pagal strategijas (list laikas / vector laikas)

**Dalijimo laikas**

| Studentų sk. | S1 dalijimas | S2 dalijimas | Mano dalijimas | Optimizuota dalijimas |
|---|---|---|---|---|
| 1 000 | 0.82 | 0.20 | 2.71 | 4.75 |
| 10 000 | 0.58 | 0.29 | 2.32 | 3.07 |
| 100 000 | 0.86 | 0.24 | 1.83 | 2.75 |
| 1 000 000 | 0.83 | 0.20 | 2.25 | 3.91 |
| 10 000 000 | 0.90 | 0.17 | 2.74 | 4.08 |

**Bendras laikas**

| Studentų sk. | S1 bendras | S2 bendras | Mano bendras | Optimizuota bendras |
|---|---|---|---|---|
| 1 000 | 1.27 | 0.93 | 1.03 | 0.83 |
| 10 000 | 0.68 | 1.02 | 1.08 | 0.80 |
| 100 000 | 0.87 | 1.07 | 1.04 | 1.13 |
| 1 000 000 | 0.92 | 0.99 | 1.12 | 1.19 |
| 10 000 000 | 1.11 | 1.18 | 1.29 | 1.32 |

### Išvados

- **Nuskaitymas ir įrašymas į failą:** santykis artimas 1 (0,62–1,12), nes darbą daugiausia lemia failo skaitymas ir rašymas, o ne konteineris.
- **Rūšiavimas:** mažuose failuose (iki 10 000) `list::sort` panašus ar net greitesnis, bet nuo 100 000 įrašų `list` lėtėja: 100 000 – 1,7 karto,
  1 mln. – 2,9 karto, 10 mln. – 4,3 karto (9,89 s prieš 2,29 s). `list` mazgai išsibarstę atmintyje, todėl blogai išnaudojama talpykla (cache).
- **Dalijimas su Optimizuota strategija:** `list` lėtesnis 2,8–4,8 karto. Tačiau tai priklauso nuo strategijos: su S2 `list` yra **greitesnis**
  (`list`/`vector` = 0,17–0,29), nes `vector` S2 realizacija lėta (rūšiavimas prieš dalijimą), o `list` trynimas yra pigus.
- **Bendras laikas:** iki 10 000 įrašų skirtumai yra milisekundžių dalys ir tikėtinai paklaida (list formaliai greitesnis, 0,80–0,83). Nuo 100 000 įrašų
  `list` lėtesnis: 1,13 → 1,19 → 1,32 karto (10 mln.: 46,56 s prieš 35,16 s).
- **Pagal strategijas:** didžiausias bendras skirtumas tarp konteinerių – su Optimizuota (1,32) ir Mano (1,29), mažiausias – su S1 (1,11),
  nes S1 `vector` atveju lėčiausia (kopijavimas), tad `list` atsilieka mažiau.
- **Atmintis:** 10 mln. įrašų testas pavyko su abiem konteineriais ir visomis strategijomis.

---

## Versijos (releases)

| Versija | Šaka | Trumpai |
|---|---|---|
| `v.pradinė` | `v.pradine` | Įvedimas ranka ir generavimas, vidurkis ir mediana, rezultatų lentelė |
| `v0.1` | `v0.1` | Skaitymas iš failo, blogų įrašų atmetimas, dalinė didelių sąrašų išvestis |
| `v0.2` | `v0.2` | Dalijimas į dvi grupes, rūšiavimo pasirinkimas, rašymas į failus, testiniai failai, laiko matavimas |
| `v0.3` | `v0.3` | Šablonai, `vector` ir `list`, objekto adresas, konteinerių spartos palyginimas |
| `v1.0` | `v1.0` | Dalijimo strategijos S1, S2, Mano, Optimizuota; efektyvūs STL algoritmai; `CMakeLists.txt`; pilnas README |

### v.pradinė

Pirmoji veikianti versija: struktūra `Studentas`, `vector<Studentas>`, įvedimas ranka arba
atsitiktinis generavimas (`rand()`), galutinis balas pagal vidurkį ir medianą, lentelės išvedimas (`<iomanip>`),
įvesties klaidų tikrinimas. Failų skaitymo nebuvo, o visas sąrašas visada buvo išvedamas iš karto.

### v0.1

- Skaitymas iš failo (`SkaitytiIsFailo()`), paskutinis skaičius – egzaminas.
- Blogų įrašų atmetimas (`NeteisingiDuomenys`, `neteisingi`).
- Dalinė išvestis, kai studentų daugiau nei 40 (pirmi ir paskutiniai 20); rikiavimas pagal vardą.
- Pridėtas `.gitignore`, testinis failas `kursiokai.txt` su įterptomis klaidomis, ištaisytos įvedimo klaidos.

### v0.2

- Kodas išskaidytas į `Strukturos.h`, `StudentuFunkcijos.h`, `TestiniaiFailai.cpp`, `main.cpp`.
- Dalijimas į „vargšelius“ ir „kietuolius“ (`std::move`), rūšiavimo pasirinkimas, rašymas į `vargseliai.txt` / `kietuoliai.txt`.
- Testinių failų kūrimas (1 tūkst. – 10 mln.), spartos testavimas (3 kartai), `Laikmatis` su `std::chrono`.
- Galutiniai balai skaičiuojami vieną kartą (`galutinisVid`, `galutinisMed`), `mt19937` vietoje `rand()`.
- Pašalinta dalinė išvestis – rezultatai rašomi į failus.

### v0.3

- Funkcijos paverstos šablonais (`template <typename Container>`), veikia su `vector` ir `list`.
- `if constexpr` pasirenka `std::sort` arba `list::sort`; `shrink_to_fit()` tik `vector`.
- Objekto adreso išvedimas, abiejų konteinerių testavimas vienu paleidimu.
- Realizacijos perkeltos į `StudentuFunkcijos.h`, ne šablonų funkcijos ir globalūs kintamieji pažymėti `inline`.
- Konteinerių tyrimas (žr. aukščiau).

### v1.0

- Realizuotos strategijos **S1**, **S2**, **Mano** ir **Optimizuota** abiem konteineriams (žr. [Dalijimo strategijos](#dalijimo-strategijos-v10)).
- Naudojami efektyvūs algoritmai (`partition_copy`, `copy_if`, `remove_if`, `count_if`, `splice`).
- Testų paleidimas lygina visas strategijas su abiem konteineriais, 3 kartų vidurkis, ankstesnis failų generavimas.
- Pridėtas `CMakeLists.txt` (C++17, Release pagal nutylėjimą) ir diegimo instrukcija.
- README papildytas lentelėmis ir išvadomis.

**Apribojimai:** po dalijimo pradinis konteineris išvalomas; `RikiotiStudentus` palaiko tik `vector<Studentas>` ir `list<Studentas>`;
10 mln. įrašų testui reikia kelių GB RAM (ypač S1).