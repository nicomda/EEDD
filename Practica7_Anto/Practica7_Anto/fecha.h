#ifndef FECHA_H
#define FECHA_H
#include <ctime>
#include<string>
#include "Excepciones.h"
using namespace std;

class Fecha{

public:
	Fecha();
	Fecha (short dia, short mes, short anio, short hora, short minuto, short segundo);
	Fecha(const Fecha& orig); 
	bool esCorrecta() const;
	void setDia(short dia);
	short getDia() const;
	void setMes(short mes);
	short getMes() const;
	void setAnio(short anio);
	short getAnio() const;
	void setHora(short hora);
	short getHora() const;
	void setMinuto(short minuto);
	short getMinuto() const;
	void setSegundo(short segundo);
	short getSegundo() const;
	bool anioBisiesto() const;
	bool operator==(const Fecha& f) const;
	bool operator!=(const Fecha& f) const;
	bool operator<(const Fecha& f) const;
	bool operator<=(const Fecha& f) const;
	bool operator>(const Fecha& f) const;
	bool operator>=(const Fecha& f) const;
	string getFecha();
	void pasarAFecha(string marcaT);
private:
	
	short dia;
	short mes;
	short anio;
	short hora;
	short minuto;
	short segundo;
};



#endif