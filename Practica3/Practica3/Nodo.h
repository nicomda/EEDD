#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <string>
using namespace std;

template <class T>
class Nodo {
	private:
		T dato;
		Nodo<T> *anterior;
		Nodo<T> *siguiente;
		//friend class Iterador;
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
#endif /*NODO_H*/ !NODO_H

