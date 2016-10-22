#ifndef ITERADOR_H
#define ITERADOR_H
#include "Nodo.h"
#include <iostream>
#include <string>
using namespace std;

template <class T>
class Iterador {
	private:
		Nodo<T> *nodo;
		//friend class ListaDEnlazada;
	public:
		Iterador();
		Iterador(Nodo<T> *nnodo);
		Iterador(const Iterador<T> &orig);
		bool existe();
		bool hayAnterior();
		bool haySiguiente();
		//Nodo<T> *anterior();
		//Nodo<T> *siguiente();
		void anterior() { nodo = nodo->ant; }
		void siguiente() { nodo = nodo->sig; }
		T &getDato();
		Nodo<T> *getNodo();
		//Iterador<T> &operator++();
		//Iterador<T> &operator--();
		bool operator==(Iterador<T> &i);
		bool operator!=(Iterador<T> &i);
		~Iterador();
};

template <class T>
Iterador<T>::Iterador() {
	nodo = 0;
}

template <class T>
Iterador<T>::Iterador(Nodo<T> *nnodo) {
	nodo = nnodo;
}

template <class T>
Iterador<T>::Iterador(const Iterador<T> &orig) {
	nodo = orig.nodo;
}

template <class T>
bool Iterador<T>::existe() {
	return nodo != 0;
}

template <class T>
bool Iterador<T>::hayAnterior() {
	return nodo->getAnterior() != 0;
}

template <class T>
bool Iterador<T>::haySiguiente() {
	return nodo->getSiguiente() != 0;
}

/*template <class T>
Nodo<T>* Iterador<T>::anterior() {
	return nodo->getAnterior();
}

template <class T>
Nodo<T>* Iterador<T>::siguiente() {
	return nodo->getSiguiente();
}
*/
template <class T>
T &Iterador<T>::getDato() {
	return nodo->getDato();
}
/*
template <class T>
Iterador<T> &Iterador<T>::operator++() {
	nodo = nodo->getSiguiente();
	return *this;
}

template <class T>
Iterador<T> &Iterador<T>::operator--() {
	nodo = nodo->getAnterior();
	return *this;
}
*/
template <class T>
bool Iterador<T>::operator==(Iterador<T> &i) {
	return nodo == i.nodo;
}

template <class T>
bool Iterador<T>::operator!=(Iterador<T> &i) {
	return nodo != i.nodo;
}

template <class T>
Nodo<T>* Iterador<T>::getNodo() {
	return nodo;
}
template <class T>
Iterador<T>::~Iterador() {

}
#endif /*ITERADOR_H*/