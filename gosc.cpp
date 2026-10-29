#include "gosc.h"
#include <iostream>
#include <string>

Gosc::Gosc(int id, const std::string &imie, const std::string &nazwisko, const std::string &pesel, const std::string &email, const std::string & nrTelefonu, const std::string &adresZamieszkania)
    : Osoba(id, imie, nazwisko), pesel(pesel), email(email), nrTelefonu(nrTelefonu), adresZamieszkania(adresZamieszkania) {}

void Gosc::wyswietlInfo() const{
    std::cout << "[Gosc] ID: " << id << "\n"
              << " | Imie: " << imie << "\n"
              << " | Nazwisko: " << nazwisko << "\n"
              << " | PESEL: " << pesel << std::endl;
}

std::string Gosc::getPesel() const {
    return pesel;
}

bool Gosc::czyPoprawnyPesel() const {
    if (pesel.length() != 11) return false;
    for (char c : pesel){
        if (!isdigit(c)) return false;
    }
    return true;
}

std::string Gosc::pobierzDaneDoFaktury() const {
    return imie + " " + nazwisko + ", PESEL" + pesel + ", Adres zamieszkania: " + adresZamieszkania + ", Numer telefonu: " + nrTelefonu + ", Adres email: " +   email;
}

void Gosc::wyslijPotwierdzenieRezerwacji(int nrPokoju, const std::string &termin) const{
    std::cout << "[Powiadomienie] Wysłano potwierdzenie rezerwacji na adres " << email << "\n"
              << "Zarezerwowano pokój " << nrPokoju << " w terminie " << termin << "." << std::endl;
}

bool Gosc::zaktualizujDaneKontaktowe(const std::string &nowyEmail, const std::string &nowyNrTelefonu){
        if(nowyEmail.find('@') == std::string::npos || nowyNrTelefonu.empty()){
            return false;
        }
        email = nowyEmail;
        nrTelefonu = nowyNrTelefonu;
        return true;
    }