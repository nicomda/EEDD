#ifndef GITCODE_H
#define GITCODE_H

#include "Excepciones.h"
#include <list>
#include "Fichero.h"
#include <string>
#include <fstream>
#include "fecha.h"
#include "Commit.h"
#include <map>


using namespace std;

class GitCode
{
public:
	GitCode();
	GitCode(string afileFichero, string afileCommits);
	GitCode(const GitCode& orig);
	~GitCode();
	bool getCommit(string code, Commit& commit); //cambiado
	vector<Commit*> getCommFechas(Fecha f1, Fecha f2);
	vector<Commit*> getCommFichero(string nombre);
	//void eliminarFichero(string nombre);
	//void nuevoCommit(Commit& c);
	//void borrarCommit(string cod);
	//string getStatus();
	void nuevoFichero(Fichero& fichero);
	vector<Fichero*> getFicherosActuales();
	int getNumFicherosActivos() { return fichActuales.size(); };
	void nuevoCommit(string codigo, string texto, string marcatiempo, vector<string> fich);
	void borrarFichero(string nombre);
	void borrarCommit(string codigo);
private:

	
	string fileFichero;
	string fileCommits;
	map<string, Fichero*> fichActuales;
	map<string, list<Commit>::iterator> mapCommit;

	list<Commit> commits;
	list<Fichero> ficheros;
	void cargaDeFichero(string fileFiche);
	void cargaDeCommit(string fileComm);
	
	Fichero* buscarFichero(string nombre);
	
};

#endif