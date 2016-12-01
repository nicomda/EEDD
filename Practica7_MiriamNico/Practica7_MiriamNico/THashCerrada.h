#ifndef THASHCERRADA_H
#define	THASHCERRADA_H
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

template <class T>
class THashCerrada {
private:
	class Casilla {
		T dato;
		char estado;
	public:
		Casilla() :dato(NULL) { estado = ' '; }
	};
	vector<Casilla> tabla;
	unsigned tamTabla;
	unsigned numeroElementos;
	unsigned maxColision;
public:
	THashCerrada() :tabla() { tamTabla = 0; numeroElementos = 0; maxColision = 0; }
	THashCerrada(unsigned mtam) : tabla(mtam) {
		tamTabla = mtam; numeroElementos = 0; maxColision = 0; Casilla c; vector<Casilla>::iterator itabla = tabla.begin();
		while (itabla != tabla.end()) {
			(*itabla) = c;
			itabla++;
		}
	}

	THashCerrada(vector<Casilla> mtabla) :tabla(mtabla) { tamTabla = 0; numeroElementos = 0; maxColision = 0; }
	unsigned getTamaTabla() { return tamTabla; }
	unsigned getNumeroElementos() { return numeroElementos; }
	unsigned getMaxColisiones() { return maxColision; }
	bool insertar(long mclave, const T& mdato);
	T* buscar(long mclave, const T& mdato);
	bool eliminar(long mclave, const T& mdato);
	float factorCarga();

};
#endif // !THASHCERRADA_H

template<class T>
inline bool THashCerrada<T>::insertar(long mclave, const T& mdato) {
	int i = 0;
	unsigned pos = mclave + pow(i, 2);
	bool libre = false;
	//podemos acceder a la posicion del vector directamente sin necesidad del iterador.
	while (!libre) {
		if (tabla[pos].estado == 'x') {
			i++;
			pos = mclave + (i * i);
		}
		else {
			libre = true;
		}
	}
	tabla[pos].dato = mdato;
	tabla[pos].estado = '1';
	numeroElementos++;
	if (i > maxColision) {
		maxColision = i;
	}

	return true;
}

template<class T>
inline T* THashCerrada<T>::buscar(long mclave, const T& mdato) {
	if (tabla == NULL) {
		return NULL;
	}
	int i = 0;
	unsigned pos = mclave + (i * i);
	bool encontrado = false;
	while (!encontrado) {
		if (tabla[pos].dato == mdato && tabla[pos].estado == '1') {
			encontrado = true;
		}
		else {
			if (tabla[pos].estado != '0') {
				i++;
				pos = mclave + (i*i);
			}
		}
	}
	if (encontrado) {
		return &(tabla[pos].dato);
	}
	else {
		return nullptr;
	}
}


template<class T>
inline bool THashCerrada<T>::eliminar(long mclave, const T& mdato) {
	if (tabla == NULL) {
		return NULL;
	}
	int i = 0;
	unsigned pos = mclave + (i * i);
	bool encontrado = false;
	while (!encontrado) {
		if (tabla[pos].dato == mdato && tabla[pos].estado == '1') {
			encontrado = true;
		}
		else {
			if (tabla[pos].estado != '0') {
				i++;
				pos = mclave + (i*i);
			}
		}
	}
	if (encontrado) {
		tabla[pos].estado = 'x';
		numeroElementos--;
		return true;
	}
	else {
		return false;
	}
}

template<class T>
inline float THashCerrada<T>::factorCarga(){
	return numeroElementos % tamTabla;
}

