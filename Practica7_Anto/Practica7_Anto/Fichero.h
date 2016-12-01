/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#ifndef FICHERO_H
#define FICHERO_H
#include <iostream>
#include <string>
#include <sstream>

class Fichero {
public:
    Fichero();
    Fichero(const Fichero& orig);
	Fichero(std::string nombre, std::string ubicacion, int tama);
    virtual ~Fichero();
    void SetTamaBytes(int _tamaBytes);
    int GetTamaBytes() const;
    void SetUbicacion(std:: string _ubicacion);
    std:: string GetUbicacion() const;
    void SetNombre(std:: string _nombre);
    std:: string GetNombre() const;
    void leerDeFichero();
    
private:
   std:: string _nombre;
    std::string _ubicacion;
    int _tamaBytes;
};

#endif /* FICHERO_H */

