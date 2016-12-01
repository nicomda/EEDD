/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



#include "Fichero.h"

Fichero::Fichero() 
{
    _nombre="---";
    _ubicacion="---";
    _tamaBytes=0;
}

Fichero::Fichero(const Fichero& orig): _nombre(orig._nombre), _ubicacion(orig._ubicacion),
_tamaBytes(orig._tamaBytes)
{
    
}

Fichero::~Fichero() 
{
}

void Fichero::SetTamaBytes(int _tamaBytes)
{
    this->_tamaBytes = _tamaBytes;
}

int Fichero::GetTamaBytes() const 
{
    return _tamaBytes;
}

void Fichero::SetUbicacion(std:: string _ubicacion) {
    this->_ubicacion = _ubicacion;
}

std:: string Fichero::GetUbicacion() const {
    return _ubicacion;
}

void Fichero::SetNombre(std:: string _nombre) {
    this->_nombre = _nombre;
}

std:: string Fichero::GetNombre() const {
    return _nombre;
}

Fichero::Fichero(std::string nombre, std::string ubicacion, int tama){
	_nombre = nombre;
	_ubicacion = ubicacion;
	_tamaBytes = tama;

}