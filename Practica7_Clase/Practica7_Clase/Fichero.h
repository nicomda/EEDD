#ifndef FICHERO_H
#define FICHERO_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Fichero {
private:
	string nombre;
	string ubicacion;
	int tamaBytes;

public:
	//Creamos los constructores de la clase 
	//Por defecto
	Fichero();
	//Por parametros
	Fichero(string mnombre, string mubicacion, int mtamaBytes);
	//Por copia
	Fichero(const Fichero& orig);
	//Destructor.
	~Fichero();

	//Creamos los metodos get.
	//Para el nombre
	string getNombre()const { return nombre; };
	//La ubicacion
	string getUbicacion()const { return ubicacion; };
	//Y el tamaño de bytes
	int getTamaBytes()const { return tamaBytes; };

	//Creamos los metodos set
	//Para el nombre
	void setNombre(string mnombre) { this->nombre = mnombre; };
	//La ubicacion
	void setUbicacion(string mubicacion) { this->ubicacion = mubicacion; };
	//Y el tamaño de bytes
	void setTamaBytes(int mtamaBytes) { this->tamaBytes = mtamaBytes; };

};

#endif // !FICHERO_H

