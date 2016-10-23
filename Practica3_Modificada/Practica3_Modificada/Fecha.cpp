#include "Fecha.h"
using namespace std;

#include <ctime>
#include <cstdio>
#include "Fecha.h"

const unsigned Fecha::diasMes[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Fecha::Fecha() {
	time_t tiempoActual;
	struct tm *fechaActual;

	time(&tiempoActual); // Obtener hora actual
	fechaActual = localtime(&tiempoActual); // Decodificar la hora en campos separados

	leerTiempo(*fechaActual);
}

Fecha::Fecha(unsigned aAnio, unsigned aMes, unsigned aDia, unsigned aHora, unsigned aMin, unsigned aSeg) {
	// Filtrado de fechas incorrectas
	comprobarFecha(aAnio, aMes, aDia, aHora, aMin, aSeg);
	anio = aAnio; mes = aMes; dia = aDia; hora = aHora; min = aMin; seg = aSeg;
}

void Fecha::asignarDia(unsigned aAnio, unsigned aMes, unsigned aDia) {
	comprobarFecha(aAnio, aMes, aDia, hora, min, seg);
	dia = aDia; mes = aMes; anio = aAnio;
}

void Fecha::asignarHora(unsigned aHora, unsigned aMin, unsigned aSeg) {
	comprobarFecha(dia, mes, anio, aHora, aMin, aSeg);
	hora = aHora; min = aMin; seg = aSeg;
}

bool Fecha::operator<=(const Fecha &f) {
	if (anio <= f.anio) {
		return true;
	}
	else if (anio > f.anio) {
		return false;
	}

	if (mes <= f.mes) {
		return true;
	}
	else if (mes > f.mes) {
		return false;
	}

	if (dia <= f.dia) {
		return true;
	} else if (dia > f.dia) {
		return false;
	}

	if (hora <= f.hora) {
		return true;
	} else if (hora > f.hora) {
		return false;
	}

	if (min <= f.min) {
		return true;
	}
	else if (min > f.min) {
		return false;
	}
	if (seg <= f.seg) {
		return true;
	}

	return false;
}

bool Fecha::operator>=(const Fecha &f) {
	if (anio >= f.anio) {
		return true;
	}
	else if (anio < f.anio) {
		return false;
	}

	if (mes >= f.mes) {
		return true;
	}
	else if (mes < f.mes) {
		return false;
	}

	if (dia >= f.dia) {
		return true;
	}
	else if (dia < f.dia) {
		return false;
	}

	if (hora >= f.hora) {
		return true;
	}
	else if (hora < f.hora) {
		return false;
	}

	if (min >= f.min) {
		return true;
	}
	else if (min >= f.min) {
		return false;
	}

	if (seg >= f.seg) {
		return true;
	}
	return false;
}

Fecha &Fecha::operator=(const Fecha &f){
	anio = f.anio; mes = f.mes; dia = f.dia; hora = f.hora; min = f.min; seg = f.seg;
	return *this;
}

void Fecha::anadirSeg(int numSeg) {
	struct tm fecha;

	escribirTiempo(fecha);
	fecha.tm_sec += numSeg;
	mktime(&fecha);
	leerTiempo(fecha);
}

void Fecha::anadirMin(int numMin){
	struct tm fecha;

	escribirTiempo(fecha);
	fecha.tm_min += numMin;
	mktime(&fecha);
	leerTiempo(fecha);
}

void Fecha::anadirHoras(int numHoras){
	struct tm fecha;

	escribirTiempo(fecha);
	fecha.tm_hour += numHoras;
	mktime(&fecha);
	leerTiempo(fecha);
}

void Fecha::anadirDias(int numDias){
	struct tm fecha;

	escribirTiempo(fecha);
	fecha.tm_mday += numDias;
	mktime(&fecha);
	leerTiempo(fecha);
}

void Fecha::anadirMeses(int numMeses){
	struct tm fecha;

	escribirTiempo(fecha);
	fecha.tm_mon += numMeses;
	mktime(&fecha);
	leerTiempo(fecha);
}

void Fecha::anadirAnios(int numAnios){
	struct tm fecha;

	escribirTiempo(fecha);
	fecha.tm_year += numAnios;
	mktime(&fecha);
	leerTiempo(fecha);
}

string Fecha::cadenaDia() const{
	char buffer[11];
	sprintf(buffer, "%u/%u/%u", anio, mes, dia);
	return string(buffer);
}


string Fecha::cadenaHora() const{
	char buffer[6];
	sprintf(buffer, "%u:%u:%u", hora, min, seg);
	return string(buffer);
}

Fecha::~Fecha(){
}

void Fecha::comprobarFecha(unsigned aAnio, unsigned aMes, unsigned aDia, unsigned aHora, unsigned aMin, unsigned aSeg) const{
	if (aSeg > 59 || aMin > 59 || aHora > 23) throw ErrorFechaIncorrecta();
	if (aMes < 1 || aMes > 12) throw ErrorFechaIncorrecta();
	if (aDia < 1 || aDia > diasMes[aMes - 1]) throw ErrorFechaIncorrecta();
	if (aDia == 29 && aMes == 2 && (aAnio % 4 != 0 || (aAnio % 100 == 0 && aAnio % 400 != 0))) throw ErrorFechaIncorrecta();
}

void Fecha::leerTiempo(const tm &t){
	anio = t.tm_year + 1900;
	mes = t.tm_mon + 1;
	dia = t.tm_mday;
	hora = t.tm_hour;
	min = t.tm_min;
	seg = t.tm_sec;
}

void Fecha::escribirTiempo(tm &t){
	t.tm_year = anio - 1900;
	t.tm_mon = mes - 1;
	t.tm_mday = dia;
	t.tm_hour = hora;
	t.tm_min = min;
	t.tm_sec = 0;
}

ostream &operator<<(ostream &os, const Fecha &f){
	os << f.cadena();
	return os;
}

