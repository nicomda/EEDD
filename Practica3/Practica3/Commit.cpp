#include "Commit.h"
#include "VDinamico.h"

Commit::Commit() {
	codigo = "";
	marcaDeTiempo = "";
	mensaje = "";
}

Commit::Commit(string mcodigo, string mmarcaDeTiempo, string mmensaje, VDinamico <Fichero*> mficheros) {
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

void Commit::SetFicheros(VDinamico<Fichero*> ficheros) {
	this->ficheros = ficheros;
}

Fichero* Commit::GetFichero(int pos) {
	return ficheros[pos];
}

int Commit::tam_ficheros() {
	return ficheros.tam();
}

void Commit::addfichero(Fichero *fich) {
	ficherosMod.insertarFinal(fich);
}

bool Commit::incluyeFichero(string nombre) {
	Iterador<Fichero*> i = ficherosMod.iteradorInicio();
	while (i.existe()) {
		if (i.getDato()->GetNombre() == nombre) {
			return true;
		}
		i++;
	}
	return false;
}

bool Commit::borrarFichero(string nombre) {
	Iterador<Fichero*> i = ficherosMod.iteradorInicio();
	while (i.existe()) {
		if (i.getDato()->GetNombre() == nombre) {
			ficherosMod.borrar(i);
			return true;
		}
		i++;
	}
	return false;
}
VDinamico<Fichero*> Commit::getFicheros() {

	VDinamico<Fichero*> vfich;
	Iterador<Fichero*> i = ficherosMod.iteradorInicio();
	int j = 0;
	while (i.existe()) {
		vfich.insertar(i.getDato(), j);
		j++;
		i++;
	}
	return vfich;
}

bool Commit::entreFechas(Fecha fdesde, Fecha fhasta) {

	return f >= fdesde && f <= fhasta;

}