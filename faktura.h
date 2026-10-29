#ifndef FAKTURA_H
#define FAKTURA_H

using namespace std;

class Faktura {
    private:
        int idFaktury;
        double kwotaCalkowita;
    
    public:
        Faktura(int idFaktury, double kwotaCalkowita);
        ~Faktura() = default;

        double getKwotaCalkowita() const;
        int getIdFaktury() const;
};

#endif