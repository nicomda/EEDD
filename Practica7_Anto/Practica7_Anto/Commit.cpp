#include "Commit.h"


Commit::Commit() : fichModificados(), fecha()
{
	codigo = mensaje = marcaDeTiempo = "";

}


Commit::~Commit()
{	
}


Commit::Commit(string codigo, string marcaTiempo, string mensaje) : fichModificados(), fecha(){
	this->codigo = codigo;
	this->marcaDeTiempo = marcaTiempo;
	this->mensaje = mensaje;
	fecha.pasarAFecha(marcaDeTiempo);


}
Commit::Commit(const Commit& orig) :fichModificados(orig.fichModificados), fecha(orig.fecha){
	this->codigo = orig.codigo;
	this->marcaDeTiempo = orig.marcaDeTiempo;
	this->mensaje = orig.mensaje;
	//this->fecha = orig.fecha;
}

void Commit::addfichero(Fichero* f){
	fichModificados.push_back(f);
}
bool Commit::incluyeFichero(string nombre){
	list<Fichero*>::iterator ifichModificados;
	ifichModificados = fichModificados.begin();

	
	while (ifichModificados!=fichModificados.end()){
		if ((*ifichModificados)->GetNombre() == nombre) return true;
		ifichModificados++;
	}
	return false;
}

void Commit::borrarFichero(string codigo){
	list<Fichero *>::iterator ifichModificados;
	ifichModificados = fichModificados.begin();
	bool enc = false;
	while (!enc && ifichModificados != fichModificados.end()){
		if ((*ifichModificados)->GetNombre() == codigo){
			fichModificados.erase(ifichModificados);
			enc = true;
		}
		else{
			ifichModificados++;
		}
		
	}
}

bool Commit::entreFechas(Fecha fdesde, Fecha fhasta){

	return fecha >= fdesde && fecha <= fhasta;

}
