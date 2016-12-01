#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H

#include <exception>

using namespace std;

class ERROR_DATOS_INCORRECTOS :public exception{
public:
	const char* what(){
		return "Datos incorrectos";
	}
};

class ERROR_FUERA_RANGO :public exception{
public:
	const char* what(){
		return "Fuera del rango del vector";
	}
};

class FECHA_NO_VALIDA :public exception{
public:
	const char* what(){
		return "Fecha no valida";
	}
};
class ERROR_CLAVE_REPETIDA :public exception{
public:
	const char* what(){
		return "Clave repetida en la tabla hash";
	}
};

class ERROR_DATO_NO_ENCONTRADO :public exception{
public:
	const char* what(){
		return "Dato no encontrado en la tabla hash";
	}
};



#endif