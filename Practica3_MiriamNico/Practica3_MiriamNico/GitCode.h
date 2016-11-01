#ifndef GITCODE_H
#define GITCODE_H

#include "Excepciones.h"
#include "VDinamico.h"
#include "ListaDEnlazada.h"
#include "Iterador.h"
#include "Fichero.h"
#include "Fecha.h"
#include "Commit.h"
#include "Nodo.h"
#include <string>
#include <fstream>

using namespace std;

class GitCode {
private:
	string fileFichero;
	string fileCommits;
	//Creamos las listas enlazadas para commits y ficheros.
	ListaDEnlazada<Commit> commits;
	ListaDEnlazada<Fichero> ficheros;
	//Creamos las funciones para cargar los archivos de commits.txt y ficheros2.txt
	void cargarFichero(string fileFiche);
	void cargarCommit(string fileComm);
public:
	//Creamos los constructores de la clase:
	GitCode(); //Por defecto
	GitCode(string afileFichero, string afileCommits); //Por parametros
	GitCode(const GitCode& orig); //Por copia.
	//Creamos el destructor de la clase.
	~GitCode();
	//Creamos el metodo getCommit para saber si al pasarle un codigo de commit este existe o no
	bool getCommit(string code, Commit& commit);
	//Creamos los vectores dinamicos de tipo commit
	VDinamico<Commit*> getCommitFechas(Fecha f1, Fecha f2); //Para guardar commits entre un rango de fechas.
	VDinamico<Commit*> getCommitFichero(string nombre); //Para guardar commits si contienen un fichero.
	//Eliminar un fichero de los commits en los que haga referencia.
	void eliminarFichero(string nombre);

};

#endif // !GITCODE_H


