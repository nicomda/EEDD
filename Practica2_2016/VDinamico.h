/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VDinamico.h
 * Author: nicomda
 *
 * Created on 4 de octubre de 2016, 10:57
 */

#ifndef VDINAMICO_H
#define VDINAMICO_H
#include "Excepciones.h"
#include <iostream>
#include <cstdlib>

using namespace std;

template<class T>
class VDinamico{
    private:
        
        T* contenedor;
        unsigned tamF;
        unsigned tamL;
        void aumentoTam();
        void disminuirTam();
        bool lleno();
        bool disminuir();
    public:
        VDinamico();
        VDinamico(unsigned tam, const T& dato);
        VDinamico(const VDinamico<T>& orig);
        VDinamico(const VDinamico<T>& origen, unsigned inicio, unsigned num);
        VDinamico<T>& operator=(const VDinamico<T>& orig);
        T& operator[](const unsigned pos);
        void insertar(const T& dato, unsigned pos = UINT_MAX);
        T borrar(unsigned pos= UINT_MAX);
        unsigned tam();
        ~VDinamico();
        
};

template <class T>
VDinamico<T>::VDinamico(){
    tamF=1;
    tamL=0;
    contenedor = new T[tamF];
}

template <class T>
VDinamico<T>::VDinamico(unsigned tam, const T& dato){
    tamL=tam;
    tamF= 2;
    while(tamF<tam){
        tamF*=2;
    }
    contenedor=new T[tamF];
    for(int i=0; i<tamL; i++){
        contenedor[i]=dato;
    }
}

template <class>
VDinamico<T>::VDinamico(const VDinamico<T>& orig){
    tamF=orig.tamF;
    tamL=orig.tamL;
    contenedor = new T[tamF];
    for(int i=0;i<tamL;i++){
        contenedor[i]=orig.contenedor[i];
    }
}

template<class T>
VDinamico<T>::VDinamico(const VDinamico<T>& origen, unsigned inicio, unsigned num){
    if((inicio+num)>origen.tamL) throw ERR_DATOS_INCORRECTOS();
    tamL=num;
    while(tamF<tam)tamF*=2;
    contenedor = new T[tamF];
    for (int i=0;i<tamL;i++){
    contenedor[i]=origen.contenedor[i];
    }
}

template<class T>
VDinamico<T>& VDinamico<T>::operator =(const VDinamico<T>& orig){
    tamF=orig.tamF;
    tamL=orig.tamL;
    contenedor=new T[tamF];
    for(int i=0;i<tamL;i++){
        contenedor[i]=orig.contenedor[i];
    }
    return *this;
}

template<class T>
T& VDinamico<T>::operator [](const unsigned pos){
    if(pos>tamL) throw ERR_FUERA_RANGO();
    return contenedor[pos];
}

template<class T>
void VDinamico<T>::aumentoTam(){
    T* aux=new T[tamF];
    for(int i=0;i<tamL;i++){
        aux[i] = contenedor[i];
    }
    delete[] contenedor;
    tamF*=2;
    contenedor=new T[tamF];
    for(int i=0;i<tamL;i++){
        contenedor[i]=aux[i];
    }
    delete[] aux;
}

template <class T>
bool VDinamico<T>::lleno(){
    return tamF==tamL;
}

template<class T>
bool VDinamico<T>::disminuir(){
    return tamL==(tamF/3);
}

template<class T>

void VDinamico<T>::disminuirTam(){
    T* aux = new T[tamF];
    for(int i=0;i<tamL;i++){
        aux[i]=contenedor[i];
    }
    delete[] contenedor;
    tamF /=2;
    contenedor=new T[tamF];
    for(int i=0;i<tamL;i++){
        contenedor[i]=aux[i];
    }
    delete[] aux;
}

template<class T>

void VDinamico<T>::insertar(const T& dato, unsigned pos = UINT_MAX){
    if(lleno())aumentoTam();
    if(pos==UINT_MAX || pos=tamL){
        contenedor[tamL++]=dato;
    }else{
        if(pos>tamL)throw ERR_FUERA_RANGO();
        for(int i=tamL;i>=pos;i--){
            contenedor[i]=contenedor[i-1];
            contenedor[pos]=dato;
            tamL++;
        }
    }
}

template <class T>
T VDinamico<T>::borrar(unsigned pos = UINT_MAX){
    T dato;
    if(pos == UINT_MAX || pos ==tamL-1) dato=contenedor[--tamL];
    else{
        if(pos >= tamL)throw ERR_FUERA_RANGO();
        dato=contenedor[pos];
        for(int i=0;i<tamL;i++){
        contenedor[i]=contenedor[i+1];
        
        }
        tamL--;
    }
    if (disminuir()) disminuirTam();
        return dato;
}

template<class T>
unsigned VDinamico<T>::tam(){
    return tamL;
}

template<class T>
VDinamico<T>::~VDinamico(){
    delete[] contenedor;
    tamL=tamF=0;
}
#endif /* VDINAMICO_H */

