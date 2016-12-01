#include "Fichero.h"
//Implementamos los constructores de la clase
Fichero::Fichero() {
	nombre = " ";
	ubicacion = " ";
	tamaBytes = 0;
}

Fichero::Fichero(string mnombre, string mubicacion, int mtamaBytes) {
	this->nombre = mnombre;
	this->ubicacion = mubicacion;
	this->tamaBytes = mtamaBytes;
}

Fichero::Fichero(const Fichero& orig) {
	this->nombre = orig.nombre;
	this->ubicacion = orig.ubicacion;
	this->tamaBytes = orig.tamaBytes;
}

Fichero::~Fichero() {

}