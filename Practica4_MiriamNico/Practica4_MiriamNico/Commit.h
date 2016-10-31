#ifndef COMMIT_H
#define COMMIT_H
#include <iostream>
#include <fstream>
#include <string>
#include "Fichero.h"
#include "Fecha.h"
#include "Excepciones.h"
#include <list>
#include <vector>
using namespace std;
class Commit {
private:
	string codigo;
	string marcaDeTiempo;
	string mensaje;
	list<Fichero*> ficherosMod;
	Fecha f;
	Fecha pasarFFecha(string marcaTiempo);
public:
	Commit() :ficherosMod(), f() { codigo = marcaDeTiempo = mensaje = " "; };
	Commit(string mcodigo, string mmarcaDeTiempo, string mmensaje);
	Commit(const Commit& orig);
	~Commit() {};
	string getCodigo() { return codigo; };
	string getMarcaDeTiempo() { return marcaDeTiempo; };
	string getMensaje() { return mensaje; };
	Fecha& getFecha() { return f; };
	bool entreDosFechas(Fecha inicio, Fecha fin);

	void setCodigo(string mcodigo) { this->codigo = mcodigo; };
	void setMarcaDeTiempo(string mmarcaDeTiempo) { this->marcaDeTiempo = mmarcaDeTiempo; };
	void setMensaje(string mmensaje) { this->mensaje = mmensaje; };

	vector<Fichero*> getFicheros();
	void addFichero(Fichero *fichero);
	void eliminarFichero(string mnombre);
	bool tieneFichero(string mnombre);
};
#endif // !COMMIT_H

