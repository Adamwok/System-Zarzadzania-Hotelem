#include "gosc.h"
#include <iostream>
#include <string>
using namespace std;

Gosc::Gosc(int id, const string &imie, const string &nazwisko, const string &pesel)
    : Osoba(id, imie, nazwisko), pesel(pesel) {}

void Gosc::wyswietlInfo() const{
    cout << "[Gosc] ID: " << id << ", Imie: " << imie << ", Nazwisko: " << nazwisko << ", PESEL: " << pesel << endl;
}

string Gosc::getPesel() const {
    return pesel;
}