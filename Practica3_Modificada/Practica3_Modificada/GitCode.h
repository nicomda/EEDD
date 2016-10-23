#pragma once
#ifndef GITCODE_H
#define GITCODE_H
#include "Excepciones.h"
#include "Commit.h"
#include "Fichero.h"
#include "Fecha.h"
#include "NodoIterador.h"
#include "ListaDEnlazada.h"
#include "VDinamico.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class GitCode {
	private:
		string fileFichero;
		string fileCommits;
		ListaDEnlazada<Commit> commits;
		ListaDEnlazada<Fichero> ficheros;
		void cargaDeFichero(string fileFiche);
		void cargaDeCommit(string fileCommi);
	public:
		GitCode();
		GitCode(string ffileFichero, string cfileCommits);
		GitCode(const GitCode &orig);
		bool getCommit(string code, Commit &commit);
		VDinamico<Commit> getCommFechas(Fecha f1, Fecha f2);
		VDinamico<Commit> getCommFichero(string nombre);
		void eliminarFichero(string nombre);
		~GitCode();
};
#endif // !GITCODE_H


