#ifndef THASHCERRADA_H
#define	THASHCERRADA_H
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
template<class T>
class Casilla {
public:
	T dato;
	char estado;
	Casilla() :dato() { estado = '0'; }
};

template <class T>
class THashCerrada {
private:
	
	vector<Casilla<T>> tabla;
	unsigned tamTabla;
	unsigned numeroElementos;
	unsigned maxColision;
public:
	THashCerrada() :tabla() { tamTabla = 0; numeroElementos = 0; maxColision = 0; }
	THashCerrada(unsigned mtam) : tabla(mtam) {
		tamTabla = mtam; numeroElementos = 0; maxColision = 0; Casilla<T> c; vector<Casilla<T>>::iterator itabla = tabla.begin();
		while (itabla != tabla.end()) {
			(*itabla) = c;
			itabla++;
		}
	}
	THashCerrada(const THashCerrada& orig);

	//THashCerrada(vector<Casilla> mtabla) :tabla(mtabla) { tamTabla = 0; numeroElementos = 0; maxColision = 0; }
	unsigned getTamaTabla() { return tamTabla; }
	unsigned getNumeroElementos() { return numeroElementos; }
	unsigned getMaxColisiones() { return maxColision; }
	bool insertar(long mclave, const T& mdato);
	T* buscar(long mclave, const T& mdato);
	bool eliminar(long mclave, const T& mdato);
	float factorCarga();

};


template<class T>
THashCerrada<T>::THashCerrada(const THashCerrada & orig) :tabla(orig.tabla){
	tamTabla = orig.tamTabla;
	numeroElementos = orig.numeroElementos;
	maxColision = orig.maxColision;
}

template<class T>
bool THashCerrada<T>::insertar(long mclave, const T& mdato) {
	unsigned colisiones = 0;
	unsigned posicionT = 0;
	unsigned salto = 0;
	if (tamTabla == numeroElementos) return false;
	unsigned pos =( mclave + (salto*salto)) % tamTabla;
	//podemos acceder a la posicion del vector directamente sin necesidad del iterador.
	while (tabla[posicionT].estado == '1') {
		if (tabla[posicionT].dato == mdato) throw ERROR_CLAVE_REPETIDA();
		colisiones++;
		salto++;
		posicionT = (mclave + (salto * salto)) % tamTabla;
	}
	if (colisiones > maxColision) {
		maxColision = colisiones;
	}

	Casilla<T> casilla;
	posicionT = pos;
	casilla.dato = mdato;
	casilla.estado = '1';
	tabla[posicionT] = casilla;
	numeroElementos++;
	return true;
}

template<class T>
T* THashCerrada<T>::buscar(long mclave, const T& mdato) {
	if (numeroElementos == 0) {
		return NULL;
	}
	int i = 0;
	unsigned pos = (mclave + (i * i)) % tamTabla;
	bool encontrado = false;
	while (!encontrado) {
		if (tabla[pos].dato == mdato && tabla[pos].estado == '1') {
			encontrado = true;
		}
		else {
			if (tabla[pos].estado != '0') {
				i++;
				pos =( mclave + (i*i))%tamTabla;
			}
			else {
				return nullptr;
			}
		}
	}
	return &(tabla[pos].dato);
	

}


template<class T>
inline bool THashCerrada<T>::eliminar(long mclave, const T& mdato) {
	if (numeroElementos == 0) {
		return NULL;
	}
	int i = 0;
	unsigned pos = (mclave + (i * i))%tamTabla;
	bool encontrado = false;
	while (!encontrado) {
		if (tabla[pos].dato == mdato && tabla[pos].estado == '1') {
			encontrado = true;
		}
		else {
			if (tabla[pos].estado != '0') {
				i++;
				pos =( mclave + (i*i))%tamTabla;
			}
			else {
				return false;
			}
		}
	}
	tabla[pos].estado = 'x';
	numeroElementos--;
	return true;
}

template<class T>
inline float THashCerrada<T>::factorCarga(){
	return numeroElementos / tamTabla;
}

#endif // !THASHCERRADA_H