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

void Cancion::SetInterprete(std::string _interprete) {
    this->_interprete = _interprete;
}

std::string Cancion::GetInterprete() const {
    return _interprete;
}

void Cancion::SetTitulo(std::string _titulo) {
    this->_titulo = _titulo;
}

std::string Cancion::GetTitulo() const {
    return _titulo;
}

void Cancion::SetCodigo(int _codigo) {
    this->_codigo = _codigo;
}

int Cancion::GetCodigo() const {
    return _codigo;
}

