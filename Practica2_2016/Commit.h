/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Commit.h
 * Author: Miriam y Nico
 *
 * Created on 4 de octubre de 2016, 12:02
 */

#ifndef COMMIT_H
#define COMMIT_H
#include "Fichero.h"
#include <iostream>
#include <string>
#include "VDinamico.h"
using namespace std;
class Commit {
public:
    Commit();
    Commit(string mcodigo, string mmarcaDeTiempo, string mmensaje, VDinamico <Fichero*> mficheros);
    Commit(const Commit& orig);
    virtual ~Commit();
    void SetCodigo(string codigo);
    string GetCodigo() const;
    void SetMarcaDeTiempo(string marcaDeTiempo);   
    string GetMarcaDeTiempo() const;   
    void SetMensaje(string mensaje);    
    string GetMensaje() const;
    void SetFicheros(VDinamico<Fichero*> ficheros);
    Fichero* GetFichero(int pos);
    int tam_ficheros();
private:
    string codigo;
    string marcaDeTiempo;
    string mensaje;
    VDinamico <Fichero*> ficheros;
};

#endif /* COMMIT_H */

