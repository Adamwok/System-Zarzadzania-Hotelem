#include "systemHotelu.h"
#include <iostream>
#include <utility>

SystemHotelu::SystemHotelu(const std::string &nazwa)
    : nazwaHotelu(nazwa), licznikRezerwacji(1), licznikFaktur(1) {}

std::string SystemHotelu::getNazwaHotelu() const {
    return nazwaHotelu;
}

void SystemHotelu::dodajGoscia(std::unique_ptr<Gosc> gosc) {
    listaGosci.push_back(std::move(gosc));
}

void SystemHotelu::dodajRecepcjoniste(std::unique_ptr<Recepcjonista> recepcjonista) {
    listaRecepcjonistow.push_back(std::move(recepcjonista));
}

void SystemHotelu::dodajPokoj(std::unique_ptr<Pokoj> pokoj) {
    listaPokoi.push_back(std::move(pokoj));
}

bool SystemHotelu::czyPokojWolnyWTerminie(int nrPokoju, const std::string &dataOd, const std::string &dataDo) const {
    for (const auto &rez : aktywneRezerwacje) {
        if (rez->getStatus() == "ANULOWANA" || rez->getStatus() == "ZAKONCZONA") {
            continue;
        }
        if (rez->getPokoj() && rez->getPokoj()->getNumer() == nrPokoju) {
            if (dataOd < rez->getDataZakonczenia() && dataDo > rez->getDataRozpoczecia()) {
                return false;
            }
        }
    }
    return true;
}

void SystemHotelu::wyszukajDostepnePokoje(const std::string &dataOd, const std::string &dataDo, int liczbaOsob, int planowaneDoby) const {
    std::cout << "\n[SystemHotelu] Dostepne pokoje (" << dataOd << " do " << dataDo << "):\n";
    bool znaleziono = false;
    for (const auto& p : listaPokoi) {
        if (p->czyOdpowiedniDlaGosci(liczbaOsob) && czyPokojWolnyWTerminie(p->getNumer(), dataOd, dataDo)) {
            p->wyswietlSzczegoly();
            if (planowaneDoby > 0) {
                double szacowanyKoszt = planowaneDoby * p->getStawka();
                std::cout << "  -> Szacowany koszt pobytu za " << planowaneDoby << " dob: " << szacowanyKoszt << " PLN\n";
            }
            znaleziono = true;
        }
    }
    if (!znaleziono) {
        std::cout << " | Brak pokoi spelniajacych kryteria (termin / liczba osob).\n";
    }
}

int SystemHotelu::utworzRezerwacje(int idGoscia, int nrPokoju, const std::string &dataOd, const std::string &dataDo, int liczbaDob, int liczbaOsob) {
    Gosc* gosc = znajdzGoscia(idGoscia);
    if (!gosc) {
        std::cout << "[SystemHotelu] Blad: Gosc o podanym ID nie istnieje.\n";
        return -1;
    }

    Pokoj* wybranyPokoj = nullptr;
    for (auto& p : listaPokoi) {
        if (p->getNumer() == nrPokoju) {
            wybranyPokoj = p.get();
            break;
        }
    }

    if (!wybranyPokoj) {
        std::cout << "[SystemHotelu] Blad: Pokoj nr " << nrPokoju << " nie istnieje.\n";
        return -1;
    }

    if (!wybranyPokoj->czyOdpowiedniDlaGosci(liczbaOsob)) {
        std::cout << "[SystemHotelu] Blad: Pokoj nr " << nrPokoju << " jest niedostepny lub ma za malo miejsc ("
                  << wybranyPokoj->getLiczbaMiejsc() << " miejsc dla " << liczbaOsob << " gosci).\n";
        return -1;
    }

    if (!czyPokojWolnyWTerminie(nrPokoju, dataOd, dataDo)) {
        std::cout << "[SystemHotelu] Blad: Pokoj nr " << nrPokoju << " jest zajety w wybranym terminie.\n";
        return -1;
    }

    // Kryterium akceptacji US 1: zablokowanie dostepnosci pokoju
    wybranyPokoj->setDostepny(false);

    int idNowejRezerwacji = licznikRezerwacji++;
    auto rezerwacja = std::make_unique<Rezerwacja>(idNowejRezerwacji, idGoscia, wybranyPokoj, dataOd, dataDo, liczbaDob, liczbaOsob);
    aktywneRezerwacje.push_back(std::move(rezerwacja));

    std::cout << "[SystemHotelu] Utworzono rezerwacje ID: " << idNowejRezerwacji << " | Pokoj: " << nrPokoju << " (Zablokowano dostepnosc)\n";
    gosc->wyslijPotwierdzenieRezerwacji(nrPokoju, dataOd + " - " + dataDo);
    return idNowejRezerwacji;
}

void SystemHotelu::dodajUslugeDoRezerwacji(int idRezerwacji, const UslugaDodatkowa &usluga) {
    Rezerwacja* rez = znajdzRezerwacje(idRezerwacji);
    if (rez != nullptr && rez->getStatus() == "NOWA") {
        rez->dodajUsluge(usluga);
        std::cout << "[SystemHotelu] Dodano usluge do rezerwacji ID: " << idRezerwacji << std::endl;
    } else {
        std::cout << "[SystemHotelu] Blad: Nie znaleziono aktywnej rezerwacji o ID: " << idRezerwacji << std::endl;
    }
}

void SystemHotelu::zameldujGosc(int idRezerwacji) {
    Rezerwacja* rezerwacja = znajdzRezerwacje(idRezerwacji);
    if (rezerwacja != nullptr && rezerwacja->getStatus() == "NOWA") {
        rezerwacja->zmienStatus("ZAMELDOWANY");
        if (rezerwacja->getPokoj() != nullptr) {
            rezerwacja->getPokoj()->setDostepny(false);
        }
        std::cout << "[SystemHotelu] Pomyslnie zameldowano goscia dla rezerwacji ID: " << idRezerwacji << std::endl;
    } else {
        std::cout << "[SystemHotelu] Blad: Brak rezerwacji lub nieodpowiedni status.\n";
    }
}

void SystemHotelu::wymeldujGosc(int idRezerwacji, const std::string &dataWystawienia, const std::string &nip) {
    for (auto it = aktywneRezerwacje.begin(); it != aktywneRezerwacje.end(); ++it) {
        if ((*it)->getIdRezerwacji() == idRezerwacji) {
            if ((*it)->getStatus() != "ZAMELDOWANY") {
                std::cout << "[SystemHotelu] Blad: Gosc nie jest zameldowany.\n";
                return;
            }

            (*it)->zmienStatus("ZAKONCZONA");
            (*it)->wystawFakture(licznikFaktur++, dataWystawienia, nip);

            Pokoj* pokojRef = (*it)->getPokoj();
            if (pokojRef != nullptr) {
                pokojRef->setDostepny(true);
            }

            std::cout << "[SystemHotelu] Wymeldowano goscia z rezerwacji ID: " << idRezerwacji << std::endl;
            if ((*it)->getFaktura() != nullptr) {
                (*it)->getFaktura()->drukujFakture();
            }

            zakonczoneRezerwacje.push_back(std::move(*it));
            aktywneRezerwacje.erase(it);
            return;
        }
    }
    std::cout << "[SystemHotelu] Blad: Nie znaleziono rezerwacji ID: " << idRezerwacji << ".\n";
}

void SystemHotelu::anulujRezerwacje(int idRezerwacji, bool czyPoTerminie) {
    for (auto it = aktywneRezerwacje.begin(); it != aktywneRezerwacje.end(); ++it) {
        if ((*it)->getIdRezerwacji() == idRezerwacji) {
            if ((*it)->getStatus() != "NOWA") {
                std::cout << "[SystemHotelu] Blad: Mozna anulowac tylko rezerwacje o statusie NOWA.\n";
                return;
            }

            (*it)->zmienStatus("ANULOWANA");
            if (czyPoTerminie) {
                double kara = (*it)->naliczOplateManipulacyjna(100.0);
                std::cout << "[SystemHotelu] Rezerwacja anulowana po terminie. Naliczono oplate manipulacyjna: " << kara << " PLN.\n";
            } else {
                std::cout << "[SystemHotelu] Rezerwacja anulowana bezplatnie.\n";
            }
            zakonczoneRezerwacje.push_back(std::move(*it));
            aktywneRezerwacje.erase(it);
            return;
        }
    }
    std::cout << "[SystemHotelu] Blad: Nie znaleziono rezerwacji ID: " << idRezerwacji << ".\n";
}

bool SystemHotelu::oplacFakture(int idRezerwacji, const std::string &metodaPlatnosci) {
    Rezerwacja* rez = znajdzRezerwacje(idRezerwacji);
    if (rez != nullptr && rez->getFaktura() != nullptr) {
        Faktura* f = rez->getFaktura();
        if (f->zarejestrujPlatnosc(metodaPlatnosci)) {
            std::cout << "[SystemHotelu] Platnosc dla faktury zarejestrowana pomyslnie.\n";
            return true;
        } else {
            std::cout << "[SystemHotelu] Faktura jest juz oplacona.\n";
            return false;
        }
    }
    std::cout << "[SystemHotelu] Nie znaleziono rezerwacji lub faktury dla ID: " << idRezerwacji << "\n";
    return false;
}

void SystemHotelu::wyswietlHistorieGoscia(int idGoscia) const {
    Gosc* gosc = nullptr;
    for (const auto& g : listaGosci) {
        if (g->getId() == idGoscia) {
            gosc = g.get();
            break;
        }
    }

    if (!gosc) {
        std::cout << "[SystemHotelu] Nie znaleziono goscia o ID: " << idGoscia << "\n";
        return;
    }

    std::cout << "\n========================================\n";
    std::cout << "         HISTORIA I DANE GOSCIA         \n";
    std::cout << "========================================\n";
    gosc->wyswietlInfo();

    std::cout << "\n--- REZERWACJE GOSCIA ---\n";
    bool maRezerwacje = false;

    auto wypiszRez = [&](const Rezerwacja& r) {
        std::cout << " * Rezerwacja ID: " << r.getIdRezerwacji()
                  << " | Pokoj: " << (r.getPokoj() ? r.getPokoj()->getNumer() : 0)
                  << " | Termin: " << r.getDataRozpoczecia() << " do " << r.getDataZakonczenia()
                  << " | Status: " << r.getStatus();
        if (r.getFaktura()) {
            std::cout << " | Nr Faktury: " << r.getFaktura()->getNumerFaktury()
                      << " (" << r.getFaktura()->getStatusPlatnosci() << ")";
        }
        std::cout << "\n";
        maRezerwacje = true;
    };

    for (const auto& r : aktywneRezerwacje) {
        if (r->getIdGoscia() == idGoscia) wypiszRez(*r);
    }
    for (const auto& r : zakonczoneRezerwacje) {
        if (r->getIdGoscia() == idGoscia) wypiszRez(*r);
    }

    if (!maRezerwacje) {
        std::cout << " Brak historii rezerwacji dla tego goscia.\n";
    }
    std::cout << "========================================\n";
}

Rezerwacja *SystemHotelu::znajdzRezerwacje(int idRezerwacji) {
    for (const auto& rezerwacja : aktywneRezerwacje) {
        if (rezerwacja->getIdRezerwacji() == idRezerwacji) {
            return rezerwacja.get();
        }
    }
    for (const auto& rezerwacja : zakonczoneRezerwacje) {
        if (rezerwacja->getIdRezerwacji() == idRezerwacji) {
            return rezerwacja.get();
        }
    }
    return nullptr;
}

Gosc *SystemHotelu::znajdzGoscia(int idGoscia) {
    for (const auto& g : listaGosci) {
        if (g->getId() == idGoscia) {
            return g.get();
        }
    }
    return nullptr;
}