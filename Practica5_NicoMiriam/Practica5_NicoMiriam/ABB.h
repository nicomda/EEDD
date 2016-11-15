
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
	bool eliminar1(Nodo<T>* mnodo);
	bool eliminar2(Nodo<T>* mnodo);
	bool eliminar3(Nodo<T>* mnodo);
	Nodo<T>* recorrerIzquierda(Nodo<T>* mnodo);
public:
	ABB() { raiz = NULL; numElementos = 0; }
	ABB(Nodo<T>* mraiz, unsigned mnumElementos) { raiz = mraiz; numElementos = mnumElementos; }
	ABB(const ABB<T>& orig) { raiz = orig.raiz; numElementos = orig.numElementos; }
	~ABB() {}

	Nodo<T>* getRaiz() { return raiz; }
	unsigned getNumElementos() { return numElementos; }

	void setRaiz(Nodo<T>* mraiz) { this->raiz = mraiz; }
	void setNumElementos(unsigned mnumElementos) { this->numElementos = mnumElementos; }

	bool buscar(T& mdato);
	bool insertar(T& mdato);
	int altura(T& mdato);
	int alturaTotal(Nodo<T>* mnodo);
	int numHojas(Nodo<T>* mnodo);
	bool eliminar(Nodo<T>* mnodo);
};
template<class T>
bool ABB<T>::buscar(T& mdato) {
	Nodo<T>* mnodo;
	bool encontrado = false;
	mnodo = raiz;
	while (!encontrado && mnodo != NULL) {
		if (mnodo->getDato() == mdato) {
			encontrado = true;
		}
		else {
			if (mdato < mnodo->getDato()) {
				mnodo = mnodo->getIzquierda();
			}
			else {
				mnodo = mnodo->getDerecha();
			}
		}
	}
	throw ERROR_DATOS_INCORRECTOS();
	return encontrado;
}

template<class T>
bool ABB<T>::insertar(T& mdato) {
	Nodo<T>* nodo = 0;
	Nodo<T>* iABB;
	bool encontrado = buscar(mdato);
	bool insertado = false;
	if (encontrado) {
		return false;
	}
	else {
		iABB = raiz; //Ponemos el iterador en la raiz del arbol
		if (!raiz) {
			raiz = nodo; //para que apunte al nodo.
			numElementos++;
		}
		else {
			while (!insertado) {
				nodo = new Nodo<T>(mdato);
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
	Nodo<T>* nodo;
	Nodo<T>* iABB;
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
int ABB<T>::alturaTotal(Nodo<T>* mnodo) {
	int AltIzquierda, AltDerecha;
	if (!mnodo) {
		return -1;
	}
	else {
		AltIzquierda = alturaTotal(mnodo->getIzquierda());
		AllDerecha = alturaTotal(mnodo->getDerecha());
		if (AltIzquierda > AltDerecha) {
			return AltIzquierda + 1;
		}
		else {
			return AltDerecha + 1;
		}
	}
}

template <class T>
int ABB<T>::numHojas(Nodo<T>* mnodo) {
	if (!mnodo)return 0;
	if (!mnodo->existeIzquierda() && !mnodo->existeDerecha()) {
		return 1;
	}
	else {
		return(numHojas(mnodo->getIzquierda() + numHojas(mnodo->getDerecha())));
	}

}

template <class T>
bool ABB<T>::eliminar1(Nodo<T>* mnodo) {
	Nodo<T>* hijoIzquierdo = mnodo.getDato().getIzquierda();
	Nodo<T>* hijoDerecho = mnodo.getDato().getDerecha();

	if (hijoIzquierdo == mnodo) {
		mnodo.getDato().setIzquierda(NULL);
		return true;
	}

	if (hijoDerecho == mnodo) {
		nodo.getDato().setDerecha(NULL);
		return true;
	}

	return false;
}

template <class T>
bool ABB<T>::eliminar2(Nodo<T>* mnodo) {
	Nodo<T>* hijoIzquierdo = mnodo.getDato().getIzquierda();
	Nodo<T>* hijoDerecho = mnodo.getDato().getDerecha();

	Nodo<T>* hijoActual;
	if (mnodo.getIzquierda() != null) {
		hijoActual = mnodo.getIzquierda();
	}
	else {
		hijoActual = mnodo.getDerecha();
	}


	if (hijoIzquierdo == mnodo) {
		mnodo.getDato().setIzquierda(hijoActual);
		hijoActual.setDato(mnodo.getDato());
		mnodo.setDerecha(NULL);
		mnodo.setIzquierda(NULL);

		return true;
	}

	if (hijoDerecho == mnodo) {
		mnodo.getDato().setDerecha(hijoActual);
		hijoActual.setDato(mnodo.getDato());
		mnodo.setDerecha(NULL);
		mnodo.setIzquierda(NULL);

		return true;
	}

	return false;
}

template <class T>
bool ABB<T>::eliminar3(Nodo<T>* mnodo) {
	//Tomar el hijo derecho del Nodo que queremos eliminar
	Nodo<T>* nodoMasALaIzquierda = recorrerIzquierda(mnodo.getDerecha());
	if (nodoMasALaIzquierda != NULL) {
		//Reemplazamos el valor del nodo que queremos eliminar por el nodo que encontramos
		mnodo.setDato(nodoMasALaIzquierda.getDato());
		//Eliminar este nodo de las formas que conocemos ( caso 1, caso 2 )
		removeNodo(nodoMasALaIzquierda);
		return true;
	}
	return false;
}

template <class T>
Nodo<T>* ABB<T>::recorrerIzquierda(Nodo<T>* mnodo) {
	if (mnodo.getIzquierda() != NULL) {
		return recorrerIzquierda(mnodo.getIzquierda());
	}
	return mnodo;
}

template <class T>
bool ABB<T>::eliminar(Nodo<T>* mnodo) {
	bool tieneNodoDerecha;
	bool tieneNodoIzquierda;
	//Creamos variables para saber si tiene hijos izquierdo y derecho 
	if (mnodo.getDerecha() != NULL) {
		tieneNodoDerecha = true;
	}else {
		tieneNodoDerecha = false;
	}

	if (mnodo.getIzquierda() != NULL) {
		tieneNodoIzquierda = true;
	}else {
		tieneNodoIzquierda = false;
	}
	//No tiene hijos
	if (!tieneNodoDerecha && !tieneNodoIzquierda) {
		return eliminar1(mnodo);
	}

	//Tiene un hijo y el otro no
	if (tieneNodoDerecha && !tieneNodoIzquierda) {
		return eliminar2(mnodo);
	}

	//Caso 2: Tiene un hijo y el otro no
	if (!tieneNodoDerecha && tieneNodoIzquierda) {
		return eliminar2(mnodo);
	}

	// Caso 3: Tiene ambos hijos
	if (tieneNodoDerecha && tieneNodoIzquierda) {
		return eliminar3(mnodo);
	}

	return false;
}

#endif // !ABB_H