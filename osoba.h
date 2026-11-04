#ifndef OSOBA_H
#define OSOBA_H

#include <string>

class Osoba {
    protected:
        int id;
        std::string imie;
        std::string nazwisko;
    
    public:
        Osoba(int id, const std::string &imie, const std::string &nazwisko);
        virtual ~Osoba() = default;

        int getId() const;
        virtual void wyswietlInfo() const = 0;
};

#endif