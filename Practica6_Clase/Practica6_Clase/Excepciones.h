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
class ERROR_COMMIT_NOENCONTRADO :public exception {
public:
	const char* what() {
		return "Commmit no encontrado";
	}
};
class ERROR_FICHERO_REPETIDO :public exception {
public:
	const char* what() {
		return "El fichero ya se encuentra en el sistema";
	}
};
class ERROR_COMMIT_REPETIDO :public exception {
public:
	const char* what() {
		return "El commit ya se encuentra en el sistema";
	}
};


#endif