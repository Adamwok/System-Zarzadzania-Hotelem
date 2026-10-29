#include "uslugaDodatkowa.h"
#include <iostream>

UslugaDodatkowa::UslugaDodatkowa(int idUslugi, const std::string &kodUslugi, const std::string &nazwa, double cena, bool dostepna)
    : idUslugi(idUslugi), kodUslugi(kodUslugi), nazwa(nazwa), cena(cena), dostepna(dostepna) {}

bool UslugaDodatkowa::czyDostepna() const {
    return dostepna;
}

bool UslugaDodatkowa::zarezerwujUsluge() {
    if (!dostepna){
        return false;
    }
    dostepna = false;
    return true;
}

void UslugaDodatkowa::zwolnijUsluge() {
    dostepna = true;
}

void UslugaDodatkowa::wyswietlSzczegoly() const {
    std::cout << "[Usluga]" << kodUslugi << " - " << nazwa
              << "\n | Cena: " << cena << " PLN"
              << "\n | Dostepnosc: " << (dostepna ? "Dostepna" : "Zajeta/Niedostepna");
}

double UslugaDodatkowa::getCena() const {
    return cena;
}

std::string UslugaDodatkowa::getNazwa() const {
    return nazwa;
}

int UslugaDodatkowa::getIdUslugi() const {
    return idUslugi;
}

std::string UslugaDodatkowa::getKodUslugi() const {
    return kodUslugi;
}