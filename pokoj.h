#ifndef POKOJ_H
#define POKOJ_H

#include <string>

class Pokoj {
    private:
        int numer;
        int liczbaMiejsc;
        double stawkaDobowa;
        bool dostepny;
        std::string standardPokoju;
    
    public:
        Pokoj(int numer, int liczbaMiejsc, double stawkaDobowa, bool dostepny, const std::string &standardPokoju);
        ~Pokoj() = default;


        int getNumer() const;
        double getStawka() const;
        bool czyDostepny() const;
        void setDostepny(bool status);

        void zablokujDostepnosc();
        void zwolnijPokoj();
        bool czyOdpowiedniDlaGosci(int liczbaOsob) const;
        void wyswietlSzczegoly() const;
};

#endif