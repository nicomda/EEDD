/* 
 * File:   Commit.cpp
 * Author: Miriam y Nico
 * 
 * Created on 4 de octubre de 2016, 12:02
 */

#include "Commit.h"
#include "VDinamico.h"
Commit::Commit() {
}

Commit::Commit(string mcodigo, string mmarcaDeTiempo, string mmensaje, VDinamico <Fichero*> mficheros) {
        this->codigo=mcodigo;
	this->marcaDeTiempo=mmarcaDeTiempo;
	this->mensaje=mmensaje;
	this->ficheros=mficheros;
}

Commit::Commit(const Commit& orig) {
    this->codigo=orig.codigo;
    this->marcaDeTiempo=orig.marcaDeTiempo;
    this->mensaje=orig.mensaje;
    this->ficheros=orig.ficheros;
}

Commit::~Commit() {
}

void Commit::SetCodigo(string mcodigo) {
	this->codigo = mcodigo;
}

string Commit::GetCodigo() const {
	return codigo;
}

void Commit::SetMarcaDeTiempo(string mmarcaDeTiempo) {
	this->marcaDeTiempo = mmarcaDeTiempo;
}

string Commit::GetMarcaDeTiempo() const {
	return marcaDeTiempo;
}

void Commit::SetMensaje(string mmensaje) {
	this->mensaje = mmensaje;
}

string Commit::GetMensaje() const {
	return mensaje;
}

void Commit::SetFicheros(VDinamico<Fichero*> ficheros) {
    this->ficheros = ficheros;
}

Fichero* Commit::GetFichero(int pos) {
    return ficheros[pos];
}

int Commit::tam_ficheros(){
    return ficheros.tam();
}

