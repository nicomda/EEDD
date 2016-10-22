#include "Fichero.h"

Fichero::Fichero() {
	nombre = "";
	ubicacion = "";
	tamaBytes = 0;

}

Fichero::Fichero(string mnombre, string mubicacion, int mtamaBytes) {
	this->nombre = mnombre;
	this->ubicacion = mubicacion;
	this->tamaBytes = mtamaBytes;
}

Fichero::Fichero(const Fichero& orig) {
	nombre = orig.nombre;
	ubicacion = orig.ubicacion;
	tamaBytes = orig.tamaBytes;
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




