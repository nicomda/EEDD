#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <string>
#include "ListaDEnlazada.h"
#include "GitCode.h"
#include "Fecha.h"
#include "Fichero.h"
#include "Commit.h"
#include "VDinamico.h"
#include "Excepciones.h"
using namespace std;
/*
//Creamos la funcion a la que pasaremos las lineas del fichero ficheros2.txt y separara los campos por ;.
//Despues creamos el fichero con los campos que hemos separado y los devolvemos con la función return.
Fichero parseFichero(string fichero) {
	auto pos = fichero.find(';');
	auto ruta = fichero.substr(0, pos);
	auto tama = fichero.substr(pos + 1, fichero.length());
	// Separamos la ubicacion del nombre del fichero
	pos = ruta.find_last_of('/');
	auto ubicacion = ruta.substr(0, pos + 1);
	auto nombre = ruta.substr(pos + 1, ruta.length());
	// Convertimos el string a int
	auto tamaBytes = stoi(tama);
	return Fichero(nombre, ubicacion, tamaBytes);
}

//Creamos la función donde le pasaremos las lineas del fichero commit.txt y separaremos los campos con ;.
//El while lo hemos creado por los ultimos campos que estan separados por ','.
//Despues creamos el commit con los campos que hemos separado y creamos el vector con los ficheros con los codigos
//que hemos separado de las ',' y lo devolvemos por la función return.
Commit parseCommit(string toParse, VDinamico<Fichero> &ficheros) {
	auto pos = toParse.find(';');
	auto codigo = toParse.substr(0, pos);
	toParse = toParse.substr(pos + 1, toParse.length());

	pos = toParse.find(';');
	auto timestamp = toParse.substr(0, pos);
	toParse = toParse.substr(pos + 1, toParse.length());

	pos = toParse.find(';');
	auto comment = toParse.substr(0, pos);
	toParse = toParse.substr(pos + 1, toParse.length());
	string references = toParse.substr(0, toParse.length());

	VDinamico<Fichero *> referencias_ficheros;
	Fichero* referencia;
	string split1, split2;
	int casted;

	while (references.find(',') != string::npos) {
		pos = references.find(',');
		split1 = references.substr(0, pos);
		casted = stoi(split1);
		split2 = references.substr(pos + 1, references.length());
		references = split2;
		referencias_ficheros.insertar(&ficheros[casted], referencias_ficheros.tam());
	}
	casted = stoi(references);
	referencias_ficheros.insertar(&ficheros[casted], referencias_ficheros.tam());
	return Commit(codigo, timestamp, comment, referencias_ficheros);
}


//Con esta función lo que hacemos es pasarle la ruta en la que se encuentra el fichero y devolemos un vector con todos
//los ficheros que lee linea a linea. 
VDinamico<Fichero> readFichero(string path) {
	ifstream inputStream;
	string toParse;
	VDinamico<Fichero> ficheros;
	try {
		inputStream.exceptions(ifstream::failbit | ifstream::badbit);
		inputStream.open(path);
		//Para quitar cabecera del fichero
		inputStream >> toParse;
		while (!inputStream.eof()) {
			inputStream >> toParse;
			ficheros.insertar(parseFichero(toParse));
		}
	}
	catch (ifstream::failure &e) {
		cerr << "Excepcion leyendo de fichero: " << e.what() << endl;
	}
	catch (ERROR_FUERA_RANGO& e) {
		cerr << "Excepcion en el vector dinámico" << e.what() << endl;
	}
	inputStream.close();
	return ficheros;
}

//Con esta función lo que hacemos es pasarle la ruta en la que se encuentra el commit y devolemos un vector con todos
//los commit que lee linea a linea. 
VDinamico<Commit> readCommit(string path, VDinamico<Fichero> &ficheros) {
	ifstream inputStream;
	string toParse;
	VDinamico<Commit> commits;
	try {
		inputStream.open(path);
		//Para quitar cabecera del fichero
		getline(inputStream, toParse);
		while (!inputStream.eof()) {
			getline(inputStream, toParse);
			commits.insertar(parseCommit(toParse, ficheros), commits.tam());
		}
	}
	catch (ifstream::failure &e) {
		cerr << "Excepcion leyendo de fichero: " << e.what() << endl;
	}
	catch (ERROR_FUERA_RANGO& e) {
		cerr << "Excepcion en el vector dinámico" << e.what() << endl;
	}
	inputStream.close();
	return commits;
}

//con esta función le pasamos el codigo de commit y el vector con todos los commits y buscamos el commit
//con el codigo que le hemos pasado.
Commit searchCommit(string code, VDinamico<Commit> &v_commits) {
	for (int i = 0; i<v_commits.tam(); i++) {
		if (v_commits[i].GetCodigo() == code) {
			return v_commits[i];
		}

	}
	throw ERROR_DATA_NOT_FOUND();
}

//en esta función le pasamos dos fechas una de inicio y otra de fin y el vector con todos los commit, y en el buscamos
//las fechas que se encuentren entre esas dos fechas pasadas por parametro y mostramos todos los commits que se encuentren
//entre esas dos fechas.
void listCommitsBetweenDates(double initDate, double endDate, VDinamico<Commit> &commits) {
	for (int i = 0; i<commits.tam(); i++) {
		if (initDate<stod(commits[i].GetMarcaDeTiempo()) && endDate>stod(commits[i].GetMarcaDeTiempo())) {
			cout << "-----" << "Coincidencia " << i << "---------" << endl;
			cout << "Codigo del commit: " << commits[i].GetCodigo() << endl;
			cout << "Marca de tiempo: " << commits[i].GetMarcaDeTiempo() << endl;
			cout << "Comentario: " << commits[i].GetMensaje() << endl;
		}
	}
	throw ERROR_DATA_NOT_FOUND();
}

//en esta función le pasamos el nombre de un fichero y el vector de commits, en el comprobaremos en cuantos commits
//se encuentra ese fichero.
void listCommitsModifyingFile(string filename, VDinamico<Commit> &commits) {
	for (int i = 0; i<commits.tam(); i++) {
		for (int j = 0; j<commits[i].tam_ficheros(); j++) {
			if (filename == commits[i].GetFichero(j)->GetNombre()) {
				cout << "-----" << "Coincidencia " << i << "---------" << endl;
				cout << "Codigo del commit: " << commits[i].GetCodigo() << endl;
				cout << "Marca de tiempo: " << commits[i].GetMarcaDeTiempo() << endl;
				cout << "Comentario: " << commits[i].GetMensaje() << endl;
			}
		}
	}
	throw ERROR_DATA_NOT_FOUND();
}

//en esta función imprimimos el menu de opciones para buscar por codigo, fecha o por fichero.
void printMenu() {
	cout << "------MENU------" << endl;
	cout << "1. Buscar commit por código" << endl;
	cout << "2. Buscar entre dos fechas" << endl;
	cout << "3. Buscar commits involucrados con un fichero" << endl;
	cout << "0. Salir" << endl;
	cout << "-----------------" << endl;
}

*/

void main() {
	try {
		GitCode git("ficheros2.txt", "commits.txt");

		cout << "Introduce un código de Commit: ";
		string codigo;
		cin >> codigo;
		Commit commitEncontrado;
		bool encontrado = false;
		encontrado = git.getCommit(codigo, commitEncontrado);
		if (!encontrado) {
			cout << "El commit no se ha encontrado. " << endl;
		}
		else {
			cout << "El commit encontrado es: " << commitEncontrado.GetMensaje() << endl;
		}

		cout << "Cargando........... " << endl;
		cout << "Introduzca la fecha de inicio: formato fecha(yyyymmddhhmmss): " << endl;
		string finicio, ffin;
		cin >> finicio;
		cout << "Introduzca la fecha de fin: formato fecha(yyyymmddhhmmss: " << endl;
		cin >> ffin;
		cout << "/n Los commits entre el rango de fechas introducidas son: " << endl;
		Fecha fini, ffn;
		VDinamico<Commit> commitFech;
		commitFech = git.getCommFechas(fini, ffn);
		for (int i = 0; i < commitFech.tam(); i++) {
			if (commitFech[i].entreFechas(fini, ffn)) {
				cout << commitFech[i].GetMensaje() << endl;
			}
		}


		string nomFichero;
		cout << "Cargando.........." << endl;
		cout << "Introduzca el codigo del fichero modificado. " << endl;
		cin >> nomFichero;
		VDinamico<Commit> commitFich;
		commitFich = git.getCommFichero(nomFichero);
		if (commitFich.tam() == 0) {
			cout << "Fichero no encontrado en ningun Commit" << endl;
		}
		else {
			cout << "/n El fichero se ha modificado en estos Commits: " << endl;
			for (int i = 0; i < commitFich.tam(); i++) {
				cout << commitFich[i].GetMensaje() << endl;
			}

			char borrar = ' ';
			do {
				cout << "¿Desea borrar el fichero? Responda: S/N" << endl;
				cin >> borrar;
			} while (borrar != 'S' || borrar != 'N');

			if (borrar == 'S') {
				git.eliminarFichero(nomFichero);
				cout << "Fichero y referencias eliminadas de todos los Commits" << endl;
			}

		}
	}
	catch (ERROR_DATOS_INCORRECTOS &error) {
		cerr << "Excepcion: " << error.what() << endl;
	}
	catch (ERROR_FUERA_RANGO &error) {
		cerr << "Excepcion: " << error.what() << endl;
	}
	catch (FECHA_NO_VALIDA &error) {
		cerr << "Excepcion: " << error.what() << endl;
	}
	catch (std::ifstream::failure &error) {
		cerr << "Excepcion: " << error.what() << endl;
	}
}