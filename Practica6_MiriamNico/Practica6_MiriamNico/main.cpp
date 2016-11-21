#include <iostream>
#include <fstream>
#include <string>
#include "GitCode.h"
#include "Commit.h"
#include "Fichero.h"
#include "Fecha.h"
#include "Excepciones.h"
#include <list>
#include <vector>
#include <map>
#include <set>
#include <cstdio>
using namespace std;

int main(int argc, char** argv) {
	try {
		GitCode git("ficheros2.txt", "commits.txt");
		cout << "Introduce el codigo de un Fichero que quiera borrar: " << endl;
		string nombre, codigo;
		cin >> codigo;

		git.borraFichero(nombre);
		int numFich = git.getNumFicherosActivos();
		vector<Fichero*> v = git.getFicherosActivos();
		cout << "Introduce el codigo del Commit que quiere borrar: " << endl;
		git.borraCommit(codigo);

		
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
		cerr << "Excepcion: Error al leer el fichero" << error.what() << endl;
	}
	catch (ERROR_COMMIT_NO_ENCONTRADO &error) {
		cerr << "Excepcion: " << error.what() << endl;
	}
	catch (ERROR_COMMIT_REPETIDO &error) {
		cerr << "Excepcion: " << error.what() << endl;
	}
	catch (ERROR_FICHERO_REPETIDO &error) {
		cerr << "Excepcion: " << error.what() << endl;
	}
}