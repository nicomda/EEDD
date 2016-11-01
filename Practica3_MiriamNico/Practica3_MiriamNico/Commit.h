#ifndef COMMIT_H
#define COMMIT_H
#include "VDinamico.h"
#include "Fichero.h"
#include "Nodo.h"
#include "Iterador.h"
#include "ListaDEnlazada.h"
#include "Fecha.h"
#include "Excepciones.h"
#include <iostream>
#include <string>

using namespace std;

class Commit {

private:
	//creamos las variables.
	string codigo;
	string marcaDeTiempo;
	string mensaje;
	//Creamos una fecha
	Fecha fecha;
	//Creamos una lista de ficheros.
	ListaDEnlazada<Fichero*> ficherosMod;

public:
	//Creamos los constructores de la clase.
	Commit(); //Por defecto
	Commit(string mcodigo, string mmarcaDeTiempo, string mmensaje); //Por parametros
	Commit(const Commit& orig); //Por copia
	//Creamos el destructor de la clase.
	virtual ~Commit();
	//creamos los gets y los sets de la clase.
	void SetCodigo(string mcodigo) { this->codigo = mcodigo; }
	string GetCodigo() const { return codigo; }
	void SetMarcaDeTiempo(string mmarcaDeTiempo) { this->marcaDeTiempo = mmarcaDeTiempo; }
	string GetMarcaDeTiempo() const { return marcaDeTiempo; }
	void SetMensaje(string mmensaje) { this->mensaje = mmensaje; }
	string GetMensaje() const { return mensaje; }
	//Creamos un metodo para que nos devuelva la fecha.
	Fecha& getFecha() { return fecha; };
	//creamos metodos adicionales para trabajar con los ficheros.
	void addFichero(Fichero* fich);
	bool incluyeFichero(string mnombre);
	bool borrarFichero(string mnombre);
	//Creamos un metodo para decir si existen fechas entre dos fechas dadas.
	bool entreFechas(Fecha finicio, Fecha ffin);
	//Guardamos en el vector los ficheros.
	VDinamico<Fichero*> getFicheros();
};

#endif // !COMMIT_H 
