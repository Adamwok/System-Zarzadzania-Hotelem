#include "gosc.h"
#include <iostream>
#include <cctype>

Gosc::Gosc(int id, const std::string &imie, const std::string &nazwisko, const std::string &pesel, const std::string &email, const std::string &nrTelefonu, const std::string &adresZamieszkania)
    : Osoba(id, imie, nazwisko), pesel(pesel), email(email), nrTelefonu(nrTelefonu), adresZamieszkania(adresZamieszkania) {}

void Gosc::wyswietlInfo() const {
    std::cout << "[Gosc] ID: " << id << "\n"
              << " | Imie i nazwisko: " << imie << " " << nazwisko << "\n"
              << " | PESEL: " << pesel << "\n"
              << " | Telefon: " << nrTelefonu << "\n"
              << " | Email: " << email << "\n"
              << " | Adres: " << adresZamieszkania << "\n";
}

std::string Gosc::getPesel() const {
    return pesel;
}

std::string Gosc::getEmail() const {
    return email;
}

void Gosc::wyslijPotwierdzenieRezerwacji(int nrPokoju, const std::string &termin) const {
    std::cout << "[Powiadomienie EMAIL wyslane na: " << email << "]\n"
              << " Potwierdzenie: Zarezerwowano pokoj " << nrPokoju << " w terminie " << termin << ".\n";
}

bool Gosc::czyPoprawnyPesel(const std::string &p) {
    if (p.length() != 11) return false;
    for (char c : p) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool Gosc::czyPoprawnyEmail(const std::string &e) {
    return (e.find('@') != std::string::npos && e.find('.') != std::string::npos && e.length() >= 5);
}