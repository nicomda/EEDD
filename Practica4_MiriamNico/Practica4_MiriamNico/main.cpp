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
using namespace std;

int main(int argc, char** argv) {
	try {
		GitCode git("ficheros2.txt", "commits.txt");
		cout << "Introduce el codigo de un Commit: " << endl;
		string codigo;
		cin >> codigo;

		Commit commits;
		bool encontrado = false;
		encontrado = git.getCommit(codigo, commits);

		if (!encontrado) {
			cout << "El commit con codigo : " << codigo << " no se ha encontrado. " << endl;
		}
		else {
			cout << "El commit con codigo: " << codigo << " se ha encontrado y es: " << commits.getMensaje() << endl;
		}

		cout << "Cargando------------------------------------------------------------------------------------" << endl;
		cout << "Introduzca una fecha de inicio (con formato: (yyyymmddhhmmss)): " << endl;
		string fechaInicio, fechaFin;
		cin >> fechaInicio;
		cout << "Introduzca una fecha de fin (con formato: (yyyymmddhhmmss)): " << endl;
		cin >> fechaFin;
		cout << "/n Los commits encontrados entre la fecha de inicio y la fecha de fin, son: " << endl;
		Fecha finicio, ffin;
		finicio.pasarFFecha(fechaInicio);
		ffin.pasarFFecha(fechaFin);
		vector<Commit*> commitFechas;
		commitFechas = git.getCommitFechas(finicio, ffin);
		for (int i = 0; i < commitFechas.size(); i++) {
			if (commitFechas[i]->entreDosFechas(finicio, ffin)) {
				cout << commitFechas[i]->getFecha() << "  :" << commitFechas[i]->getMensaje() << endl;
			}
		}
		string nombreFichero;
		cout << "Cargando------------------------------------------------------------------------------------" << endl;
		cout << "Introduzca el nombre del fichero que quiere ver si ha sido modificado: " << endl;
		cin >> nombreFichero;
		vector<Commit*> commitFicheroMod;
		commitFicheroMod = git.getCommitFichero(nombreFichero);
		if (commitFicheroMod.size() == 0) {
			cout << "El fichero con nombre: " << nombreFichero << " no ha sido encontrado." << endl;
		}
		else {
			cout << "/n El fichero con nombre: " << nombreFichero << " ha sido encontrado, y se ha modificado en los siguientes commits: " << endl;
			for (int i = 0; i < commitFicheroMod.size(); i++) {
				cout << commitFicheroMod[i]->getMensaje() << endl;
			}
			char borrar;
			do {
				cout << "¿Desea usted borrar el fichero? Introduzca (S / N): " << endl;
				cin >> borrar;
			} while (borrar != 'S' && borrar != 'N' && borrar != 's' && borrar != 'n');
			if (borrar == 'S' || borrar == 's') {
				git.eliminarFichero(nombreFichero);
				cout << "El fichero ha sido borrado correctamente y todas sus referencias con los commits" << endl;
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
		cerr << "Excepcion: Error al leer el fichero" << error.what() << endl;
	}
}