#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H
#include <exception>
using namespace std;

//Implementamos las excepciones que vamos a necesitar.
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
#endif // !EXCEPCIONES_H
