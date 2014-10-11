/* 
 * File:   Nodo.h
 * Author: nicomda
 *
 * Created on 11 de octubre de 2014, 12:02
 */

#ifndef NODO_H
#define	NODO_H
template<class T> class Nodo{
    public:
        T dato;
        Nodo *sig;
        Nodo(T &aDato, Nodo *aSig=0):dato(aDato), sig(aSig){};
};


#endif	/* NODO_H */

