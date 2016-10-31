#include "Commit.h"


Commit::Commit() :fecha(), ficherosMod() {
	codigo = " ";
	marcaDeTiempo = " ";
	mensaje = " ";

}

Commit::Commit(string mcodigo, string mmarcaDeTiempo, string mmensaje) :fecha(), ficherosMod() {
	this->codigo = mcodigo;
	this->marcaDeTiempo = mmarcaDeTiempo;
	this->mensaje = mmensaje;
	fecha.castingFecha(marcaDeTiempo);
}


Commit::Commit(const Commit& orig) :fecha(orig.fecha), ficherosMod(orig.ficherosMod) {
	this->codigo = orig.codigo;
	this->marcaDeTiempo = orig.marcaDeTiempo;
	this->mensaje = orig.mensaje;

}

Commit::~Commit() {
}

void Commit::addFichero(Fichero* fich) {
	ficherosMod.insertarFinal(fich);
}

bool Commit::incluyeFichero(string mnombre) {
	Iterador<Fichero*> i = ficherosMod.iteradorInicio();
	while (i.existe()) {
		if (i.getDato()->GetNombre() == mnombre) return true;
		i = i.siguiente();
	}
	return false;
}

bool Commit::borrarFichero(string mnombre) {
	Iterador<Fichero*> i = ficherosMod.iteradorInicio();
	while (i.existe()) {
		if (i.getDato()->GetNombre() == mnombre) {
			ficherosMod.borrar(i);
			return true;
		}
		i = i.siguiente();
	}
	return false;
}

bool Commit::entreFechas(Fecha finicio, Fecha ffin) {
	return fecha >= finicio && fecha <= ffin;
}

VDinamico<Fichero*> Commit::getFicheros() {

	VDinamico<Fichero*> vFicheros;
	Iterador<Fichero*> i = ficherosMod.iteradorInicio();
	int j = 0;
	while (i.existe()) {
		vFicheros.insertar(i.getDato(), j);
		j++;
		i = i.siguiente();
	}
	return vFicheros;
}