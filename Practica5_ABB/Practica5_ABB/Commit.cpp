#include "Commit.h"

Commit::Commit(string mcodigo, string mmarcaDeTiempo, string mmensaje) :ficherosMod(), f() {
	this->codigo = mcodigo;
	this->marcaDeTiempo = mmarcaDeTiempo;
	this->mensaje = mmensaje;
	this->f.pasarFFecha(mmarcaDeTiempo);
}

Commit::Commit(const Commit& orig) :ficherosMod(orig.ficherosMod), f(orig.f) {
	this->codigo = orig.codigo;
	this->marcaDeTiempo = orig.marcaDeTiempo;
	this->mensaje = orig.mensaje;
	this->f.pasarFFecha(orig.marcaDeTiempo);
}

Fecha Commit::pasarFFecha(string marcaTiempo) {
	short anio, mes, dia, hora, min, seg;
	anio = std::stoi(marcaTiempo.substr(0, 4));
	mes = std::stoi(marcaTiempo.substr(4, 2));
	dia = std::stoi(marcaTiempo.substr(6, 2));
	hora = std::stoi(marcaTiempo.substr(8, 2));
	min = std::stoi(marcaTiempo.substr(10, 2));
	seg = std::stoi(marcaTiempo.substr(12, 2));
	Fecha fecha(anio, mes, dia, hora, min, seg);
	return fecha;
}

bool Commit::entreDosFechas(Fecha inicio, Fecha fin) {
	return f >= inicio && f <= fin;
}

vector<Fichero*> Commit::getFicheros() {
	vector<Fichero*> vectorFicheros;
	list<Fichero*>::iterator i;
	i = ficherosMod.begin();
	string iterador;
	while (i != ficherosMod.end()) {
		vectorFicheros.push_back(*i);
		i++;
	}
	return vectorFicheros;
}

void Commit::addFichero(Fichero* fichero) {
	ficherosMod.push_back(fichero);
}

void Commit::eliminarFichero(string mnombre) {
	list<Fichero*>::iterator ificherosMod;
	ificherosMod = ficherosMod.begin();
	while (ificherosMod != ficherosMod.end()) {
		if ((*ificherosMod)->getNombre()==mnombre) {
			ficherosMod.erase(ificherosMod);
		}
		ificherosMod++;
	}
}

bool Commit::tieneFichero(string mnombre) {
	list<Fichero*>::iterator ificherosMod;
	ificherosMod = ficherosMod.begin();
	while (ificherosMod != ficherosMod.end()) {
		if ((*ificherosMod)->getNombre() == mnombre) {
			return true;
		}
		ificherosMod++;
	}
	return false;
}
