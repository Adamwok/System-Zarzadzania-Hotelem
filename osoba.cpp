#include "osoba.h"

Osoba::Osoba(int id, const std::string &imie, const std::string &nazwisko)
    : id(id), imie(imie), nazwisko(nazwisko) {}

int Osoba::getId() const {
    return id;
}