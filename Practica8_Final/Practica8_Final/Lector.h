#ifndef LECTOR_H
#define LECTOR_H
#include "Valoracion.h"
#include "Excepciones.h"
#include "Libro.h"
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <vector>
using namespace std;

class Lector{
private:
	string alias;
	multimap<int, Valoracion, greater<int>> valoraciones;
public:
	Lector() :valoraciones() { alias = ""; }
	Lector(string malias) :valoraciones() { alias = malias; }
	Lector(const Lector& orig) :valoraciones(orig.valoraciones) { alias = orig.alias; }
	~Lector() { valoraciones.clear(); }
	string getAlias() { return alias; }
	void setAlias(string malias) { alias = malias; }
	vector<Libro*> librosLeidos();
	vector<Libro*> librosRecomendados();
	void nuevaValoracion(Libro* l, int puntuacion);
};
#endif // !LECTOR_H

