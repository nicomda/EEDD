/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Excepciones.h
 * Author: Miriam
 *
 * Created on 26 de septiembre de 2016, 23:53
 */

#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H
#include <exception>

using namespace std;

class ERR_ENTRADA_DATOS :public exception{
public:
	const char* what(){
		return "Datos de entrada incorrectos";
	}
};

class ERR_FUERA_RANGO :public exception{
public:
	const char* what(){
		return "Fuera del rango del vector";
	}
};



#endif