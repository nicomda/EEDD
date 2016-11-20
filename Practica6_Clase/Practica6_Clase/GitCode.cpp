#include "GitCode.h"


GitCode::GitCode() :fileFichero(""), fileCommits(""), commits(), ficheros(), fichActuales(), mapCommit()
{
}


GitCode::~GitCode()
{
	commits.clear();
	ficheros.clear();
	fichActuales.clear();
	mapCommit.clear();
}



GitCode::GitCode(string afileFichero, string afileCommits) :fileFichero(afileFichero), fileCommits(afileCommits), commits(), ficheros(), fichActuales(), mapCommit(){
	cargaDeFichero(afileFichero);
	cargaDeCommit(afileCommits);
}
GitCode::GitCode(const GitCode& orig) : fileFichero(orig.fileFichero), fileCommits(orig.fileCommits), commits(orig.commits), ficheros(orig.ficheros), fichActuales(orig.fichActuales), mapCommit(orig.mapCommit){

}

bool GitCode::getCommit(string code, Commit& commit){
	/*	
	RefCommit rc(code);
	Nodo<RefCommit>* p;
	if (arbolCommit.buscar(rc, p)) {
		commit = (*(p->getDato().itc));
		return true;
	}
	return false;*/

	map<string, list<Commit>::iterator>::iterator imapCommit;
	imapCommit = mapCommit.find(code);
	if (imapCommit == mapCommit.end()) return false;
	commit = (*(*imapCommit).second);
	return true;
}
vector<Commit*> GitCode::getCommFechas(Fecha f1, Fecha f2){
	vector<Commit*> vCommits;
	list<Commit>::iterator icommits;
	icommits = commits.begin();

	while (icommits!=commits.end()){
		if ((*icommits).entreFechas(f1, f2)){
			vCommits.push_back(&(*icommits));
		}
		icommits++;
	}
	return vCommits;
}
vector<Commit*> GitCode::getCommFichero(string nombre){
	vector<Commit*> vCommits;
	list<Commit>::iterator icommits;
	icommits = commits.begin();
	while (icommits!=commits.end()){
		if ((*icommits).incluyeFichero(nombre))
			vCommits.push_back(&(*icommits));
		icommits++;
	}
	return vCommits;
}

/*
void GitCode::eliminarFichero(string nombre){
	
	list<Fichero>::iterator ificheros;
	ificheros = ficheros.begin();
	bool encontrado = false;
	while ((ificheros!=ficheros.end()) && !encontrado){
		if ((*ificheros).GetNombre()== nombre){
			encontrado = true;
		}
		else{
			ificheros++;
		}
		
	}

	if (encontrado){
		list<Commit>::iterator icommits ;
		icommits = commits.begin();
		while (icommits!=commits.end()){
			(*icommits).borrarFichero(nombre);
			icommits++;
		}
		ficheros.erase(ificheros);
	}
	
}
*/
void GitCode::cargaDeFichero(string fileFiche)
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
		//ficheros.push_back(f);
		try {
			nuevoFichero(f);

		}
		catch (ERROR_FICHERO_REPETIDO er) {
			cout << "El fichero ya se encuentra en el sistema";
			er.what();
		}
	}
		inputStream.close();
	
}

void GitCode::cargaDeCommit(string fileComm)
{
	string rutaFichero(fileComm);
	string lineaActual;
	list<Fichero>::iterator ificheros;
	ificheros = ficheros.begin();
	vector<string> nombresFicheros;
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
			nombresFicheros.push_back((*ificheros).GetNombre());
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
		nombresFicheros.push_back((*ificheros).GetNombre());
		//commit.addfichero(&(*ificheros));
		nuevoCommit(codigo, mensajeS, marcatiempo, nombresFicheros);
		//commits.push_back(commit);	
		//nuevoCommit(commit);
	}
	inputStream.close();
	
}
/*
void GitCode::nuevoCommit(Commit& c) {
	list<Commit>::iterator icommit;
	commits.push_back(c);
	icommit = commits.end();
	icommit--;
	RefCommit rc(c.getCodigo(), icommit);
	arbolCommit.insertarDato(rc);
}
void GitCode::borrarCommit(string cod) {
	RefCommit rc(cod);
	Nodo<RefCommit>* p;
	if (!arbolCommit.buscar(rc, p)) {
		throw ERROR_COMMIT_NOENCONTRADO();
	}
	commits.erase(p->getDato().itc);
	arbolCommit.borraDato(rc);
}
string GitCode::getStatus() {
	string estado = "";
	estado = "Num Hojas: " + arbolCommit.numHojasArbol();
	estado += "-- Altura: " + arbolCommit.alturaArbol();
	estado+="-- Num elementos: " + arbolCommit.numElementos();
	return estado;
}
*/
void GitCode::nuevoFichero(Fichero& fichero) {
	pair<string, Fichero*> pFich;
	map<string, Fichero*>::iterator iEnc;
	list<Fichero>::iterator ificheros;
	iEnc = fichActuales.find(fichero.GetNombre());
	if (iEnc == fichActuales.end()) {
		ficheros.push_back(fichero);
		ificheros = ficheros.end();
		ificheros--;
		pFich.first = fichero.GetNombre();
		pFich.second = &(*ificheros);
		fichActuales.insert(pFich);
	}
	else {
		throw ERROR_FICHERO_REPETIDO();
	}
}

vector<Fichero*> GitCode::getFicherosActuales() {
	vector<Fichero*> ficherosActuales;
	map<string, Fichero*>::iterator ifichAct = fichActuales.begin();
	while (ifichAct != fichActuales.end()) {
		ficherosActuales.push_back((*ifichAct).second);
		ifichAct++;
	}
	return ficherosActuales;
}

Fichero* GitCode::buscarFichero(string nombre) {
	map<string, Fichero*>::iterator iEnc;
	list<Fichero>::iterator ificheros;
	iEnc = fichActuales.find(nombre);
	if (iEnc != fichActuales.end()) {
		return (*iEnc).second;
	}
	return NULL;
}

void GitCode::nuevoCommit(string codigo, string texto, string marcatiempo, vector<string> fich) {
	Commit commit(codigo, marcatiempo, texto);
	Fichero* enc=0;
	map<string, list<Commit>::iterator>::iterator imapCommit;
	imapCommit = mapCommit.find(codigo);
	if (imapCommit != mapCommit.end()) throw ERROR_COMMIT_REPETIDO();
	
	vector<string>::iterator inomFich = fich.begin();
	while (inomFich != fich.end()) {
		enc = buscarFichero(*inomFich);
		if (enc) {
			commit.addfichero(enc);
		}
		inomFich++;
	}
	list<Commit>::iterator icommit;
	commits.push_back(commit);
	icommit = commits.end();
	icommit--;
	pair<string, list<Commit>::iterator> pMapCommit;
	pMapCommit.first = codigo;
	pMapCommit.second = icommit;
	mapCommit.insert(pMapCommit);
}

void GitCode::borrarFichero(string nombre) {
	fichActuales.erase(nombre);
}


void GitCode::borrarCommit(string codigo) {
	map<string, list<Commit>::iterator>::iterator imapCommit;
	imapCommit=mapCommit.find(codigo);
	if (imapCommit == mapCommit.end()) throw ERROR_COMMIT_NOENCONTRADO();
	commits.erase((*imapCommit).second);
	mapCommit.erase(codigo);
}