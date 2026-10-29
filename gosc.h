#ifndef GOSC_H
#define GOSC_H

#include "osoba.h"
#include <string>
using namespace std;


class Gosc : public Osoba {
private:
    string pesel;

public:
    Gosc(int id, const string &imie, const string &nazwisko, const string &pesel);
    ~Gosc() override = default;

    void wyswietlInfo() const override;
    string getPesel() const;
};

#endif