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
public:
	//Creamos los constructores por defecto, parametros y copia.
	Nodo();
	Nodo(T& adato, Nodo<T>* ant, Nodo<T>* sig);
	Nodo(const Nodo<T>& orig);
	//Creamos los metodos gets y set 
	T& getDato() { return dato; }
	void setDato(T& mdato) { dato = mdato; }
	Nodo<T>* getAnterior() { return anterior; }
	Nodo<T>* getSiguiente() { return siguiente; }
	void setAnterior(Nodo<T>* ant) { anterior = ant; }
	void setSiguiente(Nodo<T>* sig) { siguiente = sig; }
	//Creamos el destructor.
	~Nodo() { anterior = siguiente = 0; }
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



#endif // !NODO_H


