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
        int getLiczbaMiejsc() const;
        double getStawka() const;
        std::string getStandard() const;
        bool czyDostepny() const;
        void setDostepny(bool status);

        bool czyOdpowiedniDlaGosci(int liczbaOsob) const;
        void wyswietlSzczegoly() const;
};

#endif