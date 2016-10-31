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
using namespace std;

class GitCode {
private:
	string fileFichero;
	string fileCommits;
	list<Commit> commits;
	vector<Fichero> ficheros;
	void cargarFichero(string mfileFichero);
	void cargarCommits(string mfileCommits);
public:
	GitCode() :fileFichero(" "), fileCommits(" "), commits(), ficheros() {};
	GitCode(string mfileFichero, string mfileCommits);
	GitCode(const GitCode& orig);
	~GitCode();
	bool getCommit(string mcodigo, Commit& commit);
	vector<Commit*> getCommitFechas(Fecha inicio, Fecha fin);
	vector<Commit*> getCommitFichero(string mnombre);
	void eliminarFichero(string mnombre);
};
#endif // !GITCODE_H