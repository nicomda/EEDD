/* 
 * File:   Peticion.cpp
 * Author: macosx
 * 
 * Created on 25 de septiembre de 2014, 18:27
 */

#include "Peticion.h"

Peticion::Peticion(int _cod): _cod(0) {

}

Peticion::Peticion(const Peticion& orig) {
_cod=orig._cod;
_nPetic=orig._nPetic;
}

Peticion::~Peticion() {
}

void Peticion::AnadePeticion (int cod) {
    _nPetic++;
}

