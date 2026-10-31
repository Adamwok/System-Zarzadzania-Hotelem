#ifndef REZERWACJA_H
#define REZERWACJA_H

#include <string>
#include <vector>
#include <memory>
#include "pokoj.h"
#include "uslugaDodatkowa.h"
#include "faktura.h"

class Rezerwacja {
    private:
        int idRezerwacji;
        int idGoscia;
        std::string dataRozpoczecia;
        std::string dataZakonczenia;
        std::unique_ptr<Pokoj> pokoj;
        std::vector<UslugaDodatkowa> uslugiDodatkowe;
        std::unique_ptr<Faktura> faktura;


    public:
        Rezerwacja(int idRezerwacji, int idGoscia,  std::string dataRozpoczenia, std::string dataZakonczenia, std::unique_ptr<Pokoj> pokoj);
        ~Rezerwacja() = default;

        void dodajUsluge(const UslugaDodatkowa &usluga);
        double obliczKoszt() const;
        void wystawFakture(int idFaktury);
        double anuluj(bool czyPoTerminie);

        int getIdGoscia() const;
        int getIdRezerwacji() const;
        const std::unique_ptr<Pokoj>& Rezerwacja::getPokoj() const;
        std::unique_ptr<Pokoj> oddajPokoj();
        const std::unique_ptr<Faktura> &getFaktura() const;
};

#endif