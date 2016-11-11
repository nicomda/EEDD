#ifndef ABB_H
#define ABB_H
#include "Nodo.h"
#include <iostream>
#include <string>
using namespace std;

template <class T>
class ABB {
private:
	Nodo<T>* raiz;
	unsigned numElementos;
public:
	ABB() { raiz = null; numElementos = 0; }
	ABB(Nodo<T>* mraiz, unsigned mnumElementos) { raiz = mraiz; numElementos = mnumElementos; }
	ABB(const ABB<T>& orig) { raiz = orig.raiz; numElementos = orig.numElementos; }
	~ABB(){}

	Nodo<T>* getRaiz() { return raiz; }
	unsigned getNumElementos() { return numElementos; }

	void setRaiz(Nodo<T>* mraiz) { this->raiz = mraiz; }
	void setNumElementos(unsigned mnumElementos) { this->numElementos = mnumElementos; }

	bool buscar(T& mdato, Nodo<T>* nodo);
	bool insertar(T& mdato);
	bool borrar(T& mdato);
	int altura(T& mdato);
	int numHojas();

};
template <class T>
bool ABB<T>::buscar(T& mdato, Nodo<T>* nodo) {
	bool encontrado = false;
	nodo = raiz;
	while (!encontrado && nodo != NULL) {
		if (nodo->getDato() == mdato) {
			encontrado = true;
		}
		else {
			if (mdato < nodo->getDato()) {
				nodo = nodo->getIzquierda();
			}
			else {
				nodo = nodo->getDerecha();
			}
		}
	}
	return encontrado;
}

template <class T>
bool ABB<T>::insertar(T& mdato) {
	Nodo<T>* nodo, iABB;
	bool encontrado = buscar(mdato, nodo);
	bool insertado = false;
	if (encontrado) {
		return false;
	}
	else {
		nodo = new Nodo<T>(mdato);
		iABB = raiz; //Ponemos el iterador en la raiz del arbol
		if (!raiz) {
			raiz = nodo; //para que apunte al nodo.
			numElementos++;
		}
		else {
			while (!insertado) {
				if (mdato < iABB->getDato()) {
					if (iABB->existeIzquierda()) {
						iABB = iABB->getIzquierda();
					}
					else {
						iABB->setIzquierda(nodo);
						insertado = true;
					}
				}
				else {
					if (iABB->existeDerecha()) {
						iABB = iABB->getDerecha();
					}
					else {
						iABB->setDerecha(nodo);
						insertado = true;
					}
				}
			}
			numElementos++;
			return true;
		}
	}
}

template <class T>
int ABB<T>::altura(T& mdato) {
	Nodo<T>* nodo, iABB;
	bool encontrado = buscar(mdato, nodo);
	int nivel = 0;
	if (encontrado) {
		bool profundidad = false;
		while (!profundidad) {
			nodo = raiz;
			if (nodo->getDato() == mdato) {
				profundidad = true;
			}
			else {
				if (mdato < nodo->getDato()) {
					nodo = nodo->getIzquierda();
					nivel++;
				}
				else {
					nodo = nodo->getDerecha();
					nivel++;
				}
			}
		}
		return nivel;
	}
	else {
		return -1;
	}
}
template <class T>
int ABB<T>::numHojas() {
	
}

template <class T>
bool ABB<T>::borrar(T& mdato) {

}
#endif // !ABB_H

