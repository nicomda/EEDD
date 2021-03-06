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

class ERROR_FICHERO_REPETIDO :public exception {
public:
	const char* what() {
		return "El fichero ya se encuentra creado";
	}
};

class ERROR_COMMIT_REPETIDO :public exception {
public:
	const char* what() {
		return "El Commit ya se encuentra creado";
	}
};

class ERROR_COMMIT_NO_ENCONTRADO :public exception {
public:
	const char* what() {
		return "El Commit no se encuentra en la lista.";
	}
};

class ERROR_DATO_YA_INSERTADO :public exception {
public:
	const char* what() {
		return "El Commit ya se ha insertado en la lista.";
	}
};

class ERROR_CLAVE_REPETIDA :public exception {
public:
	const char* what() {
		return "La clave del dato que se desea insertar ya existe.";
	}
};
#endif // !EXCEPCIONES_H
