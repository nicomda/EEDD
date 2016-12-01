#include "GitCode.h"



GitCode::GitCode(string mfileFichero, string mfileCommits) :fileFichero(mfileFichero), fileCommits(mfileCommits), commits(), ficheros(), ficherosActivos(){
	cargarFichero(mfileFichero);
	cargarCommits(mfileCommits);
}

GitCode::GitCode(const GitCode& orig) : fileFichero(orig.fileFichero), fileCommits(orig.fileCommits), commits(orig.commits), ficheros(orig.ficheros), ficherosActivos(orig.ficherosActivos) {
	cargarFichero(orig.fileFichero);
	cargarCommits(orig.fileCommits);
}

GitCode::~GitCode() {
	commits.clear();
	ficheros.clear();
	
}

void GitCode::cargarFichero(string mfileFichero) {
	string rutaFichero(mfileFichero);
	string lineaActual;
	std::ifstream inputStream;
	inputStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	inputStream.open(rutaFichero);

	//Extraemos la cabecera del fichero
	inputStream >> lineaActual;
	while (!inputStream.eof()) {
		inputStream >> lineaActual;

		//Parseamos la l�nea
		auto pos = lineaActual.find(';');
		auto ruta = lineaActual.substr(0, pos);
		auto tama = lineaActual.substr(pos + 1, lineaActual.length());
		//Separamos la ubicaci�n del nombre del fichero
		pos = ruta.find_last_of('/');
		auto ubicacion = ruta.substr(0, pos + 1);
		auto nombre = ruta.substr(pos + 1, ruta.length());
		//Convertimos el string en un int
		int tamaB = std::stoi(tama);
		Fichero fichero(nombre, ubicacion, tamaB);
		try {
			nuevoFichero(fichero);
		}
		catch (ERROR_FICHERO_REPETIDO &error) {
			cerr << "Excepcion: " << error.what() << endl;
		}
	}
	inputStream.close();
}

void GitCode::cargarCommits(string mfileCommits) {
	string rutaFichero(mfileCommits);
	string lineaActual;
	list<Fichero>::iterator ificheros;
	ificheros = ficheros.begin();
	list<string> nombresFicheros;
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
		//Commit commit(codigo, marcatiempo, mensajeS);

		// Separamos los ficheros por el la ","
		int tamFin = numFicheros.length();
		pos = numFicheros.find(',');
		int inicio = 0;
		bool fin = false;
		while (pos<tamFin){
			auto numF = numFicheros.substr(inicio, pos);
			int posF = std::stoi(numF);
			posF--;
			ificheros = ficheros.begin();
			int j = 0;
			while (j < posF){
				j++;
				ificheros++;
			}
			nombresFicheros.push_back((*ificheros).getNombre());
			//commit.addfichero(&(*ificheros));
			inicio = pos + 1;
			numFicheros = numFicheros.substr(inicio, numFicheros.length());
			tamFin = numFicheros.length();
			inicio = 0;
			pos = numFicheros.find(',');
		}
		auto numF = numFicheros.substr(inicio, numFicheros.length());
		int posF = std::stoi(numF);
		posF--;
		ificheros = ficheros.begin();
		int j = 0;
		while (j < posF){
			j++;
			ificheros++;
		}
		nombresFicheros.push_back((*ificheros).getNombre());
		//commit.addfichero(&(*ificheros));
		nuevoCommit();
		//commits.push_back(commit);	
		//nuevoCommit(commit);
	}
	inputStream.close();
}

Fichero* GitCode::buscarFichero(string mnombre){

}

bool GitCode::getCommit(string mcodigo, Commit& mcommit) {
	
}

list<Commit*> GitCode::getCommitFechas(Fecha inicio, Fecha fin) {
	list<Commit*> vCommits;
	list<Commit>::iterator icommit;
	icommit = commits.begin();
	while (icommit != commits.end()) {
		if ((*icommit).entreDosFechas(inicio, fin)) {
			vCommits.push_back(&(*icommit));
		}
		icommit++;
	}
	return vCommits;
}

list<Commit*> GitCode::getCommitFichero(string mnombre) {
	list<Commit*> vCommits;
	list<Commit>::iterator icommit;
	icommit = commits.begin();
	while (icommit != commits.end()) {
		if ((*icommit).tieneFichero(mnombre)) {
			vCommits.push_back(&(*icommit));
		}
		icommit++;
	}
	return vCommits;
}

void GitCode::nuevoCommit(Commit mcommit) {
	list<Commit>::iterator itc;
	commits.push_back(mcommit);
	itc = commits.end();
	itc--;
	RefCommit tabla(mcommit.getCodigo(), itc);
	float clave = commitsPorClave.djb2(tabla.getCodCommit());
	if (commitsPorClave.buscar(clave,tabla) throw ERROR_DATO_YA_INSERTADO();
	else {
		commitsPorClave.insertar(arbol);
	}
}

void GitCode::borraCommit(string mcodigo)
{
}

string GitCode::getStatus()
{
	return string();
}

void GitCode::nuevoFichero(Fichero & mfichero)
{
}

void GitCode::borraFichero(string mnombre)
{
}
