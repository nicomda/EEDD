#ifndef NODO_H
#define NODO_H
#include <iostream>
#include <cstdio>
#include <string>
#include <exception>
using namespace std;

template <class T>
class Nodo {
private:
	//Creamos el dato tipo T
	T dato;
	//Creamos el nodo anterior
	Nodo<T>* anterior;
	//Creamos el nodo siguiente
	Nodo<T>* siguiente;
	//En la practica ponia el uso de la clase friend pero la hemos comentado porque da mil errores con los templates.
	//friend class Iterador;
	//friend class ListaDEnlazada;
public:
	//Creamos los constructores por defecto, parametros y copia.
	Nodo();
	Nodo(T& adato, Nodo<T>* ant, Nodo<T>* sig);
	Nodo(const Nodo<T>& orig);
	//Creamos los metodos gets y set 
	T& getDato();
	void setDato(T& mdato);
	Nodo<T>* getAnterior();
	Nodo<T>* getSiguiente();
	void setAnterior(Nodo<T>* ant);
	void setSiguiente(Nodo<T>* sig);
	//Creamos el destructor.
	~Nodo();

};

//Implementamos el constructor por defecto
template <class T>
Nodo<T>::Nodo() :dato() {
	anterior = siguiente = 0;
}

//Implementamos el constructor por parametros
template <class T>
Nodo<T>::Nodo(T& mdato, Nodo<T>* ant, Nodo<T>* sig) : dato(mdato) {
	anterior = ant;
	siguiente = sig;
}

//Implementamos el constructor copia
template <class T>
Nodo<T>::Nodo(const Nodo<T>& orig) : dato(orig.dato) {
	anterior = orig.anterior;
	siguiente = orig.siguiente;
}

//Implementamos el metodo getDato
template <class T>
T& Nodo<T>::getDato() {
	return dato;
}

//Implementamos el método setDato 
template <class T>
void Nodo<T>::setDato(T& mdato) {
	dato = mdato;
}

//Implementamos el metodo get anterior
template <class T>
Nodo<T>* Nodo<T>::getAnterior() {
	return anterior;
}

//Implementamos el metodo get siguiente
template <class T>
Nodo<T>* Nodo<T>::getSiguiente() {
	return siguiente;
}

//Implementamos el metodo set anterior.
template <class T>
void Nodo<T>::setAnterior(Nodo<T>* ant) {
	anterior = ant;
}

//Implementamos el metodo set siguiente
template <class T>
void Nodo<T>::setSiguiente(Nodo<T>* sig) {
	siguiente = sig;
}

//Implementamos el desctructor de la clase
template <class T>
Nodo<T>::~Nodo() {
	anterior = siguiente = 0;
}


#endif /*NODO_H*/
