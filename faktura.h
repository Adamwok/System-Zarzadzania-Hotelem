#ifndef FAKTURA_H
#define FAKTURA_H

#include <string>
using namespace std;

class Faktura {
    private:
        int idFaktury;
        double kwotaCalkowita;
    
    public:
        Faktura(int idFaktury, double kwotaCalkowita);

        double getKwotaCalkowita() const;
};

#endif