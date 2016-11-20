#include "Excepciones.h"
#include "Fichero.h"
#include "Commit.h"
#include "GitCode.h"
#include "Fecha.h"
#include <string>

#include <iostream>
using namespace std;
	

void main(){

	try{
		GitCode gitcode("ficheros2.txt", "commits.txt");
		
		gitcode.borrarFichero("mandala");
		int numFich=gitcode.getNumFicherosActivos();
		vector<Fichero*> v = gitcode.getFicherosActuales();
		gitcode.borrarCommit("h0ibmr8p");
		
		/*cout << "Introduce un código de Commit: ";
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
		vector<Commit*> commitsFechas;
		commitsFechas = gitcode.getCommFechas(fdesde, fhasta);
		for (int i = 0; i < commitsFechas.size(); i++){
			cout << commitsFechas[i]->getCadenaFecha() << "-->" << commitsFechas[i]->getMensaje() << endl;
		}
		string nombreFichero;
		cout << "**********************************" << endl;
		cout << "Introduzca el codigo del fichero que quiere comprobar si ha sido modificado entre: ";
		cin>>nombreFichero;
		vector<Commit*> commitsFichero;
		commitsFichero = gitcode.getCommFichero(nombreFichero);
		if (commitsFichero.size() == 0){
			cout << "Fichero no encontrado" << endl;
		}
		else{
			cout << endl << "El fichero se ha modificado en los siguientes commints: " << endl;
			for (int i = 0; i < commitsFichero.size(); i++){
				cout << commitsFichero[i]->getMensaje() << endl;				
			}
			cout << "Eliminamos el fichero: " << endl;
			gitcode.borrarFichero(nombreFichero);
			cout << "Fichero Borrado" << endl;
			
		}*/
		int a;
		cin >> a;
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