#ifndef ITERADOR_H
#define ITERADOR_H
#include "Nodo.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <exception>
using namespace std;

template <class T>
class Iterador {
private:
	//Creamos un nodo.
	Nodo<T>* nodo;
	//En la practica ponia el uso de la clase friend pero la hemos comentado porque da mil errores con los templates.
	//friend class ListaDEnlazada;	

public:

	//Creamos los metodos constructores de la clase Iterador por defecto, por parametros y por copia
	Iterador();
	Iterador(const Iterador<T>& orig);
	Iterador(Nodo<T> *mNodo) : nodo(mNodo) {}
	//Creamos los metodos para saber si hay un nodo anterior o siguiente
	bool hayAnterior() { return nodo != 0; }
	bool haySiguiente() { return nodo != 0; }
	//Creamos los metodos para pasar de un nodo a otro uno para el anterior y otro para el siguiente.
	Nodo<T>* anterior() { return nodo->getAnterior(); }
	Nodo<T>* siguiente() { return = nodo->getSiguiente(); }
	//Creamos el metodo para obtener el dato del nodo.
	T &dato() { return nodo->dato; }
	//Creamos el metodo para obtener el dato;
	T &getDato() { return nodo->getDato(); };
	//Creamos el metodo para obtener el nodo.
	Nodo<T>* getNodo();
	//Creamos un metodo para saber si un nodo existe o no.
	bool existe();
	//Creamos el destructor de la clase Iterador.
	~Iterador();
	//Creamos los operadores == y !=
	bool operator==(Iterador<T>& i);
	bool operator!=(Iterador<T>& i);

	//Nodo<T>* anterior();
	//Nodo<T>* siguiente();
};

//Implementamos el constructor por defecto de la clase Iterador.
template <class T>
Iterador<T>::Iterador() {
	nodo = 0;
}

//Implementamos el constructor copia de la clase Iterador.
template <class T>
Iterador<T>::Iterador(const Iterador<T>& orig) {
	nodo = orig.nodo;
}

//Implementamos el metodo get Nodo 
template <class T>
Nodo<T>* Iterador<T>::getNodo() {
	return nodo;
}

//Implementamos el metodo de si existe un nodo o no.
template <class T>
bool Iterador<T>::existe() {
	return nodo != 0;
}

//Implementamos el destructor de la clase Iterador.
template <class T>
Iterador<T>::~Iterador() {
	nodo = 0;
}

//Implementamos el operador ==
template <class T>
bool Iterador<T>::operator==(Iterador<T>& i) {
	return nodo == i.nodo;
}

//Implementamos el operador !=
template <class T>
bool Iterador<T>::operator!=(Iterador<T>& i) {
	return nodo != i.nodo;
}

/*
template <class T>
Nodo<T>* Iterador<T>::anterior() {
return nodo->getAnt();
}
template <class T>
Nodo<T>* Iterador<T>::siguiente() {
return nodo->getSig();
}

*/
#endif /*ITERADOR_H*/



