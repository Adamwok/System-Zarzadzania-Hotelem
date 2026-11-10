#ifndef RECEPCJONISTA_H
#define RECEPCJONISTA_H

#include "osoba.h"
#include <string>

class Recepcjonista : public Osoba {
    private:
        int idPracownika;
        std::string dataZatrudnienia;
        double pensja;
    
    public:
        Recepcjonista(int id, const std::string &imie, const std::string &nazwisko, int idPracownika, const std::string &dataZatrudnienia, double pensja);
        void wyswietlInfo() const override;
};

#endif