#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H

#include <exception>

using namespace std;

class ERROR_DATOS_INCORRECTOS :public exception {
public:
	const char* what() {
		return "Datos incorrectos";
	}
};

class ERROR_FUERA_RANGO :public exception {
public:
	const char* what() {
		return "Fuera del rango del vector";
	}
};

class FECHA_NO_VALIDA :public exception {
public:
	const char* what() {
		return "Fecha no valida";
	}
};

class ERROR_DATO_YA_INSERTADO :public exception {
public:
	const char* what() {
		return "Error el dato introducido ya se encuentra dentro del arbol.";
	}
};


#endif // !EXCEPCIONES_H
