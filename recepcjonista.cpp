#include "recepcjonista.h"
#include <iostream>

Recepcjonista::Recepcjonista(int id, const std::string &imie, const std::string &nazwisko, int idPracownika, const std::string &dataZatrudnienia, double pensja)
    : Osoba(id, imie, nazwisko), idPracownika(idPracownika), dataZatrudnienia(dataZatrudnienia), pensja(pensja) {}

void Recepcjonista::wyswietlInfo() const {
    std::cout << "[Recepcjonista] ID: " << id
              << " | Pracownik: " << imie << " " << nazwisko
              << " | ID Slużbowe: " << idPracownika
              << " | Zatrudniony: " << dataZatrudnienia
              << " | Wynagrodzenie: " << pensja << " PLN\n";
}