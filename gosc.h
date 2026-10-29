#ifndef GOSC_H
#define GOSC_H

#include "osoba.h"
#include <string>
using namespace std;


class Gosc : public Osoba {
private:
    string pesel;
    string email;
    string nrTelefonu;
    string adresZamieszkania;

public:
    Gosc(int id, const string &imie, const string &nazwisko, const string &pesel, const string &email, const string &nrTelefonu, const string &adresZamieszkania);
    ~Gosc() override = default;

    void wyswietlInfo() const override;
    string getPesel() const;
    bool czyPoprawnyPesel() const;
    string pobierzDaneDoFaktury() const;
    void wyslijPotwierdzenieRezerwacji(int nrPokoju, const string &termin) const;
    bool zaktualizujDaneKontaktowe(const string &nowyEmail, const string& nowyNrTelefonu);
};

#endif