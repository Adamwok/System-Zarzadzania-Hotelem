#ifndef OSOBA_H
#define OSOBA_H

#include <string>
using namespace std;


class Osoba {
    protected:
        int id;
        string imie;
        string nazwisko;
    
    public:
        Osoba(int id, string imie, string nazwisko);
        virtual ~Osoba() = default;

        int getId() const;
        string getImie() const;
        string getNazwisko() const;

        virtual void wyswietlInfo() const = 0;
};

#endif