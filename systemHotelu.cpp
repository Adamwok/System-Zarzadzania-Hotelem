#include "systemHotelu.h"
#include "pokoj.h"
#include "faktura.h"
#include <algorithm>
using namespace std;

bool SystemHotelu::utworzRezerwacje(int idGoscia, int nrPokoju, string dataOd, string dataDo, int idRezerwacji) {
    shared_ptr<Pokoj> docelowyPokoj = nullptr;

    for (auto& p : pokoje) {
        if (p->getNrPokoju() == nrPokoju) {
            docelowyPokoj = p;
            break;
        }
    }

    if (docelowyPokoj != nullptr && docelowyPokoj->czyDostepny()) {
        rezerwacje.emplace_back(idRezerwacji, idGoscia, dataOd, dataDo, docelowyPokoj);
        return true;
    }

    return false;
}

unique_ptr<Faktura> SystemHotelu::wymeldujGosc(int idRezerwacji, int idFaktury) {
    Rezerwacja * rezerwacja = nullptr;

    for (auto& r : rezerwacje) {
        if (r.getIdRezerwacji() == idRezerwacji) {
            rezerwacja = &r;
            break;
        }
    }

    if (rezerwacja == nullptr) {
        return nullptr;
    }

    auto faktura = rezerwacja->wystawFakture(idFaktury);

    const auto& pokoj = rezerwacja->getPokoj();
    if (pokoj != nullptr) {
        pokoj->setDostepny(true);
    }

    rezerwacja->setZameldowany(false);
    return faktura;
}

void SystemHotelu::zameldujGoscia(int idRezerwacji) {
    for (auto& r : rezerwacje) {
        if (r.getIdRezerwacji() == idRezerwacji) {
            r.setZameldowany(true);
            break;
        }
    }
}

void SystemHotelu::dodajPokoj(shared_ptr<Pokoj> pokoj) {
    pokoje.push_back(pokoj);
}