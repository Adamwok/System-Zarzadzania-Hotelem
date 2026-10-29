#include "systemHotelu.h"
#include <iostream>
#include <utility>

SystemHotelu::SystemHotelu()
    : licznikRezerwacji(1), licznikFaktur(1) {}

void SystemHotelu::dodajGoscia(std::unique_ptr<Gosc> gosc) {
    listaGosci.push_back(std::move(gosc));
}

void SystemHotelu::dodajRecepcjoniste(std::unique_ptr<Recepcjonista> recepcjonista) {
    listaRecepcjonistow.push_back(std::move(recepcjonista));
}

void SystemHotelu::dodajPokoj(std::unique_ptr<Pokoj> pokoj) {
    listaPokoi.push_back(std::move(pokoj));
}

void SystemHotelu::wyszukajDostepnePokoje() const {
    std::cout << "[SystemHotelu] Wyszukiwanie dostepnych pokoi:" << std::endl;
    bool znaleziono = false;
    for (const auto& p : listaPokoi) {
        if (p->czyDostepny()){
            p->wyswietlSzczegoly();
            znaleziono = true;
        }
    }
    if(!znaleziono){
        std::cout << " | Brak wolnych pokoi w hotelu." << std::endl;
    }
}

void SystemHotelu::utworzRezerwacje(int idGoscia, int nrPokoju, const std::string &dataOd, const std::string &dataDo){
    std::unique_ptr<Pokoj> wybranyPokoj = nullptr;

    for (auto it = listaPokoi.begin(); it != listaPokoi.end(); ++it){
        if ((*it)->getNumer() == nrPokoju && (*it)->czyDostepny()) {
            wybranyPokoj = std::move(*it);
            listaPokoi.erase(it);
            break;
        }
    }

    if (wybranyPokoj) {
        int idNowejRezerwacji = licznikRezerwacji++;
        auto rezerwacja = std::make_unique<Rezerwacja>(idNowejRezerwacji, idGoscia, dataOd, dataDo, std::move(wybranyPokoj));
        aktywneRezerwacje.push_back(std::move(rezerwacja));
        std::cout << "[SystemHotelu] Utworzono rezerwacje o ID: " << idNowejRezerwacji
                    << " | Pokoj: " << nrPokoju << std::endl;
    } else {
        std::cout << "[SystemHotelu] Blad: Pokoj nr: " << nrPokoju << " nie istnieje lub jest zajęty." << std::endl;
    }
}

void SystemHotelu::zameldujGosc(int idRezerwacji) {
    Rezerwacja* rezerwacja = znajdzRezerwacje(idRezerwacji);
    if (rezerwacja != nullptr) {
        std::cout << "[SystemHotelu] Pomyslnie zameldowano goscia dla reerwacji ID: " << idRezerwacji << std::endl;
    } else {
        std::cout << "[SystemHotelu] Blad zameldowania: Nie znaleziono rezerwacji ID: " << idRezerwacji << std::endl; 
    }
}

void SystemHotelu::wymeldujGosc(int idRezerwacji) {
    for (auto it = aktywneRezerwacje.begin(); it != aktywneRezerwacje.end(); ++it){
        if((*it)->getIdRezerwacji() == idRezerwacji) {
            (*it)->wystawFakture(licznikFaktur++);

            const std::unique_ptr<Pokoj>& pokojRef = (*it)->getPokoj();
            if(pokojRef != nullptr) {
                pokojRef->setDostepny(true);
            }

            std::cout << "[Systemhotelu] Wymeldowano goscia z rezerwacji ID: " << idRezerwacji << std::endl;
            if((*it)->getFaktura() != nullptr) {
                (*it)->getFaktura()->drukujFakture();
            }

            std::unique_ptr<Pokoj> oddawanyPokoj = (*it)->oddajPokoj();
            if(oddawanyPokoj){
                listaPokoi.push_back(std::move(oddawanyPokoj));
            }

            aktywneRezerwacje.erase(it);
            return;
        }
    }
    std::cout << "[Systemhotelu] Blad: Nie znaleziono rezerwacji ID: " << idRezerwacji << " do anulowania.\n";
}

Rezerwacja* SystemHotelu::znajdzRezerwacje(int idRezerwacji) {
    for (const auto& rezerwacja : aktywneRezerwacje) {
        if (rezerwacja->getIdRezerwacji() == idRezerwacji) {
            return rezerwacja.get();
        }
    }
    return nullptr;
}