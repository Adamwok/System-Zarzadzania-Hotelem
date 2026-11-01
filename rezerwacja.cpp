#include "rezerwacja.h"
#include "faktura.h"
#include <string>
#include <utility>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

Rezerwacja::Rezerwacja(int idRezerwacji, int idGoscia, std::string dataRozpoczecia, std::string dataZakonczenia, unique_ptr<Pokoj> pokoj) : idRezerwacji(idRezerwacji), idGoscia(idGoscia), dataRozpoczecia(dataRozpoczecia), dataZakonczenia(dataZakonczenia), pokoj(std::move(pokoj)), faktura(nullptr) {}

int Rezerwacja::getIdRezerwacji() const {
    return idRezerwacji;
}

int Rezerwacja::getIdGoscia() const {
    return idGoscia;
}

const std::unique_ptr<Pokoj>& Rezerwacja::getPokoj() const {
    return pokoj;
}

std::unique_ptr<Pokoj> Rezerwacja::oddajPokoj() {
    return std::move(pokoj);
}

const std::unique_ptr<Faktura> &Rezerwacja::getFaktura() const {
    return faktura;
}

void Rezerwacja::dodajUsluge(const UslugaDodatkowa& usluga) {
    uslugiDodatkowe.push_back(usluga);
}

double Rezerwacja::obliczKoszt() const {
    double koszt = 0.0;
    if(pokoj != nullptr) {
        koszt += (*pokoj).getStawka();
    }
    for(const auto& usluga : uslugiDodatkowe) {
        koszt += usluga.getCena();
    }
    return koszt;
}

void Rezerwacja::wystawFakture(int idFaktury){
    double kwota = obliczKoszt();
    auto teraz = std::chrono::system_clock::now();
    std::time_t czas = std::chrono::system_clock::to_time_t(teraz);
    std::tm czasLokalny = *std::localtime(&czas);

    std::ostringstream ssData;
    ssData << std::put_time(&czasLokalny, "%Y-%m-%d");
    std::string dataWystawienia = ssData.str();

    std::ostringstream ssNumer;
    ssNumer << "FV/" << std::put_time(&czasLokalny, "%Y-/%m/") << idFaktury;
    std::string numerFaktury = ssNumer.str();

    faktura = std::make_unique<Faktura> (idFaktury, numerFaktury, dataWystawienia, kwota);
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

