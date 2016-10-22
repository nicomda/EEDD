#include "GitCode.h"



GitCode::GitCode() :fileFichero(""), fileCommits(""), commits(), ficheros(){

}

GitCode::GitCode(string ffileFichero, string cfileCommits) : fileFichero(ffileFichero),
fileCommits(cfileCommits), commits(), ficheros() {
	cargaDeFichero(ffileFichero);
	cargaDeCommit(cfileCommits);
}

GitCode::GitCode(const GitCode &orig) :fileFichero(orig.fileFichero),
fileCommits(orig.fileCommits), commits(orig.commits), ficheros(orig.ficheros) {

}

bool GitCode::getCommit(string code, Commit &commit) {
	Iterador<Commit> i = commits.iteradorInicio();
	while (i.existe) {
		if (i.getDato().GetCodigo() == code) {
			commit = i.getDato();
			return true;
		} else {
			i++;
		}
	}
	return false;
}

VDinamico<Commit> GitCode::getCommFechas(Fecha f1, Fecha f2){
	VDinamico<Commit> vCommits;
	Iterador <Commit> i = commits.iteradorInicio();
	while (i.existe()) {
		if (i.getDato().entreFechas(f1, f2)){
			vCommits.insertar(i.getDato(), UINT_MAX);
		}
		i++;
	}
	return vCommits;
}

VDinamico<Commit> GitCode::getCommFichero(string nombre) {
	VDinamico<Commit> vCommits;
	Iterador<Commit> i = commits.iteradorInicio();
	Iterador<Fichero> j = ficheros.iteradorInicio();
	bool encontrado = false;
	int cod = 1;
	while (j.existe() && !encontrado) {
		if (j.getDato().GetNombre() == nombre) {
			encontrado = true;
		}
		else {
			j++;
			cod++;
		}
	}

	int k = 1;
	while (i.existe() && k < cod) {
		i++;
	}
	if (i.getDato().incluyeFichero(nombre)) {
		vCommits.insertar(i.getDato(), UINT_MAX);
	}
	return vCommits;
}

void GitCode::eliminarFichero(string nombre) {
	Iterador<Fichero> j = ficheros.iteradorInicio();
	bool encontrado = false;
	while (j.existe() && !encontrado) {
		if (j.getDato().GetNombre() == nombre) {
			encontrado = true;
		}
	}

	if (encontrado) {
		Iterador<Commit> i = commits.iteradorInicio();
		while (i.existe()) {
			i.getDato().borrarFichero(nombre);
			i++;
		}
		ficheros.borrar(j);
	}
}
void GitCode::cargaDeFichero(string fileFiche) {
	string rutaFichero(fileFiche);
	string lineaActual;

	std::ifstream inputStream;
	inputStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	inputStream.open(rutaFichero);

	//Extraemos la cabecera del fichero
	inputStream >> lineaActual;
	while (!inputStream.eof()) {
		inputStream >> lineaActual;
		//Parseamos la línea.
		auto pos = lineaActual.find(';');
		auto ruta = lineaActual.substr(0, pos);
		auto tama = lineaActual.substr(pos + 1, lineaActual.length());

		//Separamos la ubicacion del nombre del fichero
		pos = ruta.find_last_of('/');
		auto ubicacion = ruta.substr(0, pos + 1);
		auto nombre = ruta.substr(pos + 1, ruta.length());

		//Convertimos el string a int.
		auto tamaBytes = std::stoi(tama);
		Fichero file(nombre, ubicacion, tamaBytes);
		ficheros.insertarFinal(file);
	}
	inputStream.close();
}

void GitCode::cargaDeCommit(string fileCommi) {
	string rutaFichero(fileCommi);
	string lineaActual;
	Iterador<Fichero> i;

	std::ifstream inputStream;
	inputStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	inputStream.open(rutaFichero);

	//Extraemos la cabecera del fichero.
	getline(inputStream, lineaActual);
	
	while (!inputStream.eof()) {
		getline(inputStream, lineaActual);
		//parseamos la linea
		auto pos = lineaActual.find(';');
		auto cod = lineaActual.substr(0, pos);
		auto marcatiempo = lineaActual.substr(pos + 1, 14);
		pos += 16;
		auto mensaje = lineaActual.substr(pos, lineaActual.length());
		pos = mensaje.find(';');
		auto mensajes = mensaje.substr(0, pos);
		auto numFicheros = mensaje.substr(pos + 1, mensaje.length());
		Commit commit(cod, marcatiempo, mensajes);

		//separamos los ficheros por comas
		int tamFin = numFicheros.length();
		pos = numFicheros.find(',');
		int inicio = 0;
		bool fin = false;
		while (pos < tamFin) {
			auto numF = numFicheros.substr(inicio, pos);
			int posF = std::stoi(numF);
			i = ficheros.iteradorInicio();
			int j = 0;
			while (j < posF) {
				j++;
				i++;
			}
			commit.addfichero(&i.getDato());
			inicio = pos + 1;
			numFicheros = numFicheros.substr(inicio, numFicheros.length());
			tamFin = numFicheros.length();
			inicio = 0;
			pos = numFicheros.find(',');
		}
		auto numF = numFicheros.substr(inicio, numFicheros.length());
		int posF = std::stoi(numF);
		i = ficheros.iteradorInicio();
		int j = 0;
		while (j < posF) {
			j++;
			i++;
		}
		commit.addfichero(&i.getDato());
		commits.insertarFinal(commit);

	}
	inputStream.close();
}
GitCode::~GitCode() {
}
