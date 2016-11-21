#ifndef GITCODE_H
#define GITCODE_H
#include <iostream>
#include <fstream>
#include <string>
#include "Commit.h"
#include "Fichero.h"
#include "Fecha.h"
#include "Excepciones.h"
#include <list>
#include <vector>
#include <map>
#include <set>

using namespace std;

class GitCode {
private:
	string fileFichero;
	string fileCommits;
	//Creamos la lista de commits
	list<Commit> commits;
	//Creamos el vector de ficheros.
	vector<Fichero> ficheros;
	//Funciones para cargar los Ficheros y los Commits.
	void cargarFichero(string mfileFichero);
	void cargarCommits(string mfileCommits);
	//Creamos una función para buscar ficheros.
	Fichero* buscarFichero(string nombre);
	//Creamos el map para la asociacion con los ficheros
	map<string, Fichero*> ficherosActivos;
	//Creamos el map para los Commits
	map<string, list<Commit>::iterator> mapCommits;

public:
	//Creamos constructores de la clase:
	GitCode() :fileFichero(" "), fileCommits(" "), commits(), ficheros(), ficherosActivos(), mapCommits() {}; //Por defecto
	GitCode(string mfileFichero, string mfileCommits); //Por parametros
	GitCode(const GitCode& orig); //Por copia
	//Creamos el destructor de la clase.
	~GitCode();
	//creamos el metodo para saber si existe un commit.
	bool getCommit(string mcodigo, Commit& mcommit);
	//Creamos los vectores de commits
	vector<Commit*> getCommitFechas(Fecha inicio, Fecha fin); //Para obtener commits entre dos fechas.
	vector<Commit*> getCommitFichero(string mnombre); //Para obtener commits que contienen un fichero.

	//Creamos la función para añadir un nuevo commit
	void nuevoCommit(string mcodigo, string mmarcadetiempo, string mmensaje, vector<string> mficheros);
	void borraCommit(string mcodigo);
	int getNumFicherosActivos() { return ficherosActivos.size(); }
	vector<Fichero*> getFicherosActivos();
	void nuevoFichero(Fichero& mfichero);
	void borraFichero(string mnombre);
};
#endif // !GITCODE_H