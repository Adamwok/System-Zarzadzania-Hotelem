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
        string dataRozpoczecia;
        string dataZakonczenia;
        unique_ptr<Pokoj> pokoj;
        vector<UslugaDodatkowa> uslugiDodatkowe;
        unique_ptr<Faktura> faktura;


    public:
        Rezerwacja(int idRezerwacji, string dataRozpoczenia, string dataZakonczenia, unique_ptr<Pokoj> pokoj);
        ~Rezerwacja() = default;

        void dodajUsluge(const UslugaDodatkowa& usluga);
        double obliczKoszt() const;
        void wystawFakture(int idFaktury);
        double anuluj(bool czyPoTerminie);

        int getIdRezerwacji() const;
        const unique_ptr<Pokoj>& getPokoj() const;
};

#endif