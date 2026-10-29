#include "gosc.h"
#include <iostream>
#include <string>
using namespace std;

Gosc::Gosc(int id, const string &imie, const string &nazwisko, const string &pesel, const string &email, const string & nrTelefonu, const string &adresZamieszkania)
    : Osoba(id, imie, nazwisko), pesel(pesel), email(email), nrTelefonu(nrTelefonu), adresZamieszkania(adresZamieszkania) {}

void Gosc::wyswietlInfo() const{
    cout << "[Gosc] ID: " << id << ", Imie: " << imie << ", Nazwisko: " << nazwisko << ", PESEL: " << pesel << endl;
}

string Gosc::getPesel() const {
    return pesel;
}

bool Gosc::czyPoprawnyPesel() const {
    if (pesel.length() != 11) return false;
    for (char c : pesel){
        if (!isdigit(c)) return false;
    }
    return true;
}

string Gosc::pobierzDaneDoFaktury() const {
    return imie + " " + nazwisko + ", PESEL" + pesel + ", Adres zamieszkania: " + adresZamieszkania + ", Numer telefonu: " + nrTelefonu + ", Adres email: " +   email;
}

void Gosc::wyslijPotwierdzenieRezerwacji(int nrPokoju, const string &termin) const{
    cout << "[Powiadomienie] Wysłano potwierdzenie rezerwacji na adres " << email << "\nZarezerwowano pokój " << nrPokoju << " w terminie " << termin << ".\n";
}

bool Gosc::zaktualizujDaneKontaktowe(const string &nowyEmail, const string &nowyNrTelefonu){
        if(nowyEmail.find('@') == string::npos || nowyNrTelefonu.empty()){
            return false;
        }
        email = nowyEmail;
        nrTelefonu = nowyNrTelefonu;
        return true;
    }