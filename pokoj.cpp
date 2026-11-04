#include "pokoj.h"
#include <iostream>

Pokoj::Pokoj(int numer, int liczbaMiejsc, double stawkaDobowa, bool dostepny, const std::string &standardPokoju)
    : numer(numer), liczbaMiejsc(liczbaMiejsc), stawkaDobowa(stawkaDobowa), dostepny(dostepny), standardPokoju(standardPokoju) {}

int Pokoj::getNumer() const {
    return numer;
}

int Pokoj::getLiczbaMiejsc() const {
    return liczbaMiejsc;
}

double Pokoj::getStawka() const {
    return stawkaDobowa;
}

std::string Pokoj::getStandard() const {
    return standardPokoju;
}

bool Pokoj::czyDostepny() const {
    return dostepny;
}

void Pokoj::setDostepny(bool status) {
    dostepny = status;
}

bool Pokoj::czyOdpowiedniDlaGosci(int liczbaOsob) const {
    return dostepny && (liczbaMiejsc >= liczbaOsob);
}

void Pokoj::wyswietlSzczegoly() const {
    std::cout << "[Pokoj] Nr: " << numer
              << " | Standard: " << standardPokoju
              << " | Miejsca: " << liczbaMiejsc
              << " | Stawka: " << stawkaDobowa << " PLN/doba"
              << " | Status: " << (dostepny ? "Wolny" : "Zajety") << "\n";
}