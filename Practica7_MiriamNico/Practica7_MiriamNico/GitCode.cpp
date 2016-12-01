#include "GitCode.h"



GitCode::GitCode(string mfileFichero, string mfileCommits) :fileFichero(mfileFichero), fileCommits(mfileCommits), commits(), ficheros(), ficherosActivos(TAM){
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
		//Parseamos la linea
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
		auto marcatiempo = lineaActual.substr(pos + 1, 14);
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
			commit.addFichero(&(*ificheros));
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
		commit.addFichero(&(*ificheros));
		nuevoCommit(commit);
	}
	inputStream.close();
}

template<class T>
unsigned long GitCode::djb2(string mstring) {
	unsigned long hash = 5381;
	int c;
	for (int i = 0; i < str.length(); i++) {
		c = str[i];
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}


bool GitCode::getCommit(string mcodigo, Commit& mcommit) {
	RefCommit refcommi;
	refcommi.setCodCommit(mcodigo);
	unsigned long mclave = djb2(refcommi.getCodCommit());
	RefCommit *encontrado = commitsPorClave.buscar(mclave, refcommi);
	if (encontrado) {
		mcommit = (*(*encontrado).itc);
		return true;
	}
	return false;
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

void GitCode::nuevoCommit(Commit mcommit) {
	RefCommit tabla;
	tabla.setCodCommit(mcommit.getCodigo());
	unsigned long mclave = djb2(tabla.getCodCommit());
	RefCommit *encontrado = commitsPorClave.buscar(mclave, tabla);
	if (!encontrado) {
		commits.push_back(mcommit);
		list<Commit>::iterator icommit = commits.end();
		icommit--;
		tabla.itc = icommit;
		commitsPorClave.insertar(mclave, tabla);
	}
	else throw ERROR_DATO_YA_INSERTADO();
}

void GitCode::borraCommit(string mcodigo){
	RefCommit tabla;
	tabla.setCodCommit(mcodigo);
	unsigned long mclave = djb2(tabla.getCodCommit());
	RefCommit *encontrado = commitsPorClave.buscar(mclave, tabla);
	if (encontrado) {
		commits.erase(encontrado->itc);
		commitsPorClave.eliminar(mclave, *encontrado);
	}
	else throw ERROR_COMMIT_NO_ENCONTRADO();
}

string GitCode::getStatus()
{
	return string();
}

/*list<Fichero*> GitCode::getFicherosActivos(){
	list<Fichero*> ficheroActivo;
	list<Fichero*>::iterator iFicherosActivos;
	iFicherosActivos = ficheroActivo.begin();
	int tam = ficherosActivos.getTamaTabla();
	while (iFicherosActivos < tam){
		ficheroActivo.push_back((*iFicherosActivos));
		iFicherosActivos++;
	}
	return ficheroActivo;
}*/

void GitCode::nuevoFichero(Fichero &mfichero){
	ficheros.push_back(mfichero);
}

void GitCode::borraFichero(string mnombre) {
	list<Fichero>::iterator ificheros;
	ificheros = ficheros.begin();
	bool encontrado = false;
	while ((ificheros != ficheros.end()) && !encontrado) {
		if ((*ificheros).getNombre() == mnombre) {
			encontrado = true;
		}
		else {
			ificheros++;
		}
	}
	if (encontrado) {
		list<Commit>::iterator icommits;
		icommits = commits.begin();
		while (icommits != commits.end()) {
			(*icommits).eliminarFichero(mnombre);
			icommits++;
	}
		ficheros.erase(ificheros);
	}
}
