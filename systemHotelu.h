#ifndef SYSTEMHOTELU_H
#define SYSTEMHOTELU_H

#include <vector>
#include <memory>
#include <string>
#include "gosc.h"
#include "recepcjonista.h"
#include "pokoj.h"
#include "rezerwacja.h"
#include "uslugaDodatkowa.h"

class SystemHotelu {
    private:
        std::vector<std::unique_ptr<Gosc>> listaGosci;
        std::vector<std::unique_ptr<Recepcjonista>> listaRecepcjonistow;
        std::vector<std::unique_ptr<Pokoj>> listaPokoi;
        std::vector<std::unique_ptr<Rezerwacja>> aktywneRezerwacje;
        std::vector<std::unique_ptr<Rezerwacja>> zakonczoneRezerwacje;

        int licznikRezerwacji;
        int licznikFaktur;
        std::string nazwaHotelu;

        bool czyPokojWolnyWTerminie(int nrPokoju, const std::string &dataOd, const std::string &dataDo) const;

    public:
        SystemHotelu(const std::string &nazwa);
        ~SystemHotelu() = default;

        void dodajGoscia(std::unique_ptr<Gosc> gosc);
        void dodajRecepcjoniste(std::unique_ptr<Recepcjonista> recepcjonista);
        void dodajPokoj(std::unique_ptr<Pokoj> pokoj);

        void wyszukajDostepnePokoje(const std::string &dataOd, const std::string &dataDo, int liczbaOsob, int planowaneDoby) const;
        int utworzRezerwacje(int idGoscia, int nrPokoju, const std::string &dataOd, const std::string &dataDo, int liczbaDob, int liczbaOsob);
        void dodajUslugeDoRezerwacji(int idRezerwacji, const UslugaDodatkowa &usluga);
        void zameldujGosc(int idRezerwacji);
        void wymeldujGosc(int idRezerwacji, const std::string &dataWystawienia, const std::string &nip = "");
        void anulujRezerwacje(int idRezerwacji, bool czyPoTerminie);
        bool oplacFakture(int idRezerwacji, const std::string &metodaPlatnosci);

        void wyswietlHistorieGoscia(int idGoscia) const;
        std::string getNazwaHotelu() const;
        Rezerwacja* znajdzRezerwacje(int idRezerwacji);
        Gosc* znajdzGoscia(int idGoscia);
};

#endif