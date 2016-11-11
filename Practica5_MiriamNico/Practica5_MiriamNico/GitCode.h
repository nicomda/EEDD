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
#include "ABB.h"
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

	class RefCommit​ {
		public:
			string codCommit;
			list<Commit> itc​;
			RefCommit​(const std::string &cod, const list<Commit> &it = list<Commit>()) : codCommit(cod), itc(it) {};
			RefCommit​(const RefCommit​ &orig) : codCommit(orig.codCommit), itc(orig.itc) {};
			/**Compara los iteradores por el código del Commit al que hacen referencia*/
			bool operator<​(const RefCommit &rc) const {
				return codCommit < rc.codCommit;
			}
			//Otros operadores de comparación necesarios...
	};

public:
	//Creamos constructores de la clase:
	GitCode() :fileFichero(" "), fileCommits(" "), commits(), ficheros() {}; //Por defecto
	GitCode(string mfileFichero, string mfileCommits); //Por parametros
	GitCode(const GitCode& orig); //Por copia
	//Creamos el destructor de la clase.
	~GitCode();
	//creamos el metodo para saber si existe un commit.
	bool getCommit(string mcodigo, Commit& commit);
	//Creamos los vectores de commits
	vector<Commit*> getCommitFechas(Fecha inicio, Fecha fin); //Para obtener commits entre dos fechas.
	vector<Commit*> getCommitFichero(string mnombre); //Para obtener commits que contienen un fichero.
	//Creamos la funcion para eliminar ficheros contenidos en un Commit.
	void eliminarFichero(string mnombre);

	ABB<RefCommit​>​ commitsPorClave;
	list<Commit> commits;
};
#endif // !GITCODE_H