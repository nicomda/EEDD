/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Fichero.cpp
 * Author: Miriam y Nico
 * 
 * Created on 4 de octubre de 2016, 12:02
 */

#include "Fichero.h"
#include <iostream>
#include <string>

Fichero::Fichero() {
    
}

Fichero::Fichero(string mnombre, string mubicacion, int mtamaBytes){	
	this->nombre = mnombre;
	this->ubicacion = mubicacion;
	this->tamaBytes = mtamaBytes;
}

Fichero::Fichero(const Fichero& orig) {
   
}

Fichero::~Fichero() {
    
}

void Fichero::SetTamaBytes(int tamaBytes) {
    this->tamaBytes = tamaBytes;
}

int Fichero::GetTamaBytes() const {
    return tamaBytes;
}

void Fichero::SetUbicacion(string ubicacion) {
    this->ubicacion = ubicacion;
}

string Fichero::GetUbicacion() const {
    return ubicacion;
}

void Fichero::SetNombre(string nombre) {
    this->nombre = nombre;
}

string Fichero::GetNombre() const {
    return nombre;
}




