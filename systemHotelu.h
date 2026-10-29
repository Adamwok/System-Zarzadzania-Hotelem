#ifndef SYSTEMHOTELU_H
#define SYSTEMHOTELU_H

#include <vector>
#include <memory>
#include <string>
#include "osoba.h"
#include "pokoj.h"
#include "rezerwacja.h"

using namespace std;

class SystemHotelu {
    private:
        vector<unique_ptr<Osoba>> listaOsob;
        vector<unique_ptr<Pokoj>> listaPokoi;
        vector<unique_ptr<Rezerwacja>> aktywneRezerwacje;
    
    public:
        SystemHotelu() = default;
        ~SystemHotelu() = default;

        vector<Pokoj*> wyszukajDostepnePokoje() const;
        void utworzRezerwacje(int idGoscia, int nrPokoju, string dataOd, string dataDo, int idRezerwacji);
        void zameldujGosc(int idRezerwacji);
        void wymeldujGosc(int idRezerwacji, int idFaktury);
        void anulujRezerwacje(int idRezerwacji, bool czyPoTerminie);
};

#endif