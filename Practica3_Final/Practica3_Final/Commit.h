#pragma once
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
	VDinamico <Fichero *> ficheros;
	Fecha fecha;
	ListaDEnlazada<Fichero*> ficherosMod;

public:
	//creamos los constructores por defecto, parametros, copia y destructor de la clase.
	Commit();
	Commit(string mcodigo, string mmarcaDeTiempo, string mmensaje);
	Commit(string mcodigo, string mmarcaDeTiempo, string mmensaje, VDinamico <Fichero*> mficheros);
	Commit(const Commit& orig);
	virtual ~Commit();
	//creamos los gets y los sets de la clase.
	void SetCodigo(string codigo);
	string GetCodigo() const;
	void SetMarcaDeTiempo(string marcaDeTiempo);
	string GetMarcaDeTiempo() const;
	void SetMensaje(string mensaje);
	string GetMensaje() const;
	void SetFicheros(VDinamico<Fichero*> ficheros);
	Fichero* GetFichero(int pos);
	int tam_ficheros();
	//creamos metodos adicionales para trabajar con los ficheros.
	Fecha& getFecha() { return fecha; };
	VDinamico<Fichero*> getFicheros();
	void addFichero(Fichero* fich);
	bool incluyeFichero(string nombre);
	bool borrarFichero(string nombre);
	bool entreFechas(Fecha finicio, Fecha ffin);
};

#endif /* COMMIT_H */
