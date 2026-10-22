#ifndef RECEPCJONISTA_H
#define RECEPCJONISTA_H

#include "osoba.h"
using namespace std;

class Recepcjonista : public Osoba {
    private:
        int idPracownika;
        string dataZatrudnienia;
        double pensja;
    
    public:
        Recepcjonista(int id, string imie, string nazwisko, int idPracownika, string dataZatrudnienia, double pensja);

        int getIdPracownika() const;
        void wyswietlInfo() const override;
};

#endif