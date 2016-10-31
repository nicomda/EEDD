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
	//creamos las variables y el vector de punteros a la clase fichero.
	string codigo;
	string marcaDeTiempo;
	string mensaje;
	Fecha fecha;
	ListaDEnlazada<Fichero*> ficherosMod;

public:
	//creamos los constructores por defecto, parametros, copia y destructor de la clase.
	Commit();
	Commit(string mcodigo, string mmarcaDeTiempo, string mmensaje);
	Commit(const Commit& orig);
	virtual ~Commit();
	//creamos los gets y los sets de la clase.
	void SetCodigo(string mcodigo) { this->codigo = mcodigo; }
	string GetCodigo() const { return codigo; }
	void SetMarcaDeTiempo(string mmarcaDeTiempo) { this->marcaDeTiempo = mmarcaDeTiempo; }
	string GetMarcaDeTiempo() const { return marcaDeTiempo; }
	void SetMensaje(string mmensaje) { this->mensaje = mmensaje; }
	string GetMensaje() const { return mensaje; }

	//creamos metodos adicionales para trabajar con los ficheros.
	Fecha& getFecha() { return fecha; };
	void addFichero(Fichero* fich);
	bool incluyeFichero(string mnombre);
	bool borrarFichero(string mnombre);
	bool entreFechas(Fecha finicio, Fecha ffin);
	VDinamico<Fichero*> getFicheros();
};

#endif // !COMMIT_H 
