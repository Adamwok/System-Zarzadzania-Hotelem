#ifndef USLUGADODATKOWA_H
#define USLUGADODATKOWA_H

#include <string>

class UslugaDodatkowa {
    private:
        int idUslugi;
        std::string kodUslugi;
        std::string nazwa;
        double cena;
        bool dostepna;
    
    public:
        UslugaDodatkowa::UslugaDodatkowa(int idUslugi, const std::string &kodUslugi, const std::string &nazwa, double cena, bool dostepna = true);
        ~UslugaDodatkowa() = default;

        bool czyDostepna() const;
        bool zarezerwujUsluge();
        void zwolnijUsluge();
        void wyswietlSzczegoly() const;

        double getCena() const;
        std::string getNazwa() const;
        int getIdUslugi() const;
        std::string getKodUslugi() const;
};

#endif