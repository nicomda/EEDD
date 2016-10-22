#ifndef COMMIT_H
#define COMMIT_H

#include "Excepciones.h"
#include "VDinamico.h"
#include "ListaDEnlazada.h"
#include "Iterador.h"
#include "Fichero.h"
#include <string>
#include "fecha.h"

using namespace std;
class Commit {
public:
	//creamos los constructores por defecto, parametros, copia y destructor de la clase.
	Commit();
	Commit(string mcodigo, string mmarcaDeTiempo, string mmensaje, VDinamico <Fichero*> mficheros);
	Commit(const Commit& orig);
	virtual ~Commit();

	//creamos los gets y los sets de la clase.
	void SetCodigo(string codigo);
	string GetCodigo() const;
	void SetMarcaDeTiempo(string marcaDeTiempo);
	string GetMarcaDeTiempo() const;
	void SetMensaje(string mensaje);
	string GetMensaje() const;
	void SetFicheros(VDinamico<Fichero*> ficheros);
	//añadimos funciones para trabajar con los ficheros y las fechas 
	Fichero* GetFichero(int pos);
	int tam_ficheros();
	void addfichero(Fichero *fich);
	bool incluyeFichero(string nombre);
	bool borrarFichero(string nombre);
	VDinamico<Fichero*> getFicheros();
	bool entreFechas(Fecha fdesde, Fecha fhasta);
private:
	//creamos las variables y el vector de punteros a la clase fichero.
	string codigo;
	string marcaDeTiempo;
	string mensaje;
	VDinamico <Fichero*> ficheros;
	ListaDEnlazada<Fichero*> ficherosMod;
	Fecha f;
};

#endif /* COMMIT_H */
