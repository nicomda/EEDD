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
	//Nodo<T>* borraDato(T& mdato, Nodo<T>* mnodo);
	void borrarNodo(Nodo<T>* mpadre, Nodo<T>* mnodo);
	void borrarNodoHijos(Nodo<T>* mnodo);
	void preorden(Nodo<T>* mnodo, int nivel);
	void inorden(Nodo<T>* mnodo, int nivel);
	void postorden(Nodo<T>* mnodo, int nivel);

public:
	ABB() { raiz = NULL; numElementos = 0; }
	ABB(Nodo<T>* mraiz, unsigned mnumElementos) { raiz = mraiz; numElementos = mnumElementos; }
	ABB(const ABB<T>& orig) { raiz = orig.raiz; numElementos = orig.numElementos; }
	~ABB() {}
	//Creamos los metodos getraiz para obtener la raiz y getNumElementos para obtener el numero de elementos del vector.
	Nodo<T>* getRaiz() { return raiz; }
	unsigned getNumElementos() { return numElementos; }
	//Creamos los metodos getraiz para cambiar la raiz y getNumElementos para cambiar el numero de elementos del vector.
	void setRaiz(Nodo<T>* mraiz) { this->raiz = mraiz; }
	void setNumElementos(unsigned mnumElementos) { this->numElementos = mnumElementos; }
	//Creamos los metodos para hacer los recorridos por el arbol.
	void recorrePreorden() { preorden(raiz, 0); }
	void recorreInorden() { inorden(raiz, 0); }
	void recorrePostorden() { postorden(raiz, 0); }
	//Creamos los metodos del arbol.
	bool buscar(T& mdato);
	bool insertar(T& mdato);
	int altura(T& mdato);
	int alturaTotal();
	int numHojas();
	//bool eliminar(T& mdato);
	//Nodo<T>* borraMin(Nodo<T>* mnodo);
	bool eliminar(T& mdato);
};
template <class T>
void ABB<T>::preorden(Nodo<T>* mnodo, int nivel) {
	if (mnodo) {
		// Sustituir por procesamiento ---
		cout << "Procesando nodo " << mnodo->getDato() << endl;
		cout << "en el nivel " << nivel << endl;
		// -----------
		preorden(mnodo->getIzquierda(), nivel + 1);
		preorden(mnodo->getDerecha(), nivel + 1);
	}
} 

template <class T>
void ABB<T>::inorden(Nodo<T>* mnodo, int nivel) {
	if (mnodo) {
		inorden(mnodo->getIzquierda(), nivel + 1);
		// Sustituir por procesamiento ----
		cout << "Procesando nodo " << mnodo->getDato();
		cout << "en el nivel " << nivel << endl;
		// -----------
		inorden(mnodo->getDerecha(), nivel + 1);
	}
}

template <class T>
void ABB<T>::postorden(Nodo<T>* mnodo, int nivel) {
	if (mnodo) {
		postorden(mnodo->getIzquierda(), nivel + 1);
		postorden(mnodo->getDerecha(), nivel + 1);
		// Sustituir por procesamiento ----
		cout << "Procesando nodo " << mnodo->getDato();
		cout << "en el nivel " << nivel << endl;
		// -----------
	}
}

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
int ABB<T>::alturaTotal() {
	Nodo<T>* mnodo = raiz;
	int AltIzquierda;
	int AltDerecha;
	if (!mnodo) {
		return -1;
	}
	else {
		AltIzquierda = alturaTotal(mnodo->getIzquierda());
		AltDerecha = alturaTotal(mnodo->getDerecha());
		if (AltIzquierda > AltDerecha) {
			return AltIzquierda + 1;
		}
		else {
			return AltDerecha + 1;
		}
	}
}

template <class T>
int ABB<T>::numHojas() {
	Nodo<T>* mnodo = raiz;
	if (!mnodo)return 0;
	if (!mnodo->existeIzquierda() && !mnodo->existeDerecha()) {
		return 1;
	}
	else {
		return(numHojas(mnodo->getIzquierda() + numHojas(mnodo->getDerecha())));
	}

}
/*
template <class T>
Nodo<T> *ABB<T>::borraMin(Nodo<T>* mnodo) {
	Nodo<T> *resultado;
	if (mnodo) {
		if (mnodo->getIzquierda())
			return borraMin(mnodo->getIzquierda());
		else {
			resultado = mnodo;
			mnodo = mnodo->getDerecha();
			return resultado;
		}
	}
}

template <class T>
Nodo<T> *ABB<T>::borraDato(T& mdato, Nodo<T>* mnodo) {
	if (mnodo) {
		if (mdato < mnodo->getDato())
			borraDato(mdato, mnodo->getIzquierda());
		else
			if (mdato > mnodo->getDato())
				borraDato(mdato, mnodo->getDerecha());
			else { //encontrado
				Nodo<T> *auxiliar = mnodo;
				if (!mnodo->getIzquierda()) //tiene hijo a la decha
					mnodo = mnodo->getDerecha();
				else
					if (!mnodo->getDerecha()) //tiene hijo a la izda
						mnodo = mnodo->getIzquierda();
					else if (mnodo->getIzquierda() && mnodo->getDerecha()) { //tiene ambos hijos
						auxiliar = borraMin(mnodo->getDerecha());
						mnodo->getDato() = auxiliar->getDato();
					}
					delete auxiliar; //borrar en todos los casos (también hoja)
			}
	}
	return mnodo;
}

template<class T>
bool ABB<T>::eliminar(T& mdato) {
	Nodo<T>* resultado = borraDato(mdato, raiz);
	if (resultado) return true;
	return false;
}

*/

template<typename T>
void ABB<T>::borrarNodo(Nodo<T>* mpadre, Nodo<T>* mnodo) {
	if (mpadre != 0) {
		if (mnodo->getDato() < mpadre->getDato()) {
			mpadre->getIzquierda() = 0;
		}
		if (mnodo->getDato() > mpadre->getDato()) {
			mpadre->getDerecha() = 0;
		}
			
	}
	delete mnodo;
}

template<typename T>
void ABB<T>::borrarNodoHijos(Nodo<T>* mnodo) {
	Nodo<T>* auxiliar = mnodo;
	Nodo<T>* auxiliar2 = mnodo;
	if (auxiliar->getIzquierda()) {
		auxiliar = auxiliar->getIzquierda();
		if (!auxiliar2->getIzquierda()->getDerecha()) {
			auxiliar2->getIzquierda() = 0;
			mnodo->getDato() = auxiliar->getDato();
			delete auxiliar;
			return;
		}
		while (auxiliar->getDerecha() != 0) {
			if (auxiliar->getDerecha()->getDerecha()) {
				auxiliar2 = auxiliar2->getDerecha();
			}
			auxiliar = auxiliar->getDerecha();
		}
		mnodo->getDato() = auxiliar->getDato();
		auxiliar2->getDerecha() = 0;
	}
	else {
		auxiliar = auxiliar->getDerecha();
		if (!auxiliar2->getDerecha()->getIzquierda()) {
			auxiliar2->getDerecha() = 0;
			mnodo->getDato() = auxiliar->getDato();
			delete auxiliar;
			return;
		}

		if (auxiliar->getDerecha()->getIzquierda()) {
			auxiliar2 = auxiliar2->getDerecha();
		}
		while (auxiliar->getIzquierda() != 0) {
			if (auxiliar2->getIzquierda()->getIzquierda()) {
				auxiliar2 = auxiliar2->getIzquierda();
			}
			auxiliar = auxiliar->getIzquierda();
		}
		mnodo->getDato() = auxiliar->getDato();
		auxiliar2->getIzquierda() = 0;
	}
	delete auxiliar;
}

template<typename T>
bool ABB<T>::eliminar(T& mdato) {
	Nodo<T>* auxiliar = raiz;
	Nodo<T>* auxiliar2 = raiz;
	if (mdato == raiz->getDato()) {
		delete raiz;
		raiz = 0;
		return true;
	}

	while (auxiliar->existe()) {
		if (mdato < auxiliar->getDato()) {
			if (auxiliar2->getIzquierda()->getIzquierda()) {
				auxiliar2 = auxiliar2->getIzquierda();
			}
				
			auxiliar = auxiliar->getIzquierda();
		}

		if (mdato > auxiliar->getDato()) {
			if (auxiliar2->getDerecha()->getDerecha()) {
				auxiliar2 = auxiliar2->getDerecha();
			}
	
			auxiliar = auxiliar->getDerecha();
		}

		if (auxiliar->getDato() == mdato) {
			if (auxiliar->getIzquierda() == 0 && auxiliar->getDerecha() == 0)
				borrarNodo(auxiliar2, auxiliar);
			else
				borrarNodoHijos(auxiliar);
			return true;
		}
	}
	return false;
}

#endif // !ABB_H