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
	long indicesFicherosModificados;
	//Creamos la lista de Ficheros.
	list<Fichero*> ficherosMod;
	//Creamos una fecha
	Fecha f;
	//Creamos el casting para pasar a fecha formato string.
	// pasarFFecha(string marcaTiempo);
public:
	//Creamos constructores de la clase:
	Commit() :ficherosMod(), f() { codigo = marcaDeTiempo = mensaje = " "; indicesFicherosModificados = 0; }; //Por defecto
	Commit(string mcodigo) :ficherosMod(), f() { codigo = mcodigo; marcaDeTiempo = mensaje = " "; indicesFicherosModificados = 0; }
	Commit(string mcodigo, string mmarcaDeTiempo, string mmensaje, long mindicesFicherosModificados); //Por parametros
	Commit(const Commit& orig); //Por copia
	//Creamos el destructor de la clase.
	~Commit() {};
	//Creamos metodos get de la clase.
	string getCodigo() { return codigo; };
	string getMarcaDeTiempo() { return marcaDeTiempo; };
	string getMensaje() { return mensaje; };
	long getIndicesFicherosModificados() { return indicesFicherosModificados; }
	Fecha& getFecha() { return f; };
	//Creamos una función que nos devuelva true o false si entre dos fechas se encuentra alguna fecha.
	bool entreDosFechas(Fecha inicio, Fecha fin);
	//Creamos los metodos set de la clase.
	void setCodigo(string mcodigo) { this->codigo = mcodigo; };
	void setMarcaDeTiempo(string mmarcaDeTiempo) { this->marcaDeTiempo = mmarcaDeTiempo; };
	void setMensaje(string mmensaje) { this->mensaje = mmensaje; };
	void setInidicesFicherosModificados(long mindicesFicherosModificados) { this->indicesFicherosModificados = mindicesFicherosModificados; }
	//Creamos un vector de ficheros para obtener los ficheros.
	vector<Fichero*> getFicheros();
	//Creamos el metodo añadir y eliminar Fciheros.
	void addFichero(Fichero *fichero);
	void eliminarFichero(string mnombre);
	//Pasandole el nombre de un fichero comprobamos si este commit tiene dicho fichero.
	bool tieneFichero(string mnombre);
};
#endif // !COMMIT_H

