/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Fichero.h
 * Author: Miriam y Nico
 *
 * Created on 4 de octubre de 2016, 12:02
 */

#ifndef FICHERO_H
#define FICHERO_H
#include <string>
#include <iostream>
using namespace std;
class Fichero {
public:
    Fichero();
    Fichero(string nombre, string ubicacion, int tamaBytes);
    Fichero(const Fichero& orig);
    virtual ~Fichero();
    void SetTamaBytes(int tamaBytes);
    int GetTamaBytes() const;
    void SetUbicacion(string ubicacion);
    string GetUbicacion() const;
    void SetNombre(string nombre);
    string GetNombre() const;
private:
    string nombre;
    string ubicacion;
    int tamaBytes;
};

#endif /* FICHERO_H */

