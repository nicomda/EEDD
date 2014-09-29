/* 
 * File:   Cancion.cpp
 * Author: macosx
 * 
 * Created on 25 de septiembre de 2014, 17:57
 */

#include "Cancion.h"

Cancion::Cancion(int &codigo, string &titulo, string &interprete): _codigo(0), _titulo(""), _interprete("")  {
}

Cancion::Cancion(const Cancion& orig) {
    _codigo=orig._codigo;
    _titulo=orig._titulo;
    _interprete=orig._interprete;
}

Cancion::~Cancion() {
}

