#include "rezerwacja.h"

Rezerwacja::Rezerwacja(int idRezerwacji, int idGoscia, Pokoj* pokoj, const std::string &dataRozpoczecia, const std::string &dataZakonczenia, int liczbaDob, int liczbaOsob)
    : idRezerwacji(idRezerwacji), idGoscia(idGoscia), pokoj(pokoj), liczbaDob(liczbaDob), liczbaOsob(liczbaOsob), oplataManipulacyjna(0.0), status("NOWA"), dataRozpoczecia(dataRozpoczecia), dataZakonczenia(dataZakonczenia), faktura(nullptr) {}

void Rezerwacja::dodajUsluge(const UslugaDodatkowa &usluga) {
    uslugiDodatkowe.push_back(usluga);
}

double Rezerwacja::obliczKosztUslug() const {
    double suma = 0.0;
    for (const auto &usluga : uslugiDodatkowe) {
        suma += usluga.getCena();
    }
    return suma;
}

double Rezerwacja::obliczKosztCalkowity() const {
    double kosztPokoju = 0.0;
    if (pokoj != nullptr) {
        kosztPokoju = liczbaDob * pokoj->getStawka();
    }
    return kosztPokoju + obliczKosztUslug() + oplataManipulacyjna;
}

void Rezerwacja::zmienStatus(const std::string &nowyStatus) {
    status = nowyStatus;
}

void Rezerwacja::wystawFakture(int idFaktury, const std::string &dataWystawiania, const std::string &nip) {
    double kwota = obliczKosztCalkowity();
    std::string nrFaktury = "FV/" + std::to_string(idFaktury) + "/2026";
    faktura = std::make_unique<Faktura>(idFaktury, nrFaktury, dataWystawiania, kwota, nip);
}

double Rezerwacja::naliczOplateManipulacyjna(double kwotaKary) {
    oplataManipulacyjna = kwotaKary;
    return oplataManipulacyjna;
}

int Rezerwacja::getIdRezerwacji() const { return idRezerwacji; }
int Rezerwacja::getIdGoscia() const { return idGoscia; }
Pokoj* Rezerwacja::getPokoj() const { return pokoj; }
Faktura* Rezerwacja::getFaktura() const { return faktura.get(); }
std::string Rezerwacja::getDataRozpoczecia() const { return dataRozpoczecia; }
std::string Rezerwacja::getDataZakonczenia() const { return dataZakonczenia; }
int Rezerwacja::getLiczbaDob() const { return liczbaDob; }
int Rezerwacja::getLiczbaOsob() const { return liczbaOsob; }
std::string Rezerwacja::getStatus() const { return status; }
double Rezerwacja::getOplataManipulacyjna() const { return oplataManipulacyjna; }