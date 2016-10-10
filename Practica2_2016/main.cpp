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

Commit parseCommit(string toParse, VDinamico<Fichero> &ficheros ){
    auto pos = toParse.find(';');
    auto codigo = toParse.substr(0, pos);
    toParse=toParse.substr(pos+1,toParse.length());
    pos=toParse.find(';');
    auto timestamp=toParse.substr(0,pos);
    toParse=toParse.substr(pos+1,toParse.length());
    pos=toParse.find(';');
    auto comment= toParse.substr(0,pos);
    toParse=toParse.substr(pos+1,toParse.length());
    string references=toParse.substr(0,toParse.length());
    VDinamico<Fichero *> referencias_ficheros;
    Fichero* referencia;
    string split1,split2;
    int casted;
    while(references.find(',')!=string::npos){
        pos=references.find(',');
        split1=references.substr(0,pos);
        casted=stoi(split1);
        split2=references.substr(pos+1,references.length());
        references=split2;
        referencias_ficheros.insertar(&ficheros[casted],referencias_ficheros.tam());
    }
    casted=stoi(references);
    referencias_ficheros.insertar(&ficheros[casted],referencias_ficheros.tam());
    return Commit(codigo,timestamp,comment,referencias_ficheros);
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

VDinamico<Commit> readCommit(string path,VDinamico<Fichero> &ficheros){
    ifstream inputStream;
    string toParse;
    VDinamico<Commit> commits;
    try{
	inputStream.open(path);
        //Para quitar cabecera del fichero
        getline(inputStream,toParse);
        while (!inputStream.eof()) {
            getline(inputStream,toParse);
            commits.insertar(parseCommit(toParse,ficheros),commits.tam());
        }
    }catch(ifstream::failure &e){
        cerr << "Excepcion leyendo de fichero: " << e.what() << endl;
    }catch(ERROR_FUERA_RANGO& e){
        cerr << "Excepcion en el vector dinámico" << e.what() << endl;
    }
    inputStream.close();
    return commits;
}
int main(int argc, char** argv) {

    VDinamico<Fichero> v_ficheros;
    VDinamico<Commit> v_commits;
    v_ficheros=readFichero("ficheros2.txt");
    cout << "ficheros2.txt cargados" << endl;
    v_commits=readCommit("commits.txt",v_ficheros);
    cout << "commits.txt cargado" << endl;
    for(int i=0;i<10;i++){
    cout << v_commits[i].GetFichero(0)->GetNombre()<<endl;
    }
    return 0;
    
}

