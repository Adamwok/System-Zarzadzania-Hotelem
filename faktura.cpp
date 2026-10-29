#include "faktura.h"
#include <iostream>
#include <string>

Faktura::Faktura(int idFaktury, const std::string &numerFaktury, const std::string &dataWystawienia, double kwotaCalkowita, const std::string &nip, const std::string &metodaPlatnosci, const std::string &statusPlatnosci)
    : idFaktury(idFaktury), numerFaktury(numerFaktury), dataWystawienia(dataWystawienia), kwotaCalkowita(kwotaCalkowita), nip(nip), metodaPlatnosci(metodaPlatnosci), statusPlatnosci(statusPlatnosci) {}

int Faktura::getIdFaktury() const{
    return idFaktury;
}

double Faktura::getKwotaCalkowita() const {
    return kwotaCalkowita;
}

bool Faktura::zarejestrujPlatnosc(const std::string &wybranaMetoda){
    if (statusPlatnosci == "OPLACONA"){
        return false;
    }
    metodaPlatnosci = wybranaMetoda;
    statusPlatnosci = "OPLACONA";
    return true;
}

void Faktura::drukujFakture() const {
    std::cout << "========================================\n"
              << " [FAKTURA VAT]: " << numerFaktury << "\n"
              << " | Data wystawienia: " << dataWystawienia << "\n"
              << " | Status:           " << statusPlatnosci << "\n"
              << " | Metoda platnosci: " << metodaPlatnosci << "\n"; 
    if (!nip.empty()){
        std::cout
              << " | NIP Nabywcy:      " << nip << "\n";
    }
    std::cout << " | Kwota do zaplaty: " << kwotaCalkowita << " PLN\n"
              << "========================================\n";
}

bool Faktura::czyFakturaVat() const {
    if (nip.length() != 10){
        return false;
    }
    for (char c : nip) {
        if(!isdigit(c)){
            return false;
        }
    }
    return true;
}

bool Faktura::czyWymagaZaplaty() const {
    return statusPlatnosci != "OPLACONA";
}