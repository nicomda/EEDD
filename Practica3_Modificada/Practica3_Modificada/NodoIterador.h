
#ifndef NODOITERADOR_H
#define NODOITERADOR_H

#include <iostream>
#include <string>
using namespace std;

template <class T>
class Nodo {
private:
	T dato;
	Nodo<T>* anterior;
	Nodo<T>* siguiente;
	friend class Iterador;
public:
	Nodo();
	Nodo(T &ndato, Nodo<T> *nanterior, Nodo<T> *nsiguiente);
	Nodo(const Nodo<T>& orig);
	T& getDato();
	void setDato(T& ndato);
	Nodo<T> *getAnterior();
	void setAnterior(Nodo<T> *nanterior);
	Nodo<T> *getSiguiente();
	void setSiguiente(Nodo<T> *nsiguiente);
	~Nodo();
};

template <class T>
Nodo<T>::Nodo() :dato() {
	anterior = siguiente = 0;
}

template <class T>
Nodo<T>::Nodo(T &ndato, Nodo<T> *nanterior, Nodo<T> *nsiguiente) : dato(ndato) {
	anterior = nanterior;
	siguiente = nsiguiente;
}

template <class T>
Nodo<T>::Nodo(const Nodo<T>& orig) :dato(orig.dato) {
	anterior = orig.anterior;
	siguiente = orig.siguiente;
}

template <class T>
T& Nodo<T>::getDato() {
	return dato;
}

template <class T>
void Nodo<T>::setDato(T &ndato) {
	dato = ndato;
}

template <class T>
Nodo<T> *Nodo<T>::getAnterior() {
	return anterior;
}

template <class T>
void Nodo<T>::setAnterior(Nodo<T> *nanterior) {
	anterior = nanterior;
}

template <class T>
Nodo<T> *Nodo<T>::getSiguiente() {
	return siguiente;
}

template <class T>
void Nodo<T>::setSiguiente(Nodo<T> *nsiguiente) {
	siguiente = nsiguiente;
}

template <class T>
Nodo<T>::~Nodo() {
	anterior = siguiente = 0;
}

template <class T>
class Iterador {
private:
	Nodo<T> *nodo;
	friend class ListaDEnlazada;
public:
	Iterador();
	Iterador(Nodo<T> *nnodo);
	Iterador(const Iterador<T> &orig);
	bool existe();
	bool hayAnterior();
	bool haySiguiente();
	Nodo<T> *ant();
	Nodo<T> *sig();
	void anterior() {
		nodo = nodo->anterior;
	}
	void siguiente() { 
		nodo = nodo->siguiente; }
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

template <class T>
Nodo<T>* Iterador<T>::ant() {
return nodo->getAnterior();
}

template <class T>
Nodo<T>* Iterador<T>::sig() {
return nodo->getSiguiente();
}

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
Nodo<T> *Iterador<T>::getNodo() {
	return nodo;
}
template <class T>
Iterador<T>::~Iterador() {

}
#endif /*NODOITERADOR_H*/