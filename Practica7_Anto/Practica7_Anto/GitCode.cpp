#include "GitCode.h"


GitCode::GitCode() :fileFichero(""), fileCommits(""), commits(), ficheros(), hashCommit(TAM)
{
}


GitCode::~GitCode()
{
	commits.clear();
	ficheros.clear();
}



GitCode::GitCode(string afileFichero, string afileCommits) :fileFichero(afileFichero), fileCommits(afileCommits), commits(), ficheros(), hashCommit(TAM){
	cargaDeFichero(afileFichero);
	cargaDeCommit(afileCommits);
}
GitCode::GitCode(const GitCode& orig) : fileFichero(orig.fileFichero), fileCommits(orig.fileCommits), commits(orig.commits), ficheros(orig.ficheros), hashCommit(orig.hashCommit){

}

bool GitCode::getCommit(string code, Commit& commit){
	RefCommit ref;
	ref.codigo = code;
	unsigned long clave = djb2(ref.codigo);
	RefCommit *enc = hashCommit.buscar(clave, ref);
	if (enc){
		commit = (*(*enc).itc);
		return true;
	}
	return false;
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
void GitCode::eliminarFichero(string nombre){
	
	vector<Fichero>::iterator ificheros;
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
		nuevoFichero(f);
	}
		inputStream.close();
	
}

void GitCode::cargaDeCommit(string fileComm)
{
	string rutaFichero(fileComm);
	string lineaActual;
	vector<Fichero>::iterator ificheros;
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
			commit.addfichero(&(*ificheros));
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
		commit.addfichero(&(*ificheros));
		//commits.push_back(commit);		
		nuevoCommit(commit);
	}
	inputStream.close();
	
}
void GitCode::nuevoCommit(Commit& c){
	RefCommit ref;
	ref.codigo = c.getCodigo();
	unsigned long clave = djb2(ref.codigo);
	RefCommit *enc = hashCommit.buscar(clave, ref);
	if (!enc){
		commits.push_back(c);
		list<Commit>::iterator icommits = commits.end();
		icommits--;
		ref.itc = icommits;
		hashCommit.insertar(clave, ref);
	}
	else throw ERROR_CLAVE_REPETIDA();

}
void GitCode::borrarCommit(string code){
	RefCommit ref;
	ref.codigo = code;
	unsigned long clave = djb2(ref.codigo);
	RefCommit *enc = hashCommit.buscar(clave, ref);
	if (enc){
		commits.erase(enc->itc);
		hashCommit.borrar(clave, *enc);
	}
	else{
		throw ERROR_DATO_NO_ENCONTRADO();
	}
}

unsigned long GitCode::djb2(string str) {
	unsigned long hash = 5381;
	int c;
	for (int i = 0; i < str.length(); i++){
		c = str[i];
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

void GitCode::nuevoFichero(Fichero f){
	ficheros.push_back(f);
}