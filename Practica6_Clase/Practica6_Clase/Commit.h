#ifndef COMMIT_H
#define COMMIT_H

#include "Excepciones.h"
#include <list>
#include "Fichero.h"
#include <string>
#include "fecha.h"
#include <iterator>
#include <vector>


using namespace std;

class Commit
{
public:
	Commit();
	Commit(string codigo, string marcaTiempo, string mensaje);
	Commit(const Commit& orig);
	void setCodigo(string codigo){ this->codigo = codigo; };
	void setMarcaDeTiempo(string marcaTiempo){ this->marcaDeTiempo = marcaTiempo; };
	void setMensaje(string mensaje){ this->mensaje = mensaje; };
	string getCodigo(){ return codigo; };
	string getMarcaDeTiempo(){ return marcaDeTiempo; };
	string getMensaje(){ return mensaje; };
	Fecha& getFecha() { return fecha; };
	void addfichero(Fichero* f);
	void borrarFichero(string nombre);
	bool entreFechas(Fecha fdesde, Fecha fhasta);
	bool incluyeFichero(string nombre);
	string getCadenaFecha() { return fecha.getFecha(); }
	~Commit();
	
	
private:
	string codigo;
	string marcaDeTiempo;
	string mensaje;
	Fecha fecha;
	list <Fichero*> fichModificados;

	

	

};

#endif