# SZE-MOSZE-2020-SeGITseg
**Beadandó feladat a Modern szoftverfejlesztési eszközök (GKNB_INTM006) nevű tárgyra**

Készítették: Boros Dávid (H89ZV9), Káldy Kristóf (R9ZHPM), Kreutzog András (TDM5KG)

Széchenyi István Egyetem, 2020/21-as tanév, 1. félév

## A program működése

A játékot egy időben 2 karakter játssza, amelyek adatai futáskor JSON típusú fájlokból kerülnek betöltésre. Ha a fájlok nem léteznek, akkor hibaüzenetet ír ki a program. 

A karakterek adatai:
- name: a karakter neve (string)
- hp: a karakter életereje (int)
- dmg: a karakter sebzése (int)
- cd: a karakter támadásának sebessége (double)

Amennyiben a beolvasás megtörtént, megkezdődik a játék. Összesen három karakter van, melyek kettesével, felváltva támadják egymást, sebzést okozva a másiknak. A harcnak akkor van vége, amikor az egyik karakter életereje 0-ra csökken, ezután indul a következő harc, egészen addig amíg az összes lehetséges kombináció le nem fut.

Amikor az unitok egyesével megküzdenek egymással, akkor a program kiírja egy szöveges fájlba (`results.txt`) a harcok kimenetelét.

Végül a `results.txt` fájlt a program összehasonlítja egy `expected_results.txt` fájllal és ha esetleg nem egyeznek meg, akkor jelzi, hogy hiba van a kódban.

## A program futtatása

A programot a `test_workflow.yml` workflow futtatja.

Ez a kódot először lefordítja `g++ -std=c++17 *.cpp`, majd futtatja a script (`run_test.sh`) segítségével, valamint ellenőrzi, hogy helyesen futott-e le a program `diff test/results.txt test/expected_results.txt`. 

A `docs_workflow.yml` workflow a gh-pages branchen tárolja a dokumentációhoz tartozó fájlokat.

## A program dokumentációja

A program doxygen dokumentációja az alábbi linken található:

https://teaching-projects.github.io/SZE-MOSZE-2020-SeGITseg/
