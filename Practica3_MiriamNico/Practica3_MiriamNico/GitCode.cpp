#include "GitCode.h"


GitCode::GitCode() :fileFichero(""), fileCommits(""), commits(), ficheros() {

}

GitCode::GitCode(string afileFichero, string afileCommits) :fileFichero(afileFichero), fileCommits(afileCommits), commits(), ficheros() {
	cargarFichero(afileFichero);
	cargarCommit(afileCommits);
}
GitCode::GitCode(const GitCode& orig) : fileFichero(orig.fileFichero), fileCommits(orig.fileCommits), commits(orig.commits), ficheros(orig.ficheros) {

}

GitCode::~GitCode() {
	Iterador<Commit> i = commits.iteradorInicio();
	while (i.existe()) {
		commits.borrar(i);
		i = commits.iteradorInicio();
	}
	Iterador<Fichero> j = ficheros.iteradorInicio();
	while (j.existe()) {
		ficheros.borrar(j);
		j = ficheros.iteradorInicio();
	}
}

void GitCode::cargarFichero(string fileFiche)
{
	string rutaFichero(fileFiche);
	string lineaActual;

	std::ifstream inputStream;
	inputStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	inputStream.open(rutaFichero);
	// Extraemos la cabecera del fichero
	inputStream >> lineaActual;
	while (!inputStream.eof()) {
		inputStream >> lineaActual;
		// Parseamos la linea
		auto pos = lineaActual.find(';');
		auto ruta = lineaActual.substr(0, pos);
		auto tama = lineaActual.substr(pos + 1, lineaActual.length());
		// Separamos la ubicacion del nombre del fichero
		pos = ruta.find_last_of('/');
		auto ubicacion = ruta.substr(0, pos + 1);
		auto nombre = ruta.substr(pos + 1, ruta.length());
		// Convertimos el string a int
		auto tamaBytes = std::stoi(tama);
		Fichero f(nombre, ubicacion, tamaBytes);
		ficheros.insertarFinal(f);
	}
	inputStream.close();

}

void GitCode::cargarCommit(string fileComm)
{
	string rutaFichero(fileComm);
	string lineaActual;
	Iterador<Fichero> i;

	std::ifstream inputStream;
	inputStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	inputStream.open(rutaFichero);
	// Extraemos la cabecera del fichero
	getline(inputStream, lineaActual);
	//inputStream >> lineaActual;
	while (!inputStream.eof()) {
		//inputStream >> lineaActual;
		getline(inputStream, lineaActual);
		// Parseamos la linea
		auto pos = lineaActual.find(';');
		auto codigo = lineaActual.substr(0, pos);
		//auto posF = lineaActual.find(';');
		auto marcatiempo = lineaActual.substr(pos + 1, 14);
		//double marcaT = std::stoi(marcatiempo);
		pos += 16;

		auto mensaje = lineaActual.substr(pos, lineaActual.length());
		pos = mensaje.find(';');
		auto mensajeS = mensaje.substr(0, pos);
		auto numFicheros = mensaje.substr(pos + 1, mensaje.length());
		Commit commit(codigo, marcatiempo, mensajeS);

		// Separamos los ficheros por el la ","
		int tamFin = numFicheros.length();
		pos = numFicheros.find(',');
		int inicio = 0;
		bool fin = false;
		while (pos<tamFin) {
			auto numF = numFicheros.substr(inicio, pos);
			int posF = std::stoi(numF);
			posF--;
			i = ficheros.iteradorInicio();
			int j = 0;
			while (j < posF) {
				j++;
				i = i.siguiente();
			}
			commit.addFichero(&i.getDato());
			inicio = pos + 1;
			numFicheros = numFicheros.substr(inicio, numFicheros.length());
			tamFin = numFicheros.length();
			inicio = 0;
			pos = numFicheros.find(',');
		}
		auto numF = numFicheros.substr(inicio, numFicheros.length());
		int posF = std::stoi(numF);
		posF--;
		i = ficheros.iteradorInicio();
		int j = 0;
		while (j < posF) {
			j++;
			i = i.siguiente();
		}
		commit.addFichero(&i.getDato());
		commits.insertarFinal(commit);
	}
	inputStream.close();

}

bool GitCode::getCommit(string code, Commit& commit) {
	Iterador<Commit> i = commits.iteradorInicio();

	while (i.existe()) {
		if (i.getDato().GetCodigo() == code) {
			commit = i.getDato();
			return true;
		}
		else {
			i = i.siguiente();
		}
	}
	return false;
}
VDinamico<Commit*> GitCode::getCommitFechas(Fecha f1, Fecha f2) {
	VDinamico<Commit*> vCommits;
	Iterador<Commit> i = commits.iteradorInicio();

	while (i.existe()) {
		if (i.getDato().entreFechas(f1, f2)) {
			vCommits.insertar(&(i.getDato()), UINT_MAX);
		}
		i = i.siguiente();
	}
	return vCommits;
}

VDinamico<Commit*> GitCode::getCommitFichero(string nombre) {
	VDinamico<Commit*> vCommits;
	Iterador<Commit> i = commits.iteradorInicio();

	while (i.existe()) {
		if (i.getDato().incluyeFichero(nombre))
			vCommits.insertar(&(i.getDato()), UINT_MAX);
		i = i.siguiente();
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
		j = j.siguiente();
	}

	if (encontrado) {
		Iterador<Commit> i = commits.iteradorInicio();
		while (i.existe()) {
			i.getDato().borrarFichero(nombre);
			i = i.siguiente();
		}
		ficheros.borrar(j);
	}

}


