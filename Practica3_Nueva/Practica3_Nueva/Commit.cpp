#include "Commit.h"
#include "VDinamico.h"

Commit::Commit() {
	codigo = " ";
	marcaDeTiempo = " ";
	mensaje = " ";
}

Commit::Commit(string mcodigo, string mmarcaDeTiempo, string mmensaje) {
	this->codigo = mcodigo;
	this->marcaDeTiempo = mmarcaDeTiempo;
	this->mensaje = mmensaje;
}


Commit::Commit(string mcodigo, string mmarcaDeTiempo, string mmensaje, VDinamico <Fichero *> mficheros) {
	this->codigo = mcodigo;
	this->marcaDeTiempo = mmarcaDeTiempo;
	this->mensaje = mmensaje;
	this->ficheros = mficheros;
}

Commit::Commit(const Commit& orig) {
	this->codigo = orig.codigo;
	this->marcaDeTiempo = orig.marcaDeTiempo;
	this->mensaje = orig.mensaje;
	this->ficheros = orig.ficheros;
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

void Commit::SetFicheros(VDinamico<Fichero*> mficheros) {
	this->ficheros = mficheros;
}

Fichero* Commit::GetFichero(int pos) {
	return ficheros[pos];
}

int Commit::tam_ficheros() {
	return ficheros.tam();
}

VDinamico<Fichero*> Commit::getFicheros() {
	VDinamico<Fichero*> vFicheros;
	Iterador<Fichero*> i = ficherosMod.iteradorInicio();
	int j = 0;
	while (i.existe()) {
		vFicheros.insertar(i.getDato(), j);
		j++;
		i.siguiente;
	}
}

void Commit::addFichero(Fichero* fich) {
	ficherosMod.insertarFinal(fich);
}

bool Commit::incluyeFichero(string nombre) {
	Iterador<Fichero*> i = ficherosMod.iteradorInicio();
	while (i.existe()) {
		if (i.getDato()->GetNombre() == nombre) return true;
		i.siguiente;
	}
	return false;
}

bool Commit::borrarFichero(string nombre) {
	Iterador<Fichero*> i = ficherosMod.iteradorInicio();
	while (i.existe()) {
		if (i.getDato->GetNombre() == nombre) {
			ficherosMod.borrar(i);
			return true;
		}
		i.siguiente;
	}
	return false;
}

bool Commit::entreFechas(Fecha finicio, Fecha ffin) {
	return fecha >= finicio && fecha <= ffin;
}

