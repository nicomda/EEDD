#ifndef GITCODE_H
#define GITCODE_H

#include "Excepciones.h"
#include <list>
#include "Fichero.h"
#include <string>
#include <fstream>
#include "fecha.h"
#include "Commit.h"
#include "THashCerrada.h"
using namespace std;

const int TAM = 50000;

class GitCode
{
public:
	GitCode();
	GitCode(string afileFichero, string afileCommits);
	GitCode(const GitCode& orig);
	~GitCode();
	bool getCommit(string code, Commit& commit);
	vector<Commit*> getCommFechas(Fecha f1, Fecha f2);
	vector<Commit*> getCommFichero(string nombre);
	void eliminarFichero(string nombre);
	void nuevoCommit(Commit& c);
	void borrarCommit(string code);
	void nuevoFichero(Fichero f);

private:

	class RefCommit{
	public:

		string codigo;
		list<Commit>::iterator itc;
		RefCommit():itc() {
			codigo = "";
		}
		RefCommit(string acodigo, list<Commit>::iterator atc) : codigo(acodigo), itc(atc)
		{}
		bool operator<(const RefCommit &rc){
			return (codigo< rc.codigo);

		}
		bool operator== (const RefCommit &rc){
			return (codigo == rc.codigo);
		}

	};
	string fileFichero;
	string fileCommits;
	list<Commit> commits;
	vector<Fichero> ficheros;
	THashCerrada<RefCommit> hashCommit;
	void cargaDeFichero(string fileFiche);
	void cargaDeCommit(string fileComm);
	unsigned long djb2(string str);
};

#endif