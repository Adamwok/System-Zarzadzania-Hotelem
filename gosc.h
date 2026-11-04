#ifndef GOSC_H
#define GOSC_H

#include "osoba.h"
#include <string>

class Gosc : public Osoba {
private:
    std::string pesel;
    std::string email;
    std::string nrTelefonu;
    std::string adresZamieszkania;

public:
    Gosc(int id, const std::string &imie, const std::string &nazwisko, const std::string &pesel, const std::string &email, const std::string &nrTelefonu, const std::string &adresZamieszkania);
    ~Gosc() override = default;

    void wyswietlInfo() const override;
    std::string getPesel() const;
    std::string getEmail() const;
    void wyslijPotwierdzenieRezerwacji(int nrPokoju, const std::string &termin) const;

    static bool czyPoprawnyPesel(const std::string &pesel);
    static bool czyPoprawnyEmail(const std::string &email);
};

#endif