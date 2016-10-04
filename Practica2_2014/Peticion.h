/* 
 * File:   Peticion.h
 * Author: macosx
 *
 * Created on 25 de septiembre de 2014, 18:27
 */
#include <cstdlib>
#include <string>

#ifndef PETICION_H
#define	PETICION_H
using namespace std;
class Peticion {

    int _cod;
    int _nPetic;

public:
	Peticion(int _cod);
	Peticion(const Peticion& orig);
	virtual ~Peticion();
        void AnadePeticion();
        void SetNPetic(int _nPetic);
        int GetNPetic() const;
        void SetCod(int _cod);
        int GetCod() const;
private:

};

#endif	/* PETICION_H */

