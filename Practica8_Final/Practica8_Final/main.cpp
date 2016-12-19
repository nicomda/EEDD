#include <iostream>
#include <string>
#include "ClubLectura.h"
#include "Excepciones.h"
#include "Lector.h"
#include "Valoracion.h"
#include "Libro.h"
#include <vector>

int main() {
	try {
		ClubLectura clubLectura;
		clubLectura.cargarDatos();
		Lector* lector = clubLectura.buscarLector("phenix");
		vector<Libro*> vLibrosLeidos = lector->librosLeidos();
		vector<Libro*>::iterator iLibros = vLibrosLeidos.begin();
		char tecla;
		cout << "La lista de libros leidos por el usuario 'phenix' son: " << endl;
		while (iLibros != vLibrosLeidos.end()) {
			(*iLibros)->getInformacion();
			iLibros++;
		}
		cout << "Pulse cualquier tecla para continuar..." << endl;
		cin >> tecla;
		cout << "___________________________________________________________________________________________" << endl;
		vector<Libro*> vLibrosRecomendados = lector->librosRecomendados();
		cout << "La lista de libros afines por el usuario 'phenix' son: " << endl;
		for (int i = 0; i < vLibrosRecomendados.size(); i++) {
			vLibrosRecomendados[i]->getInformacion();
		}
		cout << "Pulse cualquier tecla para continuar... " << endl;
		cin >> tecla;
		cout << "___________________________________________________________________________________________" << endl;
		Libro* masLeidoGlobalmente = clubLectura.libroMasLeido();
		cout << "El libro mas leido globalmente es: " << endl;
		masLeidoGlobalmente->getInformacion();
		cout << "Pulse cualquier tecla para continuar..." << endl;
		cin >> tecla;
		cout << "___________________________________________________________________________________________" << endl;
		Libro* afines = clubLectura.buscarLibro(1378);
		vector<Libro*> vlibrosAfines = clubLectura.librosAfines(afines);
		cout << "Los libros afines al libro 'El lobo Estepario' son: " << endl;
		for (int i = 0; i < vlibrosAfines.size(); i++) {
			vlibrosAfines[i]->getInformacion();
		}
		cout << "Gracias por utilizar nuestro programa. Que tenga buen dia. " << endl;
		system("PAUSE");
	}
	catch (ERROR_PUNTUACION_FUERA_DE_RANGO &error) {
		cerr << "Exception: " << error.what() << endl;

	}
	catch (ERROR_LIBRO_YA_VALORADO &error) {
		cerr << "Exception: " << error.what() << endl;
	}
	catch (std::ifstream::failure &error) {
		cerr << "Exception: Error al cargar los ficheros. " << error.what() << endl;
	}

}