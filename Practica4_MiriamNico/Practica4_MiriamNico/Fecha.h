#ifndef FECHA_H
#define FECHA_H
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>
using namespace std;

/** @brief Excepción que representa fechas incorrectas */
class ErrorFechaIncorrecta : public std::domain_error {
public:
	ErrorFechaIncorrecta() : domain_error("Formato de fecha incorrecto") {
	}
};

/** @brief Clases sencilla para representar fechas y horas */
class Fecha {
	/** Fecha y hora */
	unsigned anio, mes, dia, hora, min, seg;
	/** Dias por mes */
	static const unsigned diasMes[12];

	/** Comprobación de validez de una fecha */
	void comprobarFecha(unsigned aAnio, unsigned aMes, unsigned aDia, unsigned aHora, unsigned aMin, unsigned aSeg) const;
	/** Función auxiliar de conversión desde estructura de tiempo tm de time.h */
	void leerTiempo(const tm &t);
	/** Función	auxiliar de conversión a estructura de tiempo tm de time.h */
	void escribirTiempo(tm &t);

public:
	/** Crea una fecha con la hora actual */
	Fecha();
	/** Crea una fecha concreta. Devuelve una excepción ErrorFechaIncorrecta si la fecha introducida no es correcta */
	Fecha(unsigned aAnio, unsigned aMes, unsigned aDia, unsigned aHora = 0, unsigned aMin = 0, unsigned aSeg = 0);
	/** Constructor copia */
	Fecha(const Fecha &f) :anio(f.anio), mes(f.mes), dia(f.dia), hora(f.hora), min(f.min), seg(f.seg) {};

	/** Asignar un nuevo día */
	void asignarDia(unsigned aAnio, unsigned aMes, unsigned aDia);
	/** Asignar una nueva hora */
	void asignarHora(unsigned aHora, unsigned aMin, unsigned aSeg);

	/** Obtener hora */
	unsigned verHora() const { return hora; }
	/** Obtener minutos */
	unsigned verMin() const { return min; }
	/** Obtener segundos */
	unsigned verSeg() const { return seg; }
	/** Obtener dia */
	unsigned verDia() const { return dia; }
	/** Obtener mes */
	unsigned verMes() const { return mes; }
	/** Obtener año */
	unsigned verAnio() const { return anio; }

	/** Obtener una cadena con el día */
	string cadenaDia() const;
	/** Obtener una cadena con la hora */
	string cadenaHora() const;
	/** Obtener una cadena con día y hora */
	string cadena() const {
		return cadenaDia() + " " + cadenaHora();
	}

	/** Indica si las dos fechas tienen el mismo día */
	bool mismoDia(const Fecha &f) const {
		return anio == f.anio && mes == f.mes && dia == f.dia;
	}
	/** Comparar fechas */
	bool operator<(const Fecha &f) const;
	bool operator==(const Fecha& f) const;
	bool operator!=(const Fecha& f) const;
	bool operator<=(const Fecha& f) const;
	bool operator>(const Fecha& f) const;
	bool operator>=(const Fecha& f) const;
	/** Asignar fechas */
	Fecha &operator=(const Fecha &f);

	/** Añadir un número de segundos indicado */
	void anadirSeg(int numSeg);
	/** Añadir un número de minutos indicado */
	void anadirMin(int numMin);
	/** Añadir un número de horas indicado*/
	void anadirHoras(int numHoras);
	/** Añadir un número de días indicado */
	void anadirDias(int numDias);
	/** Añadir un número de meses indicado */
	void anadirMeses(int numMeses);
	/** Añadir un nœmero de años indicado */
	void anadirAnios(int numAnios);

	~Fecha();

	/**Pasar a formato fecha*/
	void pasarFFecha(string marcaTiempo);
};

/** Serialización de fechas: salida */
ostream &operator<<(ostream &os, const Fecha &f);

#endif /**!FECHA_H*/

