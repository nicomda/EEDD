#include "fecha.h"

using namespace std;

Fecha::Fecha(){
	//dia = mes = anio = hora = minuto = segundo = 0;
}

Fecha::Fecha(const Fecha& orig) :
dia(orig.dia), mes(orig.mes), anio(orig.anio),
hora(orig.hora), minuto(orig.minuto), segundo(orig.segundo){

}

Fecha::Fecha(short dia, short mes, short anio,
	short hora, short minuto, short segundo) :
	dia(dia), mes(mes), anio(anio),
	hora(hora), minuto(minuto), segundo(segundo) {
	if (!esCorrecta()) {
		throw FECHA_NO_VALIDA();
	}
}


bool Fecha::esCorrecta() const {
	bool ok = anio >= 1 &&
		mes >= 1 && mes <= 12 &&
		hora >= 0 && hora<24 &&
		minuto >= 0 && minuto<60 &&
		segundo >= 0 && segundo<60;
	int dias;
	if (ok) {
		switch (mes) {
		case 2: dias = (anioBisiesto() ? 29 : 28); break;
		case 4: case 6: case 9: case 11: dias = 30; break;
		default: dias = 31; break;
		}
		ok = dia <= dias;
	}
	return ok;
}

void Fecha::setDia(short dia)  {
	short aux = this->dia;
	this->dia = dia;
	if (!esCorrecta()) {
		this->dia = aux;
		throw FECHA_NO_VALIDA();
	}
}

short Fecha::getDia() const { return dia; }

void Fecha::setMes(short mes)  {
	short aux = this->mes;
	this->mes = mes;
	if (!esCorrecta()) {
		this->mes = aux;
		throw FECHA_NO_VALIDA();
	}
}

short Fecha::getMes() const { return mes; }

void Fecha::setAnio(short anio){
	short aux = this->anio;
	this->anio = anio;
	if (!esCorrecta()) {
		this->anio = aux;
		throw FECHA_NO_VALIDA();
	}
}

short Fecha::getAnio() const { return anio; }

void Fecha::setHora(short hora)  {
	short aux = this->hora;
	this->hora = hora;
	if (!esCorrecta()) {
		this->hora = aux;
		throw FECHA_NO_VALIDA();
	}
}

short Fecha::getHora() const { return hora; }

void Fecha::setMinuto(short minuto) {
	short aux = this->minuto;
	this->minuto = minuto;
	if (!esCorrecta()) {
		this->minuto = aux;
		throw FECHA_NO_VALIDA();
	}
}

short Fecha::getMinuto() const { return minuto; }

void Fecha::setSegundo(short segundo){
	short aux = this->segundo;
	this->segundo = segundo;
	if (!esCorrecta()) {
		this->segundo = aux;
		throw FECHA_NO_VALIDA();
	}
}

short Fecha::getSegundo() const { return segundo; }


bool Fecha::anioBisiesto() const {
	return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
}

bool Fecha::operator==(const Fecha& f) const {
	return dia == f.dia && mes == f.mes && anio == f.anio &&
		hora == f.hora && minuto == f.minuto && segundo == f.segundo;
}

bool Fecha::operator!=(const Fecha& f) const {
	return !(*this == f);
}

bool Fecha::operator<(const Fecha& f) const {
	return anio<f.anio ||
		(anio == f.anio && mes<f.mes) ||
		(anio == f.anio && mes == f.mes && dia<f.dia) ||
		(anio == f.anio && mes == f.mes && dia == f.dia && hora<f.hora) ||
		(anio == f.anio && mes == f.mes && dia == f.dia && hora == f.hora && minuto<f.minuto) ||
		(anio == f.anio && mes == f.mes && dia == f.dia && hora == f.hora && minuto == f.minuto && segundo<f.segundo);
}

bool Fecha::operator<=(const Fecha& f) const {
	return *this<f || *this == f;
}

bool Fecha::operator>(const Fecha& f) const {
	return !(*this<f) && *this != f;
}

bool Fecha::operator>=(const Fecha& f) const {
	return *this>f || *this == f;
}
string Fecha::getFecha(){
	string cadena = to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio) + "-" + to_string(hora) + ":" + to_string(minuto) + ":" + to_string(segundo);
	return cadena;
}

//void Fecha::pasarAFecha(string marcaT){
//
//	anio = stoi(marcaT.substr(0, 4));
//	mes = stoi(marcaT.substr(3, 2));
//	dia = stoi(marcaT.substr(4, 2));
//	hora = stoi(marcaT.substr(7, 2));
//	minuto =stoi(marcaT.substr(9, 2));
//	segundo = stoi(marcaT.substr(11, 2));
//}