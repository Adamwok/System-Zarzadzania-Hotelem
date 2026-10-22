#include "rezerwacja.h"
#include <string>
using namespace std;

Rezerwacja::Rezerwacja(int idRezerwacji, string dataRozpoczecia, string dataZakonczenia, unique_ptr<Pokoj> pokoj) : idRezerwacji(idRezerwacji), dataRozpoczecia(dataRozpoczecia), dataZakonczenia(dataZakonczenia), pokoj(move(pokoj)), faktura(nullptr) {}

void Rezerwacja::dodajUsluge(const UslugaDodatkowa& usluga) {
    uslugiDodatkowe.push_back(usluga);
}

double Rezerwacja::obliczKoszt() const {
    if (!pokoj){
        return 0.0;
    }
    double kosztUslug = 0.0;
    for (const auto& usluga : uslugiDodatkowe){
        kosztUslug += usluga.getCena();
    }
    return pokoj->getStawka() + kosztUslug;
}

void Rezerwacja::wystawFakture(int idFaktury){
    double kwota = obliczKoszt();
    faktura = make_unique<Faktura>(idFaktury, kwota);
}

double Rezerwacja::anuluj(bool czyPoTerminie) {
    if (pokoj) {
        pokoj->setDostepny(true);
    }
    if (czyPoTerminie){
        return 50.0;
    }
    return 0.0;
}

int Rezerwacja::getIdRezerwacji() const {
    return idRezerwacji;
}

const unique_ptr<Pokoj>& Rezerwacja::getPokoj() const {
    return pokoj;
}