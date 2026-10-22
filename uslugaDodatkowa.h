#ifndef USLUGADODATKOWA_H
#define USLUGADODATKOWA_H

#include <string>
using namespace std;

class UslugaDodatkowa {
    private:
        string nazwa;
        double cena;
    
    public:
        UslugaDodatkowa(string nazwa, double cena);

        string getNazwa() const;
        double getCena() const;
};

#endif