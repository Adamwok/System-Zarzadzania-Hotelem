#include "UslugaDodatkowa.h"
using namespace std;

UslugaDodatkowa::UslugaDodatkowa(int idUslugi, string nazwa, double cena)
    : idUslugi(idUslugi), nazwa(nazwa), cena(cena) {}

double UslugaDodatkowa::getCena() const {
    return cena;
}

string UslugaDodatkowa::getNazwa() const {
    return nazwa;
}

int UslugaDodatkowa::getIdUslugi() const {
    return idUslugi;
}