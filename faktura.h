#ifndef FAKTURA_H
#define FAKTURA_H
#include <string>

using namespace std;

class Faktura {
    private:
        int idFaktury;
        double kwotaCalkowita;
        string dataWystawienia;
        string metodaPlatnosci;
        string statusPlatnosci;
        string numerFaktury;
        string nip;
    
    public:
        Faktura(int idFaktury, const string &numerFaktury, const string &dataWystawienia,  double kwotaCalkowita, const string &nip = "", const string &metodaPlatnosci = "BRAK", const string &statusPlatnosci = "OCZEKUJE_NA_PLATNOSC");
        ~Faktura() = default;

        double getKwotaCalkowita() const;
        int getIdFaktury() const;

        bool zarejestrujPlatnosc(const string &wybranaMetoda);
        void drukujFakture() const;
        bool czyFakturaVat() const;
        bool czyWymagaZaplaty() const;
};

#endif