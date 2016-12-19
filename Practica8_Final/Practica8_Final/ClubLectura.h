#ifndef CLUBLECTURA_H
#define CLUBLECTURA_H
#include "Lector.h"
#include "Valoracion.h"
#include "Libro.h"
#include "Excepciones.h"
#include <fstream>
#include <map>
#include <functional>
#include <vector>
#include <list>
#include <iostream>
#include <string>
using namespace std;

class ClubLectura {
private:
	map<string, Lector> lectores2;
	map<int, Libro> libros;
	void cargarLibros(string archivoLibros);
	void cargarLectores(string archivoLectores);
public:
	ClubLectura() :lectores2(), libros() {}
	ClubLectura(const ClubLectura& orig):lectores2(orig.lectores2),libros(orig.libros){}
	~ClubLectura() { lectores2.clear(); libros.clear(); }
	void cargarDatos();
	Libro* libroMasLeido();
	vector<Libro*> librosAfines(Libro* libro);
	Lector* buscarLector(string malias);
	Libro* buscarLibro(int mid);
};
#endif // !CLUBLECTURA_H



