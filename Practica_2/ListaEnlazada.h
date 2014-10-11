/* 
 * File:   ListaEnlazada.h
 * Author: nicomda
 *
 * Created on 10 de octubre de 2014, 12:57
 */

#ifndef LISTAENLAZADA_H
#define	LISTAENLAZADA_H

#include "Nodo.h"

template<typename T>
class ListaEnlazada {
    Nodo<T> *cabecera, *cola;
public:

    ListaEnlazada() : cabecera(0), cola(0) {
    }
    ListaEnlazada(const ListaEnlazada &l);
    ~ListaEnlazada();
    ListaEnlazada &operator=(ListaEnlazada &l);

    Iterador<T> iterador() {
        return Iterador<T>(cabecera);
    }
    T leer(int pos);
    void insertarInicio(T &dato);
    void insertarFinal(T &dato);
    void insertar(Iterador<T> &i, T &dato);
    void borrarInicio();
    void borrarFinal();
    void borrar(Iterador<T> &i);
};

template <class T>
void ListaEnlazada::insertarInicio(T& dato) {
    Nodo<T> *nuevo;
    nuevo = new Nodo<T>(dato, cabecera);
    if (cola == 0) {
        cola = nuevo;
    }
    cabecera = nuevo;
}

template <class T>
void ListaEnlazada::insertarFinal(T& dato) {
    Nodo<T> *nuevo;
    nuevo = new Nodo<T>(dato, 0);
    if (cola != 0) {
        cola->sig = nuevo;
    }
    if (cabecera == 0) {
        cabecera = nuevo;
    }
    cola = nuevo;
}

template <class T>
void ListaEnlazada::insertar(Iterador<T>& i, T& dato) {
    Nodo<T> *nuevo;
    Nodo<T> *anterior = 0;
    nuevo = new Nodo<T>(dato,p);
    if (cabecera != cola) {
        anterior = cabecera;
        while (anterior->sig !=)
            anterior = anterior->sig;
    }
    anterior->sig = nuevo;
    if (cabecera == 0) {
        cabecera = cola = nuevo;
    }
}

template <class T>
void ListaEnlazada::borrarInicio() {
    Nodo<T> *borrado = cabecera;
    cabecera = cabecera->sig;
    delete borrado;
    if (cabecera == 0) {
        cola = 0;
    }
}

template <class T>
void ListaEnlazada::borrarFinal() {
    Nodo<T> *anterior = 0;
    if (cabecera != cola) {
        anterior = cabecera;
        while (anterior->sig != cola) {
            anterior = anterior->sig;
        }
        delete cola;
    }
    cola = anterior;
    if (anterior != 0)
        anterior->sig = 0;
    else cabecera = 0;

}

template <class T>
void ListaEnlazada::borrar(Iterador<T>& i) {
    Nodo<T> *anterior = 0;
    if (cabecera != cola) {
        anterior = cabecera;
        while (anterior->sig != p) {
            anterior = anterior->sig;
        }
    }
    anterior->sig=p->sig;
    delete p;
}
template <class T>
T ListaEnlazada::leer(int pos){
    Nodo<T> *nodo=cabecera;
    while(pos-- >0 && nodo != 0){
        nodo=nodo->sig;
    }
    if(nodo!=0)
        return nodo->dato;
    return 0;
}

#endif	/* LISTAENLAZADA_H */

