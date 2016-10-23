#include "Excepciones.h"
#include "Fecha.h"
#include "Commit.h"
#include "Fichero.h"
#include "NodoIterador.h"
#include "ListaDEnlazada.h"
#include "GitCode.h"
#include "VDinamico.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

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