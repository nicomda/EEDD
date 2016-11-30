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
#include "THashCerrada.h"

using namespace std;

class GitCode {
private:

	class RefCommit {
	public:
		string codCommit;
		list<Commit>::iterator itc;
		RefCommit() { codCommit = ""; }
		RefCommit(const string &cod) :codCommit(cod), itc() {}
		RefCommit(const string &cod, const list<Commit>::iterator &it) : codCommit(cod), itc(it) {}
		RefCommit(const RefCommit &orig) : codCommit(orig.codCommit), itc(orig.itc) {}
		string getCodCommit() { return codCommit; }
		void setCodCommit(string mcodCommit) { codCommit = mcodCommit; }
		/**Compara los iteradores por el código del Commit al que hacen referencia*/
		bool operator< (const RefCommit &rc) const { return codCommit < rc.codCommit; }
		//Otros operadores de comparación necesarios...
		bool operator== (const RefCommit &rc) const { return codCommit == rc.codCommit; }
		bool operator> (const RefCommit &rc) const { return codCommit > rc.codCommit; }
		bool operator!= (const RefCommit &rc) const { return codCommit != rc.codCommit; }
	};

	THashCerrada<RefCommit> commitsPorClave;
	string fileFichero;
	string fileCommits;
	//Creamos la lista de commits
	list<Commit> commits;
	//Creamos el vector de ficheros.
	list<Fichero> ficheros;
	//Funciones para cargar los Ficheros y los Commits.
	void cargarFichero(string mfileFichero);
	void cargarCommits(string mfileCommits);
	//Creamos la tabla hash para la asociacion con los ficheros
	THashCerrada<Fichero*> ficherosActivos;


public:
	//Creamos constructores de la clase:
	GitCode() :fileFichero(" "), fileCommits(" "), commits(), ficheros(), ficherosActivos(){}; //Por defecto
	GitCode(string mfileFichero, string mfileCommits); //Por parametros
	GitCode(const GitCode& orig); //Por copia
	//Creamos el destructor de la clase.
	~GitCode();

    Fichero* buscarFichero(string nombre);
	//creamos el metodo para saber si existe un commit.
	bool getCommit(string mcodigo, Commit& mcommit);
	//Creamos los vectores de commits
	list<Commit*> getCommitFechas(Fecha inicio, Fecha fin); //Para obtener commits entre dos fechas.
	list<Commit*> getCommitFichero(string mnombre); //Para obtener commits que contienen un fichero.

	//Creamos la funcion para anadir un nuevo commit
	void nuevoCommit(Commit mcommit);
	void borraCommit(string mcodigo);
	string getStatus();
	int getNumFicheros() { return ficherosActivos.getNumeroElementos(); }
	list<Fichero*> getFicherosActivos();
	void nuevoFichero(Fichero& mfichero);
	void borraFichero(string mnombre);
};
#endif // !GITCODE_H