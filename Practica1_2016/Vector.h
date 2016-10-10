/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vector.h
 * Author: Miriam
 *
 * Created on 26 de septiembre de 2016, 23:53
 */

#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>
#include <iostream>
#include <string>
#include "Excepciones.h"


using namespace std;
template <class T>
class Vector {
    
    public:  
        Vector(unsigned mtam); //Constructor por parametros.
        Vector(const Vector<T>& v); //Constructor copia.
        Vector(const Vector<T>& origen, unsigned inicio, unsigned num); //Constructor copiando los datos desde el origen hasta el fin.
        Vector<T>& operator=(const Vector<T>& orig); //Operador Asignación.
        virtual ~Vector(); //Destructor.
    
        //Modificadores leer y escribir.
	T& leer(unsigned pos); 
	void escribir(unsigned pos, const T& dato);
    
        T& operator[](unsigned pos); //Acceder a un dato con operador []
        
        //void operator[](unsigned pos, T& dato); //Operador[] cambiar un dato
        
        unsigned GetTam(); 
    
    private:
        unsigned tam; //tamaño máximo del vector
        T* v; //creamos el contenedor.   
};


template <class T> //creamos la plantilla

//creamos el constructor 
Vector<T>::Vector(unsigned mtam){
    tam = mtam;
    v= new T[tam];
}

template <class T>
Vector<T>::Vector(const Vector<T>& orig) {
    //Liberamos primero memoria.
    delete[] v;
    //cogemos el tamaño del vector.
    tam = orig.tam;
    //asignamos los datos.
    v=new T[orig.tam];
    for (int i=0; i < tam; i++){
        //copiamos los datos en el vector.
        v[i]=orig.v[i];
    }
   
}


template <class T>
Vector<T>::Vector(const Vector<T>& o, unsigned ini, unsigned n){
    // Comprobamos y añadimos excepción
    if (ini + n>o.tam) throw ERR_ENTRADA_DATOS();
    //liberamos memoria
    delete[] v;
    //le damos el numero de elementos igual a num
    v=new T[n];
    //declaramos un entero j=0.
    int j=0;
    for(int i=ini;i<ini+n; i++){
        //añdimos los datos al vector
        v[j]=o.v[i];
        j++;
    }
    tam = n;    
}

template <class T>
Vector<T>& Vector<T>:: operator=(const Vector<T>& orig){    
    //Liberamos memoria
    delete[] v;
    //Signamos el valor al tamaño
    tam=orig.tam;
    //creamos el vector
    v=new T[tam];
    //copiamos los datos en el vector
    for(int i=0; i<tam;i++){
        v[i]=orig.v[i];
    }
    return (*this);
   
}

template <class T>
T& Vector<T>::operator[](unsigned p){
    //Comprobamos y añadimos excepción
    if (p >= tam) throw ERR_FUERA_RANGO();
    //devolvemos el contenido
    return v[p];
    
}
/*
template <class T>
void Vector<T>::operator[](unsigned pos, T& t){
    //Comprobamos y añadimos excepción
    if (pos >= tam) throw ERR_FUERA_RANGO();
    //asignamos nuevo dato en la posición correspondiente
    v[pos] = t;
}
 */


template <class T>
Vector<T>::~Vector() {
    delete[] v;
}


template <class T>
unsigned Vector<T>::GetTam()  {
    return tam;
}


template <class T>
T& Vector<T>::leer(unsigned pos){
    if (pos >= tam) throw ERR_FUERA_RANGO();
    return v[pos];
}

template <class T>
void Vector<T>::escribir(unsigned pos, const T& dato){
    if (pos >= tam) throw ERR_FUERA_RANGO();
    v[pos] = dato;
}


#endif /* VECTOR_H */
