#ifndef NODO_H
#define NODO_H
#include <iostream>
#include <string>
using namespace std;
template <class T>
class Nodo {
private:
	T dato;
	Nodo<T>* izquierda;
	Nodo<T>* derecha;

public:
	//Creamos el constructor por defecto de la clase.
	Nodo() :dato(NULL) { izquierda = 0; derecha = 0; }
	//Creamos un constructor por parametros con el parametro dato.
	Nodo(T mdato) :dato(mdato) { izquierda = izquierda; derecha = derecha; }
	//Creamos un constructor por parametros con todos los parametros de la clase.
	Nodo(T mdato, Nodo<T>* mizquierda, Nodo<T>* mderecha) :dato(mdato) { izquierda = mizquierda; derecha = mderecha; }
	//Creamos el constructor copia de la clase.
	Nodo(const Nodo<T>& orig) :dato(orig.dato) { izquierda = orig.izquierda; derecha = orig.derecha; }
	//Creamos el destructor.
	~Nodo() { izquierda = derecha = 0; }

	//Creamos los metodos get de la clase.
	T getDato() { return dato; }
	Nodo<T>* getIzquierda() { return izquierda; }
	Nodo<T>* getDerecha() { return derecha; }

	//Creamos los metodos set de la clase.
	void setDato(T mdato) { dato = mdato; }
	void setIzquierda(Nodo<T>* mizquierda) { izquierda = mizquierda; }
	void setDerecha(Nodo<T>* mderecha) { derecha = mderecha; }

	//Creamos unos metodos para saber si el nodo ya existe o si existen a su derecha o a su izquierda.
	bool existe() { return nodo != NULL; }
	bool existeDerecha() { return nodo->getDerecha() != 0; }
	bool existeIzquierda() { return nodo->getIzquierda() != 0; }

};

#endif // !NODO_H
