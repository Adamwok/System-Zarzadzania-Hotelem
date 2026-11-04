#include "faktura.h"
#include <iostream>
#include <cctype>

Faktura::Faktura(int idFaktury, const std::string &numerFaktury, const std::string &dataWystawienia, double kwotaCalkowita, const std::string &nip, const std::string &metodaPlatnosci, const std::string &statusPlatnosci)
    : idFaktury(idFaktury), kwotaCalkowita(kwotaCalkowita), dataWystawienia(dataWystawienia), metodaPlatnosci(metodaPlatnosci), statusPlatnosci(statusPlatnosci), numerFaktury(numerFaktury), nip(nip) {}

int Faktura::getIdFaktury() const {
    return idFaktury;
}

std::string Faktura::getNumerFaktury() const {
    return numerFaktury;
}

double Faktura::getKwotaCalkowita() const {
    return kwotaCalkowita;
}

std::string Faktura::getStatusPlatnosci() const {
    return statusPlatnosci;
}

bool Faktura::zarejestrujPlatnosc(const std::string &wybranaMetoda) {
    if (statusPlatnosci == "OPLACONA") {
        return false;
    }
    metodaPlatnosci = wybranaMetoda;
    statusPlatnosci = "OPLACONA";
    return true;
}

void Faktura::drukujFakture() const {
    std::cout << "========================================\n"
              << " [FAKTURA]: " << numerFaktury << "\n"
              << " | Data wystawienia: " << dataWystawienia << "\n"
              << " | Status:           " << statusPlatnosci << "\n"
              << " | Metoda platnosci: " << metodaPlatnosci << "\n"; 
    if (!nip.empty()) {
        std::cout << " | NIP Nabywcy:      " << nip << " (FAKTURA VAT)\n";
    }
    std::cout << " | Kwota:            " << kwotaCalkowita << " PLN\n"
              << "========================================\n";
}

bool Faktura::czyFakturaVat(const std::string &n) {
    if (n.length() != 10) return false;
    for (char c : n) {
        if (!isdigit(c)) return false;
    }
    return true;
}