#include "GitCode.h"



GitCode::GitCode(string mfileFichero, string mfileCommits) :fileFichero(mfileFichero), fileCommits(mfileCommits), commits(), ficheros(), ficherosActivos(), mapCommits() {
	cargarFichero(mfileFichero);
	cargarCommits(mfileCommits);
}

GitCode::GitCode(const GitCode& orig) : fileFichero(orig.fileFichero), fileCommits(orig.fileCommits), commits(orig.commits), ficheros(orig.ficheros), ficherosActivos(orig.ficherosActivos), mapCommits(orig.mapCommits) {
	cargarFichero(orig.fileFichero);
	cargarCommits(orig.fileCommits);
}

GitCode::~GitCode() {
	commits.clear();
	ficheros.clear();
	ficherosActivos.clear();
	mapCommits.clear();
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

		//Parseamos la línea
		auto pos = lineaActual.find(';');
		auto ruta = lineaActual.substr(0, pos);
		auto tama = lineaActual.substr(pos + 1, lineaActual.length());
		//Separamos la ubicación del nombre del fichero
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
	vector<Fichero>::iterator ifichero;
	ifichero = ficheros.begin();
	//Como se pedia un vector en vez de el set implementamos el vector
	vector<string> nombreFicheros;

	std::ifstream inputStream;
	inputStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	inputStream.open(rutaFichero);
	//Extraemos la cabecera del fichero.
	getline(inputStream, lineaActual);

	while (!inputStream.eof()) {
		getline(inputStream, lineaActual);
		//Parseamos la linea.
		auto pos = lineaActual.find(';');
		auto codigo = lineaActual.substr(0, pos);
		auto marcaT = lineaActual.substr(pos + 1, 14);
		pos += 16;

		auto mensaje = lineaActual.substr(pos, lineaActual.length());
		pos = mensaje.find(';');
		auto mensajes = mensaje.substr(0, pos);
		auto numeroFich = mensaje.substr(pos + 1, mensaje.length());
		Commit commit(codigo, marcaT, mensajes);

		//Separamos los ficheros por la ","
		int tam = numeroFich.length();
		pos = numeroFich.find(',');
		int inicio = 0;
		bool fin = false;
		while (pos < tam) {
			auto numFich = numeroFich.substr(inicio, pos);
			int posFich = std::stoi(numFich);
			posFich--;
			ifichero = ficheros.begin();
			int i = 0;
			while (i < posFich) {
				i++;
				ifichero++;
			}
			nombreFicheros.push_back((*ifichero).getNombre());
			inicio = pos + 1;
			numeroFich = numeroFich.substr(inicio, numeroFich.length());
			tam = numeroFich.length();
			inicio = 0;
			pos = numeroFich.find(',');
		}
		auto numF = numeroFich.substr(inicio, numeroFich.length());
		int posF = std::stoi(numF);
		posF--;
		ifichero = ficheros.begin();
		int j = 0;
		while (j < posF) {
			j++;
			ifichero++;
		}
		nombreFicheros.push_back((*ifichero).getNombre());
		nuevoCommit(codigo, mensajes, marcaT, nombreFicheros);
	}
	inputStream.close();
}

Fichero * GitCode::buscarFichero(string mnombre){
	map<string, Fichero*>::iterator iEncontrado;
	vector<Fichero>::iterator ificheros;
	iEncontrado = ficherosActivos.find(mnombre);
	if (iEncontrado != ficherosActivos.end()) {
		return (*iEncontrado).second;
	}
	return NULL;
}

bool GitCode::getCommit(string mcodigo, Commit& mcommit) {
	map<string, list<Commit>::iterator>::iterator imapCommit;
	imapCommit = mapCommits.find(mcodigo);
	if (imapCommit == mapCommits.end()) {
		return false;
	}
	mcommit = (*(*imapCommit).second);
	return true;
}

vector<Commit*> GitCode::getCommitFechas(Fecha inicio, Fecha fin) {
	vector<Commit*> vCommits;
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

vector<Commit*> GitCode::getCommitFichero(string mnombre) {
	vector<Commit*> vCommits;
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

void GitCode::nuevoCommit(string mcodigo, string mmarcadetiempo, string mmensaje, vector<string> mficheros){
	Commit commit(mcodigo, mmarcadetiempo, mmensaje);
	Fichero* encontrado = 0;
	map<string, list<Commit>::iterator>::iterator imapCommit;
	imapCommit = mapCommits.find(mcodigo);
	if (imapCommit != mapCommits.end()) throw ERROR_COMMIT_REPETIDO();
	vector<string>::iterator inombreFichero = mficheros.begin();
	while (inombreFichero != mficheros.end()) {
		encontrado = buscarFichero(*inombreFichero);
		if (encontrado) {
			commit.addFichero(encontrado);
		}
		inombreFichero++;
	}
	list<Commit>::iterator iCommit;
	commits.push_back(commit);
	iCommit = commits.end();
	iCommit--;
	pair<string, list<Commit>::iterator> pairmapCommit;
	pairmapCommit.first = mcodigo;
	pairmapCommit.second = iCommit;
	mapCommits.insert(pairmapCommit);
}

void GitCode::borraCommit(string mcodigo){
	map<string, list<Commit>::iterator>::iterator imapCommit;
	imapCommit = mapCommits.find(mcodigo);
	if (imapCommit == mapCommits.end()) throw ERROR_COMMIT_NO_ENCONTRADO();
	commits.erase((*imapCommit).second);
	mapCommits.erase(mcodigo);
}

vector<Fichero*> GitCode::getFicherosActivos(){
	vector<Fichero*> ficheroActivo;
	map<string, Fichero*>::iterator iFicherosActivos = ficherosActivos.begin();
	while (iFicherosActivos != ficherosActivos.end()) {
		ficheroActivo.push_back((*iFicherosActivos).second);
		iFicherosActivos++;
	}
	return ficheroActivo;
}

void GitCode::nuevoFichero(Fichero& mfichero){
	pair<string, Fichero*> pairFichero;
	map<string, Fichero*>::iterator iEncontrado;
	vector<Fichero>::iterator iFicheros;
	iEncontrado = ficherosActivos.find(mfichero.getNombre());
	if (iEncontrado == ficherosActivos.end()) {
		ficheros.push_back(mfichero);
		iFicheros = ficheros.end();
		iFicheros--;

		pairFichero.first = mfichero.getNombre();
		pairFichero.second = &(*iFicheros);
		ficherosActivos.insert(pairFichero);
	}
	else {
		throw ERROR_FICHERO_REPETIDO();
	}
}

void GitCode::borraFichero(string mnombre){
	ficherosActivos.erase(mnombre);
}
