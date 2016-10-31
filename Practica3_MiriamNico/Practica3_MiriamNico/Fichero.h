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
	Fichero(string mnombre, string mubicacion, int mtamaBytes);
	Fichero(const Fichero& orig);
	virtual ~Fichero();

	//creamos metodos los sets
	void SetTamaBytes(int mtamaBytes) { this->tamaBytes = mtamaBytes; };
	void SetUbicacion(string mubicacion) { this->ubicacion = mubicacion; };
	void SetNombre(string mnombre) { this->nombre = mnombre; };

	//creamos metodos los gets
	int GetTamaBytes() const { return tamaBytes; };
	string GetUbicacion() const { return ubicacion; };
	string GetNombre() const { return nombre; };

};

#endif // !FICHERO_H
