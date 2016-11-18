#include "GitCode.h"



GitCode::GitCode(string mfileFichero, string mfileCommits) :fileFichero(mfileFichero), fileCommits(mfileCommits), commits(), ficheros(), commitsPorClave() {
	cargarFichero(mfileFichero);
	cargarCommits(mfileCommits);
}

GitCode::GitCode(const GitCode& orig) : fileFichero(orig.fileFichero), fileCommits(orig.fileCommits), commits(orig.commits), ficheros(orig.ficheros), commitsPorClave(orig.commitsPorClave) {
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
		ficheros.push_back(fichero);
	}
	inputStream.close();
}

void GitCode::cargarCommits(string mfileCommits) {
	string rutaFichero(mfileCommits);
	string lineaActual;
	vector<Fichero>::iterator ifichero;
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
		while (tam > pos) {
			auto numFich = numeroFich.substr(inicio, pos);
			int posFich = std::stoi(numFich);
			posFich--;
			ifichero = ficheros.begin();
			int i = 0;
			while (i < posFich) {
				i++;
				ifichero++;
			}
			commit.addFichero(&(*ifichero));
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
		commit.addFichero(&(*ifichero));
		commits.push_back(commit);

		//Nuevo codigo del Arbol.
		list<Commit>::iterator iCommits;
		iCommits = commits.end();
		iCommits--;
		RefCommit refArbol(commit.getCodigo(), iCommits);
		commitsPorClave.insertar(refArbol);

	}
	inputStream.close();
}

bool GitCode::getCommit(string mcodigo, Commit& commit) {
	list<Commit>::iterator icommit;
	icommit = commits.begin();
	while (icommit != commits.end()) {
		if ((*icommit).getCodigo() == mcodigo) {
			commit = *icommit;
			return true;
		}
		else {
			icommit++;
		}
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

void GitCode::eliminarFichero(string mnombre) {
	vector<Fichero>::iterator ifichero;
	ifichero = ficheros.begin();
	bool encontrado = false;
	while (ifichero != ficheros.end() && !encontrado) {
		if ((*ifichero).getNombre() == mnombre) {
			encontrado = true;
		}
		ifichero++;
	}
	if (encontrado) {
		list<Commit>::iterator icommit;
		icommit = commits.begin();
		while (icommit != commits.end()) {
			(*icommit).eliminarFichero(mnombre);
			icommit++;
		}
		ficheros.erase(ifichero);
	}
}



void GitCode::nuevoCommit(RefCommit commit) {
	if (commitsPorClave.buscar(commit)) throw ERROR_DATO_YA_INSERTADO();
	else {
		commitsPorClave.insertar(commit);
	}

}

bool GitCode::borrarCommit(string commit) {
	list<Commit>::iterator itc;
	itc = commits.begin();
	RefCommit arbol(commit, itc);
	if (commitsPorClave.eliminar(arbol)) {
		return true;
	}
	return false;
}

string GitCode::getStatus() {

	return string();
}
