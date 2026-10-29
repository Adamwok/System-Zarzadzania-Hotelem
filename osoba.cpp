#include "osoba.h"
#include <string>
using namespace std;

Osoba::Osoba(int id, const string &imie, const string &nazwisko)
    : id(id), imie(imie), nazwisko(nazwisko) {}