#include "faktura.h"

Faktura::Faktura(int idFaktury, double kwotaCalkowita)
    : idFaktury(idFaktury), kwotaCalkowita(kwotaCalkowita) {}

int Faktura::getIdFaktury() const{
    return idFaktury;
}

double Faktura::getKwotaCalkowita() const {
    return kwotaCalkowita;
}