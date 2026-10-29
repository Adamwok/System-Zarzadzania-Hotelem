#ifndef USLUGADODATKOWA_H
#define USLUGADODATKOWA_H

#include <string>
using namespace std;

class UslugaDodatkowa {
    private:
        int idUslugi;
        string nazwa;
        double cena;
    
    public:
        UslugaDodatkowa(int id, string nazwa, double cena);

        double getCena() const;
        string getNazwa() const;
        int getIdUslugi() const;

};

#endif