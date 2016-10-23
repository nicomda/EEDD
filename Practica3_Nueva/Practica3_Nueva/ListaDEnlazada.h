#ifndef LISTADENLAZADA_H
#define LISTADENLAZADA_H

#include "Iterador.h"
#include "Nodo.h"
#include "Excepciones.h"

template<class T>
class ListaDEnlazada {
private:
	Nodo<T>* cabecera;
	Nodo<T>* cola;
public:
	//Creamos los constructores por defecto, por parametros y por copia, y el destructor de la clase.
	ListaDEnlazada() : cabecera(0), cola(0) {}
	ListaDEnlazada(Nodo<T>* cabe, Nodo<T>* col) :cabecera(cabe), cola(col) {}
	ListaDEnlazada(const ListaDEnlazada &orig) : cabecera(orig.cabecera), cola(orig.cola) {};
	~ListaDEnlazada();
	//Creamos el operador = de la clase.
	ListaDEnlazada &operator=(ListaDEnlazada &lista) : cabecera(orig.cabecera), cola(orig.cola) {};
	//Creamos los metodos para obtener los iteradores de Inicio y Final.
	Iterador<T> iteradorInicio() { return Iterador<T>(cabecera); }
	Iterador<T> iteradorFinal() { return Iterador<T>(cola); }
	//Creamos los metodos de insertar un dato al inicio y al final, y en una posicion dada.
	void insertarInicio(T& mdato);
	void insertarFinal(T& mdato);
	void insertar(Iterador<T>& i, T& mdato);
	//creamos los metodos de borrar los datos al inicio y al final, y en una posición dada.
	void borrarInicio();
	void borrarFinal();
	void borrar(Iterador<T> &i);
	//creamos los metodos para obtener los datos de inicio y final.
	T &inicio() { return cabecera->dato; }
	T &final() { return cola->dato; }

};

template<class T>
ListaDEnlazada<T>::~ListaDEnlazada() {
	cabecera = cola = 0;
}

template<class T>
void ListaDEnlazada<T>::insertarInicio(T& mdato) {
	Nodo<T>* nodo = new Nodo<T>(mdato, 0, 0);
	//si no hay ningun elememto, la lista esta vacia
	if (!cabecera) { 
		cabecera = cola = nodo;
	} else {
		nodo->setSiguiente(cabecera);
		cabecera->setAnterior(nodo);
		cabecera = nodo;
	}
}

template<class T>
void ListaDEnlazada<T>::insertarFinal(T& mdato) {
	Nodo<T>* nodo = new Nodo<T>(mdato, 0, 0);
	//si no hay ningun elememto, la lista esta vacia
	if (!cola) { 
		cabecera = cola = nodo;
	} else {
		nodo->setAnterior(cola);
		cola->setSiguiente(nodo);
		cola = nodo;
	}
}

template<class T>
void ListaDEnlazada<T>::insertar(Iterador<T>& i, T dato) {
	//Comprobamos que el iterador este apuntando a algun elemento
	if (!i.existe())throw ERROR_FUERA_RANGO();

	//Si el iterador apunta al mismo nodo que la cabecera, usamos el metodo insertarInicio().
	if (i.getNodo() == cabecera) {
		insertarInicio(dato);
	}
	else {
		//Si el iterador apunta al mismo nodo que la cola, usamos el metodo insertarFinal()
		if (i.getNodo() == cola) insertarFinal(dato);
		else {
			//Si el iterador apunta a una posición entre la cabecera y la cola, debemos insertarlo en la posición .
			Nodo<T>* nodo = new Nodo<T>(dato, i.getNodo()->getAnterior(), i.getNodo());
			Nodo<T>* anterior = i.anterior();
			i.getNodo()->setAnterior(nodo);
			anterior->setSiguiente(nodo);
		}
	}
}

template<class T>
void ListaDEnlazada<T>::borrarInicio() {
	//Si existen elementos entramos si no lanzamos la excepción.
	if (!cabecera) throw ERROR_FUERA_RANGO();
	//Si solo hay un elemento en la lista, la cola y la cabecera serán iguales, al borrarlas las dos quedarán a 0
	if (cabecera == cola) { 
		delete cabecera;
		cabecera = cola = 0;
	} else { 
		//Si hay mas de un elemento en la lista, la cola y la cabecera seran distintas, entonces borraremos al inicio la cabecera
		//y pasaremos al siguiente nodo y se eliminara el que apunte a la cabecera en ese momento.
		Nodo<T>* nodo = cabecera;
		cabecera = nodo->getSiguiente();
		cabecera->setAnterior(0);
		delete nodo;
	}
}

template<class T>
void ListaDEnlazada<T>::borrarFinal() {
	//Si existen elementos entramos si no lanzamos la excepción.
	if (!cabecera) throw ERROR_FUERA_RANGO();
	//Si solo hay un elemento en la lista, la cola y la cabecera serán iguales, al borrarlas las dos quedarán a 0
	if (cabecera == cola) { 
		delete cabecera;
		cabecera = cola = 0;
	} else { 
		//Si hay mas de un elemento en la lista, la cola y la cabecera seran distintas, entonces borraremos al inicio la cola
		//y pasaremos al siguiente nodo y se eliminara el que apunte a la cola en ese momento.
		Nodo<T>* nodo = cola;
		cola = nodo->getAnterior();
		cola->setSiguiente(0);
		delete nodo;
	}
}

template<class T>
void ListaDEnlazada<T>::borrar(Iterador<T>& i) {
	//Comprobamos que el iterador exista y si no existe lanzamos la excepción.
	if (!i.existe()) throw ERROR_FUERA_RANGO();
	//Si el iterador es igual a la cabecera usamos la función borrarInicio()
	if (i.getNodo() == cabecera) borrarInicio();
	else {
		//Si el iterador es igual a la cola usamos la función borrarFinal()
		if (i.getNodo() == cola) borrarFinal();
		else {
			//Si el iterador apunta algun elemento intermedio, tendremos que apuntar el nodo anterior al siguiente y el 
			//nodo siguiente al anterior y borrar el nodo al que se apunta.
			i.getNodo()->getAnterior()->setSiguiente(i.getNodo()->getSiguiente());
			i.getNodo()->getSiguiente()->setAnterior(i.getNodo()->getAnterior());
			delete i.getNodo();
		}
	}
}

#endif
