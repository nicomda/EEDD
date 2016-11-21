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
#include "Nodo.h"
#include "ABB.h"
using namespace std;

int main(int argc, char** argv) {
	//try {
		GitCode git("ficheros2.txt", "commits.txt");
		Commit commit;
		list<Commit*> commits;
		list<Commit>::iterator iCommits;
		cout << "Introduce el codigo de un Commit que quiera insertar: " << endl;
		string codigo;
		cin >> codigo;
		bool insertado = false;
		cout << "Insertando commit en el arbol........... espere un momento.......... " << endl;
		if (!insertado) {
			
			//git.nuevoCommit();
		}
		if (insertado == true) {
			cout << "Commit insertado con exito en el arbol." << endl;
		}
		else {
			cout << "Commit ya existe en el arbol o no ha sido posible insertarlo, intentelo de nuevo mas tarde. " << endl;
		}



		cout << "Introduce el codigo de un Commit que quiera borrar: " << endl;
		cin >> codigo;

		cout << "Si quiere saber el estado del arbol pulse S / N: " << endl;
		char estado;
		cin >> estado;
		if (estado == 's' || estado == 'S') {
			git.getStatus();
		}
		else {
			cout << "FIN DEL PROGRAMA. QUE TENGA BUEN DIA................" << endl;
		}
		
	/*
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
	*/
}