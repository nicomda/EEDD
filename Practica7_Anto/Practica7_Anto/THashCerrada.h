#ifndef THASHCERRADA_H
#define THASHCERRADA_H
#include <vector>
#include "Excepciones.h"
using namespace std;

template<class T>
class Casilla{
	//-1 vacia; 0 libre; 1 ocupada
public:
	T dato;
	int estado;
	Casilla<T>() : dato(){ estado = 0; };
};


template<class T>
class THashCerrada{
private:
	

	vector<Casilla<T>> tabla;
	unsigned tamTabla;
	unsigned numElem;
	unsigned colisionesMax;


public:
	THashCerrada();
	THashCerrada(unsigned tam);
	THashCerrada(const THashCerrada& orig);
	~THashCerrada(){};
	unsigned getTamTabla(){ return tamTabla; };
	unsigned getColisionesMax(){ return colisionesMax; };
	unsigned getNumElem(){ return numElem; };
	bool insertar(long clave, const T dato);
	bool borrar(long clave, const T dato);
	T* buscar(long clave, const T dato);
	float factorCarga(){
		return numElem / tamTabla;
	};
};
	template<class T>
	THashCerrada<T>::THashCerrada() : tabla(){ tamTabla = numElem = colisionesMax = 0; }
	
	template<class T>
	THashCerrada<T>::THashCerrada(unsigned tam) : tabla(tam){
		tamTabla = tam;
		numElem = colisionesMax = 0;
		for (int i = 0; i < tamTabla; i++){
			Casilla<T> c;
			tabla[i] = c;
		}
	}
	template<class T>
	THashCerrada<T>::THashCerrada(const THashCerrada<T>& orig) :tabla(orig.tabla){
		tamTabla = orig.tamTabla;
		numElem = orig.numElem;
		colisionesMax = orig.colisionesMax;
	}
	template<class T>
	bool THashCerrada<T>::insertar(long clave, const T dato){
		unsigned colisiones = 0;
		unsigned posTabla = 0;
		unsigned salto = 0;
		if (tamTabla == numElem) return false; // tabla llena por lo que no caben mas datos
		posTabla = (clave+(salto*salto))%tamTabla; //exploración cuadrática
		while (tabla[posTabla].estado == 1){ 
			//MIENTRAS ESTE OCUPADA LA POSICIÓN TENEMOS COLISIONES Y POR LO TANTO HAY QUE OBTENER NUEVAS POLISIONES
			if (tabla[posTabla].dato == dato) throw ERROR_CLAVE_REPETIDA();
			colisiones++;
			salto++;
			posTabla = (clave + (salto*salto)) % tamTabla;
		}
		if (colisiones > colisionesMax) colisionesMax = colisiones;
		Casilla<T> c;
		c.dato = dato;
		c.estado = 1;
		tabla[posTabla] = c;
		numElem++;
		return true;
	}
	template<class T>
	bool THashCerrada<T>::borrar(long clave, const T dato){
		unsigned salto = 0;
		unsigned posTabla = 0;
		if (numElem == 0) return false;
		posTabla = (clave + (salto*salto)) % tamTabla; //exploración cuadrática
		bool enc = false;
		bool vacio = false;
		while (!enc && tabla[posTabla].estado!=0){ //mientras no encontremos el dato y la posicion esté ocupada
			if (tabla[posTabla].dato == dato) enc = true;
			else{
				salto++;
				posTabla = (clave + (salto*salto)) % tamTabla; //exploración cuadrática
			}
		}
		if (!enc) return false;
		tabla[posTabla].estado=-1;
		numElem--;
		
	}

	template<class T>
	T* THashCerrada<T>::buscar(long clave, const T dato){
		unsigned salto = 0;
		unsigned posTabla = 0;
		if (numElem == 0) return false;
		posTabla = (clave + (salto*salto)) % tamTabla; //exploración cuadrática
		bool enc = false;
		bool vacio = false;
		while (!enc && tabla[posTabla].estado != 0){ //mientras no encontremos el dato y la posicion esté ocupada
			if (tabla[posTabla].dato == dato) enc = true;
			else{
				salto++;
				posTabla = (clave + (salto*salto)) % tamTabla; //exploración cuadrática
			}
		}
		if (!enc) return NULL;
		return &(tabla[posTabla].dato);

	}
	


#endif

