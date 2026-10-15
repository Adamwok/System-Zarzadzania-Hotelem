#ifndef POKOJ_H
#define POKOJ_H

using namespace std;

class Pokoj {
    private:
        int numer;
        int liczbaMiejsc;
        double stawkaDobowa;
        bool dostepny;
    
    public:
        Pokoj(int numer, int liczbaMiejsc, double stawkaDobowa, bool dostepny);

        int getNumer() const;
        double getStawka() const;
        bool czyDostepny() const;
        void setDostepny(bool status);
};

#endif