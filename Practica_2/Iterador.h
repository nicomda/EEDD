/* 
 * File:   Iterador.h
 * Author: nicomda
 *
 * Created on 11 de octubre de 2014, 12:07
 */

#ifndef ITERADOR_H
#define	ITERADOR_H
template<class T> class Iterador{
    Nodo<T> *nodo;
    friend class ListaEnlazada;
    public:
        Iterador(Nodo<T> *aNodo): nodo(aNodo){};
        bool fin(){return nodo == 0;}
        void siguiente(){
            nodo=nodo->sig;
        }
        T &dato(){return nodo->dato;}
};


#endif	/* ITERADOR_H */

