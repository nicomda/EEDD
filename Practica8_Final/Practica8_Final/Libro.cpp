#include "Libro.h"



Libro::Libro():lectores(){
	id = 0;
	autor = "";
	titulo = "";
	tematica = "";
	sumaValoraciones = 0;
	numValoraciones = 0;

}

Libro::Libro(int mid, string mautor, string mtitulo, string mtematica):lectores() {
	id = mid;
	autor = mautor;
	titulo = mtitulo;
	tematica = mtematica;
	sumaValoraciones = 0;
	numValoraciones = 0;
}

Libro::Libro(const Libro & orig):lectores(orig.lectores){
	id = orig.id;
	autor = orig.autor;
	titulo = orig.titulo;
	tematica = orig.tematica;
	sumaValoraciones = orig.sumaValoraciones;
	numValoraciones = orig.numValoraciones;

}


Libro::~Libro()
{
}

float Libro::valoracionMedia()
{
	return sumaValoraciones/numValoraciones;
}

void Libro::nuevaValoracion(int puntuacion) {
	sumaValoraciones += puntuacion;
	numValoraciones++;
}

void Libro::nuevoLector(Lector* lector){
	pair<string, Lector*> pairLectores;
	pairLectores.first = lector->getAlias();
	pairLectores.second = lector;
	lectores.insert(pairLectores);
}

Lector * Libro::buscarLector(string alias) {
	map<string, Lector*>::iterator iLectores;
	iLectores = lectores.find(alias);
	if (iLectores != lectores.end()) {
		return (*iLectores).second;
	} else return nullptr;
}

vector<Lector*> Libro::getLectores(){
	map<string, Lector*>::iterator iLectores = lectores.begin();
	vector<Lector*> vLectores;
	while (iLectores != lectores.end()) {
		vLectores.push_back((*iLectores).second);
	}
	return vLectores;
}
