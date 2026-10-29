#ifndef SYSTEMHOTELU_H
#define SYSTEMHOTELU_H

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "gosc.h"
#include "recepcjonista.h"
#include "pokoj.h"
#include "rezerwacja.h"

using namespace std;

class SystemHotelu {
    private:
        std::vector<std::unique_ptr<Gosc>> listaGosci;
        std::vector<std::unique_ptr<Recepcjonista>> listaRecepcjonistow;
        std::vector<std::unique_ptr<Pokoj>> listaPokoi;
        std::vector<std::unique_ptr<Rezerwacja>> aktywneRezerwacje;

        int licznikRezerwacji;
        int licznikFaktur;
    
    public:
        SystemHotelu() = default;
        ~SystemHotelu() = default;

        void dodajGoscia(std::unique_ptr<Gosc> gosc);
        void dodajRecepcjoniste(std::unique_ptr<Recepcjonista> recepcjonista);
        void dodajPokoj(std::unique_ptr<Pokoj> pokoj);

        void wyszukajDostepnePokoje() const;
        void utworzRezerwacje(int idGoscia, int nrPokoju, const std::string &dataOd, const std::string &dataDo);
        void zameldujGosc(int idRezerwacji);
        void wymeldujGosc(int idRezerwacji);
        void anulujRezerwacje(int idRezerwacji);

        Rezerwacja& znajdzRezerwacje(int idRezerwacji);
};

#endif