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
        Pokoj* pokoj;
        int liczbaDob;
        int liczbaOsob;
        double oplataManipulacyjna;
        std::string status;
        std::string dataRozpoczecia;
        std::string dataZakonczenia;
        std::vector<UslugaDodatkowa> uslugiDodatkowe;
        std::unique_ptr<Faktura> faktura;

    public:
        Rezerwacja(int idRezerwacji, int idGoscia, Pokoj* pokoj, const std::string &dataRozpoczecia, const std::string &dataZakonczenia, int liczbaDob, int liczbaOsob);
        ~Rezerwacja() = default;

        void dodajUsluge(const UslugaDodatkowa &usluga);
        double obliczKosztUslug() const;
        double obliczKosztCalkowity() const;
        void zmienStatus(const std::string &nowyStatus);
        void wystawFakture(int idFaktury, const std::string &dataWystawiania, const std::string &nip = "");
        double naliczOplateManipulacyjna(double kwotaKary);

        int getIdRezerwacji() const;
        int getIdGoscia() const;
        Pokoj* getPokoj() const;
        Faktura* getFaktura() const;
        std::string getDataRozpoczecia() const;
        std::string getDataZakonczenia() const;
        int getLiczbaDob() const;
        int getLiczbaOsob() const;
        std::string getStatus() const;
        double getOplataManipulacyjna() const;
};

#endif