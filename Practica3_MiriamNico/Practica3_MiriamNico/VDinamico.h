#ifndef VDINAMICO_H
#define VDINAMICO_H
#include "Excepciones.h"
#include <iostream>
#include <string>
using namespace std;

template <class T>
class VDinamico {
private:
	T* vector;
	unsigned tamF;
	unsigned tamL;
	void aumentoTam();    // las creamos privadas para cualquiera que utilize la clase no pueda 
	void disminuirTam();  // usarlas ni cambiar el vector.
	bool lleno();
	bool disminuir();

public:
	//creamos los constructores, por defecto, por parametros y copia
	VDinamico();
	VDinamico(unsigned tam, const T& mdato);
	VDinamico(const VDinamico<T>& orig);
	VDinamico(const VDinamico<T>& origen, unsigned inicio, unsigned num);
	//creamos el operador =
	VDinamico<T>& operator=(const VDinamico<T>& orig);
	//creamos el operador []
	T& operator[](const unsigned pos);
	//la funci�n insertar un dato
	void insertar(const T& mdato, unsigned pos = UINT_MAX);
	//la funci�n borrar un dato
	T borrar(unsigned pos = UINT_MAX);
	unsigned tam();
	~VDinamico();

};

template <class T>
//implementamos el constructor por defecto
VDinamico<T>::VDinamico() {
	tamF = 1; //vamos a incrementarlo en potencias de 2 por eso lo ponemos a 1
	tamL = 0;
	vector = new T[tamF]; // pasamos tamF para reservar la memoria con ese tama�o.
}

template <class T>
//implementamos el constructor por parametros
VDinamico<T>::VDinamico(unsigned tam, const T& mdato) {
	tamL = tam;
	//lo ponemos a dos o a 1 para que sean siempre potencias de dos.
	tamF = 2;
	while (tamF<tam) {
		tamF *= 2;
	}
	//craemos un nuevo vector
	vector = new T[tamF];
	//introducimos los datos
	for (int i = 0; i < tamL; i++) {
		vector[i] = mdato;
	}
}

template <class T>
//creamos el constructor copia
VDinamico<T>::VDinamico(const VDinamico<T>& orig) {
	tamF = orig.tamF;
	tamL = orig.tamL;
	vector = new T[tamF];
	for (int i = 0; i<tamL; i++) {
		vector[i] = orig.vector[i];
	}
}

template <class T>
//creamos un constructor copia del vector desde una posicion de inicio y un numero determinado.
VDinamico<T>::VDinamico(const VDinamico<T>& origen, unsigned inicio, unsigned num) {
	//comprobamos que el numero de la posicion de inicio y la suma del numero no sean mayores que el tama�o del vector.
	if (inicio + num>origen.tamL) throw ERROR_DATOS_INCORRECTOS();
	tamL = num;
	while (tamF<tamL) {
		//comprobamos que el tama�o fisico no sea menor que el tama�o logico y si es asi lo aumentamos en potencia de dos
		tamF *= 2;
		vector = new T[tamF];
		for (int i = 0; i < tamL; i++) {
			vector[i] = origen.vector[i];
		}
	}
}

template <class T>
//creamos el operador =
VDinamico<T>& VDinamico<T>::operator=(const VDinamico<T>& orig) {
	tamF = orig.tamF;
	tamL = orig.tamL;
	vector = new T[tamF];
	for (int i = 0; i < tamL; i++) {
		vector[i] = orig.vector[i];
	}
	return *this;
}

template <class T>
//creamso el operador [] para que nos devuelva el dato en la posicion que le pasamos por parametro.
T& VDinamico<T>::operator[](const unsigned pos) {
	if (pos>tamL) throw ERROR_FUERA_RANGO();
	return vector[pos];
}


template <class T>
//creamos una funcion para que nos aumente el tama�o del vector.
void VDinamico<T>::aumentoTam() {
	//nos creamos un vector auxiliar.
	T* aux = new T[tamF];
	//copiamos los datos del vector actual al auxiliar.
	for (int i = 0; i<tamL; i++) {
		aux[i] = vector[i];
	}
	//eliminamos el vector.
	delete[] vector;
	//aumentamos el tama�o
	tamF *= 2;
	//creamos el nuevo vector.
	vector = new T[tamF];
	//copiamos los datos del vector auxiliar al nuevo vector con mas tama�o
	for (int i = 0; i < tamL; i++) {
		vector[i] = aux[i];
	}
	//eliminamos el vector auxiliar.
	delete[] aux;
}

template <class T>
//creamos la funcion para disminuir el tama�o
void VDinamico<T>::disminuirTam() {
	//nos creamos un vector auxiliar.
	T* aux = new T[tamF];
	//pasamos los datos al vector auxiliar del vector actual
	for (int i = 0; i < tamL; i++) {
		aux[i] = vector[i];
	}
	//eliminamos el vector actual
	delete[] vector;
	//disminuimos el tama�o del vector.
	tamF /= 2;
	//creamos un vector nuevo
	vector = new T[tamF];
	//pasamos los datos al nuevo vector del vector auxiliar.
	for (int i = 0; i<tamL; i++) {
		vector[i] = aux[i];
	}
	//eliminamos el vector auxiliar.
	delete[] aux;
}

template <class T>
//creamos una funci�n que nos diga si el vector esta lleno.
bool VDinamico<T>::lleno() {
	//si el tama�o fisico es igual al tama�o logico nos devolvera true y el vector estara lleno
	return tamF == tamL;
}

template <class T>
//creamos una funci�n que nos diga si podemos disminuir el vector.
bool VDinamico<T>::disminuir() {
	//si el tama�o logico es igual a la tercera parte del tama�o fisico entonces podremos disminuir el vector y nos devolvera true.
	return tamL == tamF / 3;
}

template <class T>
//creamos la funcion para insertar datos en una posicion del vector
void VDinamico<T>::insertar(const T& mdato, unsigned pos = UINT_MAX) {
	//comprobamos que el vector no esta lleno y en caso de que lo este aumentamos el tama�o
	if (lleno()) aumentoTam();
	if (pos == UINT_MAX || pos == tamL) {
		//a�adimos los datos e incrementamos la posicion
		vector[tamL++] = mdato;
	}
	else {
		//si la posicion es mayor que el tama�o logico del vector lanzamos un error.
		if (pos > tamL)throw ERROR_FUERA_RANGO();

		for (int i = tamL; i >= pos; i--) {
			vector[pos] = vector[i - 1];
		}
		vector[pos] = mdato;
		tamL++;
	}
}

template <class T>
//creamos la funci�n para borrar un dato de una posicion
T VDinamico<T>::borrar(unsigned pos = UINT_MAX) {
	T mdato;
	if (pos == UINT_MAX || pos == tamL - 1) {
		mdato = vector[tamL--];
	}
	else {
		if (pos >= tamL) throw ERROR_FUERA_RANGO();
		mdato = vector[pos];
		for (int i = pos; i < tamL; i++) {
			vector[i] = vector[i + 1];
		}
		tamL--;
	}
	if (disminuir()) disminuirTam();
	return mdato;
}

template <class T>
//creamos una funcion que nos devuelva el tama�o logico del vector
unsigned VDinamico<T>::tam() {
	return tamL;
}

template <class T>
//implementamos el destructor.
VDinamico<T>::~VDinamico() {
	delete[] vector;
	tamL = tamF = 0;

}
#endif /* VDINAMICO_H */

