/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VDinamico.h
 * Author: Miriam y Nico
 *
 * Created on 4 de octubre de 2016, 10:44
 */

#ifndef VDINAMICO_H
#define VDINAMICO_H
#include "Excepciones.h"
#include <iostream>
#include <string>
using namespace std;

template <class T>
class VDinamico{
    private:
        T* vector;
        unsigned tamF;
        unsigned tamL;
        void aumentoTam();    // las creamos privadas para cualquiera que utilize la clase no pueda 
        void disminuirTam();  // usarlas ni cambiar el vector.
        bool lleno();
        bool disminuir();
        
    public:
        VDinamico();
        VDinamico(unsigned tam, const T& dato);
        VDinamico(const VDinamico<T>& orig);
        VDinamico(const VDinamico<T>& origen, unsigned inicio, unsigned num);
        VDinamico<T>& operator=(const VDinamico<T>& orig);
        T& operator[](const unsigned pos);
        void insertar (const T& dato, unsigned pos = UINT_MAX);
        T borrar(unsigned pos = UINT_MAX);
        unsigned tam();
        ~VDinamico();
        
};     

template <class T>
VDinamico<T>::VDinamico(){
    tamF=1; //vamos a incrementarlo en potencias de 2 por eso lo ponemos a 1
    tamL=0;
    vector = new T[tamF]; // pasamos tamF para reservar la memoria con ese tamaño.
}

template <class T>
VDinamico<T>::VDinamico(unsigned tam, const T& dato){
    tamL= tam;
    tamF = 2;
    while (tamF<tam){
        tamF *= 2;
    }
    
    vector = new T[tamF];
    for (int i = 0; i < tamL; i++){
    vector[i]=dato;   
    }    
}

template <class T>
VDinamico<T>::VDinamico(const VDinamico<T>& orig){
    tamF=orig.tamF;
    tamL=orig.tamL;
    vector = new T[tamF];
    for(int i = 0; i<tamL;i++){
        vector[i]=orig.vector[i];
    }
}

template <class T>
VDinamico<T>::VDinamico(const VDinamico<T>& origen, unsigned inicio, unsigned num){
    if(inicio + num>origen.tamL) throw ERROR_DATOS_INCORRECTOS();
    tamL = num;
    while(tamF<tamL){
        tamF *= 2;
        vector = new T[tamF];
        for(int i=0; i < tamL;i ++){
            vector[i]=origen.vector[i];
        }
    }
}

template <class T>
VDinamico<T>& VDinamico<T>::operator =(const VDinamico<T>& orig){
    tamF=orig.tamF;
    tamL=orig.tamL;
    vector = new T[tamF];
    for(int i = 0; i < tamL; i++){
        vector[i]=orig.vector[i];
    }
    return *this;
}

template <class T>
T& VDinamico<T>::operator [](const unsigned pos){
    if(pos>tamL) throw ERROR_FUERA_RANGO();
    return vector[pos];
}


template <class T>
void VDinamico<T>::aumentoTam(){
    T* aux = new T[tamF];
    for(int i=0; i<tamL; i++){
        aux[i]=vector[i];
    }
    delete[] vector;
    tamF *= 2;
    vector = new T[tamF];
    for (int i = 0; i < tamL; i++){
        vector[i]=aux[i];
    }
    delete[] aux;
}

template <class T>
void VDinamico<T>::disminuirTam(){
    T* aux = new T[tamF];
    for(int i = 0;i < tamL; i++){
        aux[i]= vector[i];
    }
    delete[] vector;
    tamF /= 2;
    vector = new T[tamF];
    for(int i=0; i<tamL; i++){
        vector[i]= aux[i];
    }
    delete[] aux;
}

template <class T>
bool VDinamico<T>::lleno(){
    return tamF == tamL;
}

template <class T>
bool VDinamico<T>::disminuir(){
    return tamL == tamF/3;
}

template <class T>
void VDinamico<T>::insertar(const T& dato, unsigned pos){
    if(lleno()) aumentoTam();
    if(pos == UINT_MAX || pos == tamL){
        vector[tamL++]= dato;
    } else {
        if(pos > tamL)throw ERROR_FUERA_RANGO();
        for(int i = tamL;i>= pos; i--){
            vector[pos] = vector[i-1];
        }
        vector[pos] = dato;
        tamL++;
    }
}

template <class T>
T VDinamico<T>::borrar(unsigned pos){
    T dato;
    if(pos == UINT_MAX || pos == tamL - 1){
        dato = vector[tamL--];
    } else {
      if(pos>=tamL) throw ERROR_FUERA_RANGO();
      dato=vector[pos];
      for(int i = pos; i < tamL; i++){
          vector[i] = vector[i+1];
      }
      tamL--;
    }
    if(disminuir()) disminuirTam();
    return dato;
}


/**

T VDinamico<T>::borrar(unsigned pos = UINT_MAX) {
	T dato;
	if (pos <= tamL)throw ERROR_FUERA_RANGO();
	if (pos == UINT_MAX) {
		dato = vector[tamL--];
		tamL--;
	}
	else {
		dato = contenedor[pos];
		for (int i = pos; i < tamL - 1; i++) {
			vector[i] = vector[i + 1];
		}
		tamL--;
	}
	if (tamL <= tamF / 3) {
		disminuirTam();
	}
	return dato;

}

*/


template <class T>
unsigned VDinamico<T>::tam(){
    return tamL;
}

template <class T>
VDinamico<T>::~VDinamico(){
    delete[] vector;
    tamL = tamF = 0;
    
}
#endif /* VDINAMICO_H */

