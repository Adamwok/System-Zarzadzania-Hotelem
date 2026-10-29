#include "UslugaDodatkowa.h"

UslugaDodatkowa::UslugaDodatkowa(int id, std::string nazwa, double cena)
    : idUslugi(id), nazwa(nazwa), cena(cena) {}

double UslugaDodatkowa::getCena() const {
    return cena;
}

std::string UslugaDodatkowa::getNazwa() const {
    return nazwa;
}