#ifndef LISTADENLAZADA_H
#define LISTADENLAZADA_H


#include "NodoIterador.h"
#include "Excepciones.h"
#include <iostream>
#include <string>
using namespace std;
template <class T>
class ListaDEnlazada {
	private:
		Nodo<T> *cabecera;
		Nodo<T> *cola;
		
	public:
		ListaDEnlazada();
		ListaDEnlazada(const ListaDEnlazada<T>& orig);
		// ListaDEnlazada& operator=(ListaDEnlazada &l);
		~ListaDEnlazada();

		Iterador<T> iteradorInicio();
		Iterador<T> iteradorFinal();

		void insertarInicio(T& dato);
		void insertarFinal(T& dato);
		void insertar(Iterador<T>& i, T& dato);
		void borrarInicio();
		void borrarFinal();
		void borrar(Iterador<T>& i);
		T& inicio();
		T& final();
};

template <class T>
ListaDEnlazada<T>::ListaDEnlazada() {
	cabecera = cola = 0;
}

template <class T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada<T>& orig) {
	cabecera = orig.cabecera;
	cola = orig.cola;
}

/*Falta operator igual*/

template <class T>
ListaDEnlazada<T>::~ListaDEnlazada() {

}

template <class T>
Iterador<T> ListaDEnlazada<T>::iteradorInicio() {
	return Iterador<T>(cabecera);
}

template <class T>
Iterador<T> ListaDEnlazada<T>::iteradorFinal() {
	return Iterador<T>(cola);
}

template <class T>
void ListaDEnlazada<T>::insertarInicio(T& dato) {
	Nodo<T>* nodo = new Nodo<T>(dato, 0, 0);
	if (!cabecera) {
		cabecera = cola = nodo;
	} else {
		nodo->setSiguiente(cabecera);
		cabecera->setAnterior(nodo);
		cabecera = nodo;
	}
}
template <class T>
void ListaDEnlazada<T>::insertarFinal(T& dato) {
	Nodo<T>* nodo = new Nodo<T>(dato, 0, 0);
	if (!cola) {
		cabecera = cola = nodo;
	} else {
		nodo->setAnterior(cola);
		cola->setSiguiente(nodo);
		cola = nodo;
	}
}

template <class T>
void ListaDEnlazada<T>::insertar(Iterador<T>& i, T& dato) {
	//Hay que comprobar que el iterador este apuntando algun
	//elemento que sea correcto
	if (!i.existe())throw ERROR_FUERA_RANGO;
	if (i.getNodo() == cabecera) {
		insertarInicio(dato);
	} else {
		if (i.getNodo() == cola) {
			insertarFinal(dato);
		} else {
			Nodo<T> *nodo = new Nodo<T>(dato, i.getNodo()->getAnterior(), i.getNodo());
			Nodo<T> *anterior = i.anterior();
			i.getNodo()->setAnterior(nodo);
			anterior->setSiguiente(nodo);
		}
	}
}

template <class T>
void ListaDEnlazada<T>::borrarInicio() {
	if (!cabecera)throw ERROR_FUERA_RANGO();
	if (cabecera == cola) {
		delete cabecera;
		cabecera = cola = 0;
	} else {
		Nodo<T>* nodo = cabecera;
		cabecera = nodo->getSiguiente();
		delete nodo;
	}
}

template <class T>
void ListaDEnlazada<T>::borrarFinal() {
	if (!cabecera) throw ERROR_FUERA_RANGO();
	if (cabecera == cola) {
		delete cabecera;
		cabecera = cola = 0;
	} else {
		Nodo<T>* nodo = cola;
		cola = nodo->getAnterior();
		cola->setSiguiente(0);
		delete nodo;
	}
}

template<class T>
void ListaDEnlazada<T>::borrar(Iterador<T>& i)
{
	if (!i.existe())throw ERROR_FUERA_RANGO();
	if (i.getNodo() == cabecera) borrarInicio() {
	}
	else {
		if (i.getNodo() == cola) borrarFinal() {
		}
		else {
			i.getNodo()->getAnterior()->setSiguiente(i.getNodo()->getSiguiente());
			i.getNodo()->getSiguiente()->setAnterior(i.getNodo()->getAnterior());
			delete i.getNodo();
		}
	}
}


template <class T>
T& ListaDEnlazada<T>::inicio() {
	return cabecera->dato;
}

template <class T>
T& ListaDEnlazada<T>::final() {
	return cola->dato;
}
#endif /*LISTADENLAZADA_H*/
