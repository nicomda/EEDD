#ifndef VALORACION_H
#define VALORACION_H
#include "Libro.h"
#include <iostream>
#include <string>
using namespace std;
class Valoracion {
private:
	int puntuacion;
	Libro* libro;
public:
	Valoracion() { puntuacion = 0; libro = NULL; }
	Valoracion(int mpuntuacion, Libro* l) { puntuacion = mpuntuacion; libro = l; }
	Valoracion(const Valoracion& orig) { puntuacion = orig.puntuacion; libro = orig.libro; }
	~Valoracion(){}
	int getPuntuacion() { return puntuacion; }
	Libro* getLibro() { return libro; }
	void setPuntuacion(int mpuntuacion) { puntuacion = mpuntuacion;}
	void setLibro(Libro* l) { libro = l; }
};

#endif // !VALORACION_H

