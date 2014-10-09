/* 
 * File:   Peticion.cpp
 * Author: macosx
 * 
 * Created on 25 de septiembre de 2014, 18:27
 */

#include "Peticion.h"

Peticion::Peticion(int cod): _cod(0) {
    SetCod(cod);
}

Peticion::Peticion(const Peticion& orig) {
_cod=orig._cod;
_nPetic=orig._nPetic;
}

Peticion::~Peticion() {
}

void Peticion::AnadePeticion () {
    _nPetic++;
}

void Peticion::SetNPetic(int _nPetic) {
    this->_nPetic = _nPetic;
}

int Peticion::GetNPetic() const {
    return _nPetic;
}

void Peticion::SetCod(int _cod) {
    this->_cod = _cod;
}

int Peticion::GetCod() const {
    return _cod;
}

