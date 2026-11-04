#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <limits>

#include "faktura.h"
#include "gosc.h"
#include "osoba.h"
#include "pokoj.h"
#include "recepcjonista.h"
#include "rezerwacja.h"
#include "systemHotelu.h"
#include "uslugaDodatkowa.h"

void wyczyscBuforWejscia() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void uruchomScenariuszUserStories(SystemHotelu &hotel, int &kolejnyIdGoscia) {
    std::cout << "\n========================================================\n"
              << "   AUTOMATYCZNA DEMONSTRACJA USER STORIES (1 - 5)       \n"
              << "========================================================\n";

    int idGosciaDemo = kolejnyIdGoscia++;
    hotel.dodajGoscia(std::make_unique<Gosc>(
        idGosciaDemo, "Marek", "Nowak", "92051412345", "marek.nowak@email.pl", "500600700", "ul. Kwiatowa 10, Poznan"
    ));

    std::cout << "\n[USER STORY 1: Tworzenie / transakcja]\n"
              << "Cel: Gosc rezerwuje pokoj nr 101 na 3 doby i dolacza uslugi dodatkowe (Parking, Sniadanie).\n";
    int idRez1 = hotel.utworzRezerwacje(idGosciaDemo, 101, "2026-12-01", "2026-12-04", 3, 2);
    if (idRez1 != -1) {
        hotel.dodajUslugeDoRezerwacji(idRez1, UslugaDodatkowa(1, "Parking", 30.0));
        hotel.dodajUslugeDoRezerwacji(idRez1, UslugaDodatkowa(2, "Sniadanie", 50.0));
    }
    std::cout << "Weryfikacja blokady pokoju 101 (ponowne wyszukiwanie):\n";
    hotel.wyszukajDostepnePokoje("2026-12-01", "2026-12-04", 2, 3);

    std::cout << "\n[USER STORY 2: Wyszukiwanie / przegladanie]\n"
              << "Cel: Gosc wyszukuje dostepne pokoje w terminie 2026-12-01 - 2026-12-04 dla 2 osob (3 doby).\n";
    hotel.wyszukajDostepnePokoje("2026-12-01", "2026-12-04", 2, 3);

    std::cout << "\n[USER STORY 3 (czesc 1): Zarzadcza - Zameldowanie]\n"
              << "Cel: Recepcjonista melduje goscia przy przyjezdzie (zmiana statusu na ZAMELDOWANY).\n";
    hotel.zameldujGosc(idRez1);

    std::cout << "\n[USER STORY 3 (czesc 2) oraz USER STORY 4: Wymeldowanie i Faktura]\n"
              << "Cel: Recepcjonista wymeldowuje goscia i generuje fakture (3 doby x 200 PLN + 30 PLN + 50 PLN = 680 PLN).\n";
    hotel.wymeldujGosc(idRez1, "2026-12-04", "1234567890");
    hotel.oplacFakture(idRez1, "Karta");

    std::cout << "\n[USER STORY 5: Logika biznesowa / zarzadcza - Anulowanie rezerwacji]\n"
              << "Cel: Gosc tworzy nowa rezerwacje na pokoj 102, a nastepnie anuluje ja po przekroczeniu czasu.\n";
    int idRez2 = hotel.utworzRezerwacje(idGosciaDemo, 102, "2026-12-10", "2026-12-12", 2, 1);
    if (idRez2 != -1) {
        hotel.anulujRezerwacje(idRez2, true);
    }

    std::cout << "\n[PODSUMOWANIE KONTA GOSCIA PO SCENARIUSZACH]\n";
    hotel.wyswietlHistorieGoscia(idGosciaDemo);

    std::cout << "\n========================================================\n"
              << "         KONIEC DEMONSTRACJI USER STORIES               \n"
              << "========================================================\n";
}

int main() {
    SystemHotelu hotel("Grand Hotel");
    
    hotel.dodajPokoj(std::make_unique<Pokoj>(101, 2, 200.0, true, "Standard"));
    hotel.dodajPokoj(std::make_unique<Pokoj>(102, 1, 150.0, true, "Standard"));
    hotel.dodajPokoj(std::make_unique<Pokoj>(201, 4, 380.0, true, "Deluxe"));
    hotel.dodajPokoj(std::make_unique<Pokoj>(301, 2, 500.0, true, "Apartament"));

    hotel.dodajRecepcjoniste(std::make_unique<Recepcjonista>(1, "Jan", "Kowalski", 101, "2024-01-15", 4500.0));

    int opcja = -1;
    int kolejnyIdGoscia = 1;

    while (true) {
        std::cout << "\n========================================\n"
                  << "SYSTEM ZARZADZANIA HOTELEM: " << hotel.getNazwaHotelu() << "\n"
                  << "========================================\n"
                  << "1. Sprawdz dostepnosc i oszacuj koszt\n"
                  << "2. Wprowadz dane goscia i utworz rezerwacje\n"
                  << "3. Dodaj usluge dodatkowa do rezerwacji\n"
                  << "4. Zameldowanie goscia\n"
                  << "5. Wymeldowanie i rozliczenie goscia\n"
                  << "6. Anuluj rezerwacje\n"
                  << "7. Oplac fakture dla rezerwacji\n"
                  << "8. Wyszukaj dane i historie goscia\n"
                  << "9. Demonstracja wszystkich User Stories (1-5)\n"
                  << "0. Wyjscie\n"
                  << "Wybierz opcje: ";

        if (!(std::cin >> opcja)) {
            std::cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
            wyczyscBuforWejscia();
            continue;
        }
        wyczyscBuforWejscia();

        if (opcja == 0) {
            std::cout << "Zamykanie systemu...\n";
            break;
        }

        switch (opcja) {
            case 1: {
                std::string dataOd, dataDo;
                int liczbaOsob, liczbaDob;
                std::cout << "\n--- SPRAWDZANIE DOSTEPNOSCI POKOI ---\n"
                          << "Data zameldowania (RRRR-MM-DD): ";
                std::getline(std::cin, dataOd);
                std::cout << "Data wymeldowania (RRRR-MM-DD): ";
                std::getline(std::cin, dataDo);
                std::cout << "Liczba osob: ";
                std::cin >> liczbaOsob;
                std::cout << "Planowana liczba dob (0 jesli bez kalkulacji): ";
                std::cin >> liczbaDob;
                wyczyscBuforWejscia();

                hotel.wyszukajDostepnePokoje(dataOd, dataDo, liczbaOsob, liczbaDob);
                break;
            }
            case 2: {
                std::string imie, nazwisko, pesel, email, nrTel, adres;
                std::string dataOd, dataDo;
                int nrPokoju, liczbaDob, liczbaOsob;

                std::cout << "\n--- FORMULARZ REJESTRACJI GOSCIA ---\n"
                        << "Imie: ";
                std::getline(std::cin, imie);
                std::cout << "Nazwisko: ";
                std::getline(std::cin, nazwisko);

                do {
                    std::cout << "PESEL (11 cyfr): ";
                    std::getline(std::cin, pesel);
                    if (!Gosc::czyPoprawnyPesel(pesel)) {
                        std::cout << "Blad: PESEL musi miec dokladnie 11 cyfr! Sprobuj ponownie.\n";
                    }
                } while (!Gosc::czyPoprawnyPesel(pesel));

                do {
                    std::cout << "Email: ";
                    std::getline(std::cin, email);
                    if (!Gosc::czyPoprawnyEmail(email)) {
                        std::cout << "Blad: Niepoprawny format adresu email (wymagany znak @ i kropka)! Sprobuj ponownie.\n";
                    }
                } while (!Gosc::czyPoprawnyEmail(email));

                std::cout << "Numer telefonu: ";
                std::getline(std::cin, nrTel);
                std::cout << "Adres zamieszkania: ";
                std::getline(std::cin, adres);

                int idAktualnegoGoscia = kolejnyIdGoscia++;
                hotel.dodajGoscia(std::make_unique<Gosc>(idAktualnegoGoscia, imie, nazwisko, pesel, email, nrTel, adres));
                std::cout << ">> Zarejestrowano goscia o ID: " << idAktualnegoGoscia << "\n";

                std::cout << "\n--- PARAMETRY REZERWACJI ---\n"
                          << "Data od (RRRR-MM-DD): ";
                std::getline(std::cin, dataOd);
                std::cout << "Data do (RRRR-MM-DD): ";
                std::getline(std::cin, dataDo);
                std::cout << "Liczba dob: ";
                std::cin >> liczbaDob;
                std::cout << "Liczba gosci: ";
                std::cin >> liczbaOsob;
                std::cout << "Numer wybranego pokoju: ";
                std::cin >> nrPokoju;
                wyczyscBuforWejscia();

                int idNowejRez = hotel.utworzRezerwacje(idAktualnegoGoscia, nrPokoju, dataOd, dataDo, liczbaDob, liczbaOsob);
                if (idNowejRez != -1) {
                    char czyDodacUsluge;
                    std::cout << "Czy chcesz od razu dolaczyc usluge dodatkowa (np. parking, sniadanie)? (t/n): ";
                    std::cin >> czyDodacUsluge;
                    wyczyscBuforWejscia();

                    int licznikUslugLokalny = 1;
                    while (czyDodacUsluge == 't' || czyDodacUsluge == 'T') {
                        std::string nazwaUslugi;
                        double cenaUslugi;
                        std::cout << "Nazwa uslugi (np. Parking, Sniadanie): ";
                        std::getline(std::cin, nazwaUslugi);
                        std::cout << "Cena uslugi (PLN): ";
                        std::cin >> cenaUslugi;
                        wyczyscBuforWejscia();

                        hotel.dodajUslugeDoRezerwacji(idNowejRez, UslugaDodatkowa(licznikUslugLokalny++, nazwaUslugi, cenaUslugi));

                        std::cout << "Czy dodac kolejna usluge? (t/n): ";
                        std::cin >> czyDodacUsluge;
                        wyczyscBuforWejscia();
                    }
                }
                break;
            }
            case 3: {
                int idRezerwacji, idUslugi;
                std::string nazwaUslugi;
                double cena;

                std::cout << "\n--- DODAWANIE USLUGI DODATKOWEJ ---\n"
                          << "ID rezerwacji: ";
                std::cin >> idRezerwacji;
                std::cout << "ID uslugi: ";
                std::cin >> idUslugi;
                wyczyscBuforWejscia();
                std::cout << "Nazwa uslugi: ";
                std::getline(std::cin, nazwaUslugi);
                std::cout << "Cena (PLN): ";
                std::cin >> cena;
                wyczyscBuforWejscia();

                hotel.dodajUslugeDoRezerwacji(idRezerwacji, UslugaDodatkowa(idUslugi, nazwaUslugi, cena));
                break;
            }
            case 4: {
                int idRezerwacji;
                std::cout << "\n--- ZAMELDOWANIE GOSCIA ---\n"
                        << "ID rezerwacji: ";
                std::cin >> idRezerwacji;
                wyczyscBuforWejscia();

                hotel.zameldujGosc(idRezerwacji);
                break;
            }
            case 5: {
                int idRezerwacji;
                std::string dataWystawienia, nip = "";
                char czyVat;

                std::cout << "\n--- WYMELDOWANIE I ROZLICZENIE ---\n"
                          << "ID rezerwacji: ";
                std::cin >> idRezerwacji;
                wyczyscBuforWejscia();

                std::cout << "Data wystawienia faktury (RRRR-MM-DD): ";
                std::getline(std::cin, dataWystawienia);

                std::cout << "Czy wystawic fakture VAT na firme? (t/n): ";
                std::cin >> czyVat;
                wyczyscBuforWejscia();

                if (czyVat == 't' || czyVat == 'T') {
                    do {
                        std::cout << "Podaj NIP nabywcy (10 cyfr): ";
                        std::getline(std::cin, nip);
                        if (!Faktura::czyFakturaVat(nip)) {
                            std::cout << "Blad: NIP musi skladac sie dokladnie z 10 cyfr!\n";
                        }
                    } while (!Faktura::czyFakturaVat(nip));
                }

                hotel.wymeldujGosc(idRezerwacji, dataWystawienia, nip);
                break;
            }
            case 6: {
                int idRezerwacji;
                char pozno;
                std::cout << "\n--- ANULOWANIE REZERWACJI ---\n"
                          << "ID rezerwacji: ";
                std::cin >> idRezerwacji;
                std::cout << "Czy anulowanie nastepuje po regulaminowym czasie? (t/n): ";
                std::cin >> pozno;
                wyczyscBuforWejscia();

                hotel.anulujRezerwacje(idRezerwacji, (pozno == 't' || pozno == 'T'));
                break;
            }
            case 7: {
                int idRezerwacji;
                std::string metoda;
                std::cout << "\n--- OPLACENIE FAKTURY ---\n"
                          << "Podaj ID rezerwacji: ";
                std::cin >> idRezerwacji;
                wyczyscBuforWejscia();

                std::cout << "Wybierz metode platnosci (Karta / Gotowka / BLIK / Przelew): ";
                std::getline(std::cin, metoda);

                if (hotel.oplacFakture(idRezerwacji, metoda)) {
                    Rezerwacja* r = hotel.znajdzRezerwacje(idRezerwacji);
                    if (r && r->getFaktura()) {
                        r->getFaktura()->drukujFakture();
                    }
                }
                break;
            }
            case 8: {
                int idGoscia;
                std::cout << "\n--- WYSZUKIWANIE DANYCH GOSCIA ---\n"
                          << "Podaj ID goscia: ";
                std::cin >> idGoscia;
                wyczyscBuforWejscia();

                hotel.wyswietlHistorieGoscia(idGoscia);
                break;
            }
            case 9: {
                uruchomScenariuszUserStories(hotel, kolejnyIdGoscia);
                break;
            }
            default:
                std::cout << "Nieznana opcja. Wybierz liczbe od 0 do 9.\n";
                break;
        }
    }
    return 0;
}