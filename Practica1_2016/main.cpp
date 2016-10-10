/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Miriam
 *
 * Created on 26 de septiembre de 2016, 23:47
 */

#include <cstdlib>
#include <fstream>
#include "Vector.h"
#include "Fichero.h"
#include "Excepciones.h"
#include <iostream>
#include <string>

using namespace std;
const unsigned TAM=200;

int main(){

    int cont=0;
    Vector<Fichero> ficheros(TAM);
    int numFicheros = 0;
    string nombre;
    string ubicacion;
    int tamaBytes;
    
    string rutaFichero("ficheros.txt");
    string lineaActual;
    
    try{
        ifstream inputStream;
        inputStream.exceptions(ifstream::failbit | ifstream::badbit);
        inputStream.open(rutaFichero);
        // Extraemos la cabecera del fichero
        inputStream >> lineaActual;
        while (!inputStream.eof()) {
            inputStream >> lineaActual;
            // Parseamos la linea
            auto pos = lineaActual.find(';');
            auto ruta = lineaActual.substr(0, pos);
            auto tama = lineaActual.substr(pos + 1, lineaActual.length());
            // Separamos la ubicacion del nombre del fichero
            pos = ruta.find_last_of('/');
            auto ubicacion = ruta.substr(0, pos + 1);
            auto nombre = ruta.substr(pos + 1, ruta.length());
            // Convertimos el string a int
            auto tamaBytes = stoi(tama);
            Fichero f(nombre,ubicacion,tamaBytes);
            ficheros.escribir(numFicheros,f);
            numFicheros++;
        }
        inputStream.close();
        cout<<"Ficheros leidos: "<< numFicheros<<endl;
        int suma = 0;
	for (int i = 0; i < numFicheros; i++){
            if (ficheros[i].GetTamaBytes()>3000){
            suma= suma + ficheros[i].GetTamaBytes();
            }
        }
        cout << "La suma de los ficheros son mas de 3000MB es: " << suma << endl;
        Vector<Fichero> fich2(ficheros, numFicheros - 5, 5);
        for (int i = 0; i < fich2.GetTam(); i++){
            cout << "Nombre: " << fich2[i].GetNombre() << endl;
            cout << "Ubicacion: " << fich2[i].GetUbicacion() << endl;
            cout << "Tamaño: " << fich2[i].GetTamaBytes() << endl;
        }

    }catch (ifstream::failure &e){
        cerr << "Excepcion leyendo de fichero: " << e.what() << endl;
    }catch (bad_alloc& e){
	cerr << "Reserva de memoria" << e.what() << endl;
    }catch (ERR_ENTRADA_DATOS& e){
	cerr << "Constructor desde origen" << e.what() << endl;
    }catch (ERR_FUERA_RANGO& e){
	cerr << "Acceso al vector: " << e.what() << endl;
    }
    return 0;
}



