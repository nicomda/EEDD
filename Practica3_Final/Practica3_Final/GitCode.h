#pragma once
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

class GitCode{
private:
	string fileFichero;
	string fileCommits;
	ListaDEnlazada<Commit> commits;
	ListaDEnlazada<Fichero> ficheros;
	void cargarFichero(string fileFiche);
	void cargarCommit(string fileComm);
public:
	GitCode();
	GitCode(string afileFichero, string afileCommits);
	GitCode(const GitCode& orig);
	~GitCode();
	bool getCommit(string code, Commit& commit);
	VDinamico<Commit> getCommitFechas(Fecha f1, Fecha f2);
	VDinamico<Commit> getCommitFichero(string nombre);
	void eliminarFichero(string nombre);

};

#endif

