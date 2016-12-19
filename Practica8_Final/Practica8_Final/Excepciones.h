#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H
#include <exception>
#include <iostream>
#include <string>
using namespace std;
class ERROR_PUNTUACION_FUERA_DE_RANGO :public exception {
public:
	const char* what() {
		return "La puntuacion debe estar entre un rango de [0,5]. Vuelva a intentarlo.";
	}
};

class ERROR_LIBRO_YA_VALORADO :public exception {
public:
	const char* what() {
		return "El libro que desea valorar ya ha sido valorado. Pruebe con otro libro.";
	}
};
#endif // !EXCEPCIONES_H

