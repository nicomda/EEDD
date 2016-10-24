#include "Excepciones.h"
#include "Fichero.h"
#include "Commit.h"
#include "VDinamico.h"
#include "ListaDEnlazada.h"
#include "GitCode.h"
#include "fecha.h"
#include <string>

#include <iostream>
using namespace std;
	

void main(){

	try{
		
		GitCode gitcode("ficheros2.txt", "commits.txt");

		/*
		cout << "Introduce un código de Commit: ";
		string codigo;
		cin >> codigo;
		Commit commitEncontrado;
		bool encontrado = false;
		encontrado = gitcode.getCommit(codigo, commitEncontrado);

		if (!encontrado){
			cout << "El commit no se ha encontrado" << endl;
		}
		else{

			cout << "El commint encontrado es: " << commitEncontrado.getMensaje() << endl;
		}
		cout << "**********************************" << endl;
		cout << "Introduzca fecha de inicio: (yyyymmddhhmmss) ";
		string fechaDesde, fechaHasta;
		cin >> fechaDesde;
		cout << "Introduzca fecha de fin: (yyyymmddhhmmss) ";
		cin >> fechaHasta;
		cout << endl << "Los commints entre las fechas son: ";
		Fecha fdesde, fhasta;
		fdesde.pasarAFecha(fechaDesde);
		fhasta.pasarAFecha(fechaHasta);
		VDinamico<Commit*> commitsFechas;
		commitsFechas = gitcode.getCommFechas(fdesde, fhasta);
		for (int i = 0; i < commitsFechas.tam(); i++){
			if (commitsFechas[i]->entreFechas(fechaDesde, fechaHasta)){
				cout << commitsFechas[i]->getCadenaFecha() << "-->" << commitsFechas[i]->getMensaje() << endl;
			}
		}*/
		string nombreFichero;
		cout << "**********************************" << endl;
		cout << "Introduzca el codigo del fichero que quiere comprobar si ha sido modificado entre: ";
		cin>>nombreFichero;
		VDinamico<Commit*> commitsFichero;
		commitsFichero = gitcode.getCommFichero(nombreFichero);
		if (commitsFichero.tam() == 0){
			cout << "Fichero no encontrado" << endl;
		}
		else{
			cout << endl << "El fichero se ha modificado en los siguientes commints: " << endl;
			for (int i = 0; i < commitsFichero.tam(); i++){
				cout << commitsFichero[i]->getMensaje() << endl;				
			}
			char borra;
			do{
				
				cout << "¿Quiere borrar el fichero? S/N" << endl;
				cin >> borra;
			} while (borra != 'S' && borra != 'N' && borra != 's' && borra != 'n');
			if (borra == 'S' || borra == 's'){
				gitcode.eliminarFichero(nombreFichero);
				cout << "Fichero Borrado, y eliminadas las referencias de los commints"<<endl;
			}
		}
		
	}
	catch (ERROR_DATOS_INCORRECTOS &e)
	{
		cerr << "Excepcion" << e.what() << endl;
	}
	catch (ERROR_FUERA_RANGO &e)
	{
		cerr << "Excepcion" << e.what() << endl;
	}
	catch (FECHA_NO_VALIDA &e)
	{
		cerr << "Excepcion" << e.what() << endl;
	}
	catch (std::ifstream::failure &e)
	{
		std::cerr << "Excepcion leyendo de fichero: " << e.what() << std::endl;
	}


}