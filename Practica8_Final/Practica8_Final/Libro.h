#pragma once
#ifndef LIBRO_H
#define LIBRO_H
#include <string>
//#include "Lector.h"
#include <map>
#include <iostream>
#include <vector>
using namespace std;
class Lector;

class Libro {
private:
	int id;
	string autor;
	string titulo;
	string tematica;
	int sumaValoraciones;
	int numValoraciones;
	map<string, Lector*> lectores;
public:
	Libro();
	Libro(int mid, string mautor, string mtitulo, string mtematica);
	Libro(const Libro& orig);
	~Libro();
	int getId() { return id; }
	string getAutor() { return autor; }
	string getTitulo() { return titulo; }
	string getTematica() { return tematica; }
	int getSumaValoraciones() { return sumaValoraciones; }
	int getNumValoraciones() { return numValoraciones; }
	void setId(int mid) { id = mid; }
	void setAutor(string mautor) { autor = mautor; }
	void setTitulo(string mtitulo) { titulo = mtitulo; }
	void setTematica(string mtematica) { tematica = mtematica; }
	void setSumaValoraciones(int msumaValoraciones) { sumaValoraciones = msumaValoraciones; }
	void setNumValoraciones(int mnumValoraciones) { numValoraciones = mnumValoraciones; }
	float valoracionMedia();
	void nuevaValoracion(int puntuacion);
	void nuevoLector(Lector* lector);
	Lector* buscarLector(string alias);
	vector<Lector*> getLectores();
	void getInformacion() {
		cout << "Id: " << id << ", Autor: " << autor << ", Titulo: " << titulo << ", Tematica: " << tematica << "." << endl;
		cout << "Total valoraciones: " << sumaValoraciones << "." << endl;
		cout << "Valoracion media: " << valoracionMedia() << "." << endl;
		cout << "Numero de usuarios que lo han leido: " << numValoraciones << "." << endl;
		cout << "____________________________________________________________________________________________________________" << endl;
	}

};

#endif // !LIBRO_H


