#include "pokoj.h"
#include <iostream>
#include <string>

Pokoj::Pokoj(int numer, int liczbaMiejsc, double stawkaDobowa, bool dostepny, const std::string &standardPokoju)
    : numer(numer), liczbaMiejsc(liczbaMiejsc), stawkaDobowa(stawkaDobowa), dostepny(dostepny), standardPokoju(standardPokoju) {}

int Pokoj::getNumer() const {
    return numer;
}

double Pokoj::getStawka() const {
    return stawkaDobowa;
}

bool Pokoj::czyDostepny() const {
    return dostepny;
}

void Pokoj::setDostepny(bool status) {
    dostepny = status;
}

void Pokoj::zablokujDostepnosc() {
    dostepny = false;
}

bool Pokoj::czyOdpowiedniDlaGosci(int liczbaOsob) const {
    return dostepny && (liczbaMiejsc >= liczbaOsob);
}

void Pokoj::zwolnijPokoj(){
    dostepny = true;
}

void Pokoj::wyswietlSzczegoly() const {
    std::cout << "[Pokoj] Nr: " << numer
         << " | Standard: " << standardPokoju
         << " | Liczba miejsc: " << liczbaMiejsc
         << " | Stawka: " << stawkaDobowa << " PLN/doba"
         << " | Status: " << (dostepny ? "Wolny" : "Zajety") << std::endl;
}