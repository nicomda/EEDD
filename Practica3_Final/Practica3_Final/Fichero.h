#ifndef FICHERO_H
#define FICHERO_H
#include <string>
#include <iostream>
using namespace std;

class Fichero {

private:
	//creamos las variables del fichero.
	string nombre;
	string ubicacion;
	int tamaBytes;

public:
	//creamos los constructores por defecto, parametros y copia y el destructor.
	Fichero();
	Fichero(string nombre, string ubicacion, int tamaBytes);
	Fichero(const Fichero& orig);
	virtual ~Fichero();

	//creamos los sets y los gets
	void SetTamaBytes(int tamaBytes);
	int GetTamaBytes() const;
	void SetUbicacion(string ubicacion);
	string GetUbicacion() const;
	void SetNombre(string nombre);
	string GetNombre() const;

};

#endif /* FICHERO_H */

