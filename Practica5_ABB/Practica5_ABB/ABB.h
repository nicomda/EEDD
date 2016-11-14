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
	~ABB() {}

	Nodo<T>* getRaiz() { return raiz; }
	unsigned getNumElementos() { return numElementos; }

	void setRaiz(Nodo<T>* mraiz) { this->raiz = mraiz; }
	void setNumElementos(unsigned mnumElementos) { this->numElementos = mnumElementos; }

	bool buscar(T& mdato, Nodo<T>* nodo);
	bool insertar(T& mdato);
	Nodo<T>* menorDescendiente(Nodo<T> *mnodo);
	Nodo<T>* buscarMinimo(Nodo<T> *mnodo);
	bool eliminar(T& mdato, Nodo<T>* mnodo);
	int altura(T& mdato);
	int alturaTotal(Nodo<T>* mnodo);
	int numHojas(Nodo<T>* mnodo);


};
template<class T>
bool ABB<T>::buscar(T& mdato, Nodo<T>* mnodo) {
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
	return encontrado;
}

template<class T>
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

template<class T>
Nodo<T>* ABB<T>::menorDescendiente(Nodo<T> *mnodo) {
	if (mnodo == NULL) {
		return mnodo;
	}
	if (mnodo->getDerecha() == NULL) {
		return NULL;
	}
	return(buscarMinimo(mnodo->getDerecha()));
}

template<class T>
Nodo<T>* ABB<T>::buscarMinimo(Nodo<T> *mnodo) {
	while (mnodo != NULL) {
		if (mnodo->getIzquierda() == NULL) {
			return mnodo;
		}
		else {
			mnodo = mnodo->getDerecha();
		}
	}
	return mnodo;
}

template<class T>
bool ABB<T>::eliminar(T& mdato, Nodo<T>* mnodo){
	Nodo<T>* aux;
	if (mnodo == NULL) throw ERROR_DATOS_INCORRECTOS() {
		return false;
	}
	else {
		//Por la izquierda.
		if (mdato < mnodo->getDato()) {
			mnodo->getIzquierda() = borrar(mnodo->getIzquierda(), mdato);
			return true;
		}
		else if (mdato > mnodo->getDato()) {
			//Por la derecha.
			mnodo->getDerecha() = borrar(mnodo->getDerecha(), mdato);
			return true;
		}
		else {
			//Si encontramos el elemento.
			if (mnodo->getIzquierda() && mnodo->getDerecha()) {
				//Si tiene dos hijos.
				aux = menorDescendiente(mnodo->getDerecha());
				mnodo->getDato() = aux->getDato(); //Copiamos el nodo en uno auxiliar.
				mnodo->getDerecha() = borrar(mnodo->getDerecha(), aux->getDato()); //borramos nodo
				return true;
			}
			else {
				//Si tiene un solo hijo o ninguno.
				aux = mnodo;
				//Si solo tiene un hijo derecho o no tiene hijos
				if (mnodo->getIzquierda() == NULL) {
					mnodo = mnodo->getDerecha();
					return true;
				}
				else {
					//Si solo tiene un hijo izquierdo
					if (mnodo->getDerecha() == NULL) {
						mnodo = mnodo->getIzquierda();
						return true;
					}
					free(aux);
				}
			}
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


#endif // !ABB_H


