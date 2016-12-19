#include "ClubLectura.h"

void ClubLectura::cargarLibros(string archivoLibros) {
	string rutaFichero(archivoLibros);
	string lineaActual;
	pair<int, Libro> pairLibro;
	std::ifstream inputStream;
	pair<map<int, Libro>::iterator, bool> encontrado;
	list<int> repetidos;
	inputStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	inputStream.open(rutaFichero);
	int num = 1;
	try {
		while (!inputStream.eof()) {
			//Parseamos la linea.
			getline(inputStream, lineaActual);
			auto pos = lineaActual.find('|');
			auto id = lineaActual.substr(0, pos);
			auto mid = atoi(id.c_str());
			auto linea = lineaActual.substr(pos + 1, lineaActual.length());
			pos = linea.find_first_of('|');
			auto autor = linea.substr(0, pos);
			linea = linea.substr(pos + 1, linea.length());
			pos = linea.find_first_of('|');
			auto titulo = linea.substr(0, pos);
			auto tematica = linea.substr(pos + 1, linea.length());
			Libro libro(mid, autor, titulo, tematica);
			pairLibro.first = mid;
			pairLibro.second = libro;
			encontrado = libros.insert(pairLibro);
			if (!encontrado.second) repetidos.push_back(mid);
		}
	}
	catch (std::ifstream::failure& error) {
		cout << "Fin de la lectura de los libros." << endl;
	}
	inputStream.close();
}

void ClubLectura::cargarLectores(string archivoLectores) {
	string rutaFichero(archivoLectores);
	string lineaActual;
	pair<string, Lector> pairLector;
	pair<map<string, Lector>::iterator, bool> encontrado;
	list<string> repetidos;
	std::ifstream inputStream;
	Libro* libro;
	inputStream.exceptions(std::ifstream::failbit | std::istream::badbit);
	inputStream.open(rutaFichero);
	int num = 1;
	try {
		while (!inputStream.eof()) {
			//Parseamos la linea
			getline(inputStream, lineaActual);
			auto pos = lineaActual.find('|');
			auto alias = lineaActual.substr(0, pos);
			Lector lector(alias);
			auto puntuaciones = lineaActual.substr(pos + 1, lineaActual.length());
			pos = puntuaciones.find_first_of('-');

			bool fin;
			if (pos < puntuaciones.length()) fin = false;
			else fin = true;
			while (!fin) {
				auto id = puntuaciones.substr(0, pos);
				auto mid = atoi(id.c_str());
				auto puntos = puntuaciones.substr(pos + 2, 1);
				int mpuntos = atoi(puntos.c_str());
				libro = buscarLibro(mid);
				if (libro) {
					lector.nuevaValoracion(libro, mpuntos);
				}
				if (pos + 4 < puntuaciones.length()) {
					puntuaciones = puntuaciones.substr(pos + 4, puntuaciones.length());
					pos = puntuaciones.find_first_of('-');
				}
				else {
					fin = true;
				}

			}
			pairLector.first = alias;
			pairLector.second = lector;
			encontrado = lectores2.insert(pairLector);
			if (!encontrado.second) repetidos.push_back(alias);
		}
	}
	catch (std::ifstream::failure& error) {
		cout << "Fin de la lectura de los lectores." << endl;
	}
	inputStream.close();

}

void ClubLectura::cargarDatos(){
	cargarLibros("libros.csv");
	cargarLectores("usuarios.csv");
}

Libro * ClubLectura::libroMasLeido() {
	map<int, Libro>::iterator iLibros = libros.begin();
	int masValorado = (*iLibros).second.getNumValoraciones();
	map<int, Libro>::iterator imasValorado = iLibros;
	iLibros++;
	while (iLibros != libros.end()) {
		if ((*iLibros).second.getNumValoraciones() > masValorado) {
			masValorado = (*iLibros).second.getNumValoraciones();
			imasValorado = iLibros;
		}
		iLibros++;
	}
	return &(*imasValorado).second;
}

vector<Libro*> ClubLectura::librosAfines(Libro * libro) {
	Libro* leidos = NULL;
	map<string, Lector>::iterator iLectores = lectores2.begin();
	multimap<int, Libro*, greater<int>> librosRecomendados;
	vector<Libro*> libros;
	return libros;
}

Lector * ClubLectura::buscarLector(string malias){
	map<string, Lector>::iterator iLectores;
	iLectores = lectores2.find(malias);
	if (iLectores != lectores2.end()) return &(*iLectores).second;
	return nullptr;
}

Libro * ClubLectura::buscarLibro(int mid) {
	map<int, Libro>::iterator iLibros;
	pair<int, Libro> pairLibros;
	iLibros = libros.find(mid);
	if (iLibros != libros.end()) {
		return &(*iLibros).second;
	}
	return nullptr;
}
