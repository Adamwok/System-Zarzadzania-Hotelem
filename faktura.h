#ifndef FAKTURA_H
#define FAKTURA_H
#include <string>

class Faktura {
    private:
        int idFaktury;
        double kwotaCalkowita;
        std::string dataWystawienia;
        std::string metodaPlatnosci;
        std::string statusPlatnosci;
        std::string numerFaktury;
        std::string nip;
    
    public:
        Faktura(int idFaktury, const std::string &numerFaktury, const std::string &dataWystawienia,  double kwotaCalkowita, const std::string &nip = "", const std::string &metodaPlatnosci = "BRAK", const std::string &statusPlatnosci = "OCZEKUJE_NA_PLATNOSC");
        ~Faktura() = default;

        double getKwotaCalkowita() const;
        int getIdFaktury() const;

        bool zarejestrujPlatnosc(const std::string &wybranaMetoda);
        void drukujFakture() const;
        bool czyFakturaVat() const;
        bool czyWymagaZaplaty() const;
};

#endif