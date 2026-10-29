#include "pokoj.h"

Pokoj::Pokoj(int numer, int liczbaMiejsc, double stawkaDobowa, bool dostepny)
    : numer(numer), liczbaMiejsc(liczbaMiejsc), stawkaDobowa(stawkaDobowa), dostepny(dostepny) {}

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