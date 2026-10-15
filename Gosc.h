#ifndef GOSC_H
#define GOSC_H

#include "osoba.h"
using namespace std;

class Gosc : public Osoba {
    private:
        string pesel;
    
    public:
        Gosc(int id, string imie, string nazwisko, string pesel);

        string getPesel() const;
        void wyswietlInfo() const override;
};

#endif