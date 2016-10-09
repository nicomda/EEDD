/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Miriam y Nico
 *
 * Created on 4 de octubre de 2016, 10:41
 */

#include <cstdlib>
#include <fstream>
#include <cstdio>
#include "Fichero.h"
#include "Commit.h"
#include "VDinamico.h"
#include "Excepciones.h"
using namespace std;

Fichero parseFichero(string fichero){
    auto pos = fichero.find(';');
    auto ruta = fichero.substr(0, pos);
    auto tama = fichero.substr(pos + 1, fichero.length());
    // Separamos la ubicacion del nombre del fichero
    pos = ruta.find_last_of('/');
    auto ubicacion = ruta.substr(0, pos + 1);
    auto nombre = ruta.substr(pos + 1, ruta.length());
    // Convertimos el string a int
    auto tamaBytes = stoi(tama);
    return Fichero(nombre,ubicacion,tamaBytes);
}

VDinamico<Fichero> readFichero(string path){
    ifstream inputStream;
    string toParse;
    VDinamico<Fichero> ficheros;
    try{
	inputStream.exceptions(ifstream::failbit | ifstream::badbit);
	inputStream.open(path);
        //Para quitar cabecera del fichero
        inputStream >> toParse;
        while (!inputStream.eof()) {
            inputStream >> toParse;
            ficheros.insertar(parseFichero(toParse));
        }
    }catch(ifstream::failure &e){
        cerr << "Excepcion leyendo de fichero: " << e.what() << endl;
    }catch(ERROR_FUERA_RANGO& e){
        cerr << "Excepcion en el vector dinámico" << e.what() << endl;
    }
    inputStream.close();
    return ficheros;
}

int main(int argc, char** argv) {

    VDinamico<Fichero> ficheros;
    ficheros=readFichero("ficheros2.txt");
    for(int i=0;i<10;i++){
        cout << ficheros[i].GetNombre() << endl;
    }

	
    return 0;
        
}

