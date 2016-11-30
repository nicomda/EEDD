#include <iostream>
#include <fstream>
#include <string>
#include "GitCode.h"
#include "Commit.h"
#include "Fichero.h"
#include "Fecha.h"
#include "Excepciones.h"
#include <list>
#include <vector>
#include "THashCerrada.h"
#include <cstdio>
using namespace std;

int main(int argc, char** argv) {
	try {
            int select=0;
            GitCode git("ficheros2.txt", "commits 2.txt");
            string nombre, codigo, mmarcadetiempo, mmensaje,ruta;
            vector<string> mficheros;
            int numFich,insertfich,tamabytes;
            vector<Fichero*> v;
            Fichero f;
            do{
                cout<< "--------MENU-------"<<endl;
                cout<<"1. Borrar fichero"<<endl;
                cout<<"2. Borrar commit"<<endl;
                cout<<"3. Insertar commit"<<endl; 
                cout<<"4. Insertar fichero"<<endl;
                cout<<"5. Estado de archivos"<<endl;
                cout << "0. Salir"<<endl;
                
                //cout<<"6. Borrar fichero"<<endl;
                cout<<"Introduce una opción del menu:"<<endl;
                cin >> select;
                switch(select){
                    case 0:
                        cout <<"Gracias por utilizar nuestro software"<<endl;
                        break;
                    case 1:
                        cout << "Introduce el nombre de un Fichero que quiera borrar: " << endl;
                        cin >> nombre;
                        git.borraFichero(nombre);
                        break;
                    case 2:
                        cout << "Introduce el codigo del Commit que quiere borrar: " << endl;
                    cin >> codigo;
                    git.borraCommit(codigo);
                    break;
                    case 3:
                        cout<<"Codigo del commit:"<<endl;
                        cin>>codigo;
                        cout<<"Fecha de creacion (YYYYMMDDHHMMSS)"<<endl;
                        cin>>mmarcadetiempo;
                        cout<<"Descripcion del commit"<<endl;
                        cin.ignore();
                        getline(std::cin,mmensaje);
                        cout << "Cuantos ficheros quiere vincular?" << endl;
                        cin>>insertfich;
                        for(int i=0;i<insertfich;i++){
                            cout<<"Nombre de fichero. Quedan "<<(insertfich-i)<<endl;
                            cin>>nombre;
                            v.push_back(git.buscarFichero(nombre));
                        
                        }
                        cout <<"Commit insertado"<<endl;
                        break;
                    case 4:
                        cout << "Introduce nombre de fichero: "<<endl;
                        cin>>nombre;
                        cout << "Introduce la ruta: "<<endl;
                        cin>>ruta;
                        cout << "Introduce el tamanio del archivo: "<<endl;
                        cin>>tamabytes;
                        f.setNombre(nombre);
                        f.setUbicacion(ruta);
                        f.setTamaBytes(tamabytes);
                        git.nuevoFichero(f);
                        cout << "Fichero insertado"<<endl;
                        break;
                    case 5:
                        cout <<"Numero de ficheros activos: "<<numFich<<endl;
                        break;
                        
                    default:
                        cout<<"Introduzca una opción correcta: "<<endl;
                        break;
                }
                numFich = git.getNumFicherosActivos();
		v=git.getFicherosActivos();
            
            }while(select!=0);
		
	}
	catch (ERROR_DATOS_INCORRECTOS &error) {
		cerr << "Excepcion: " << error.what() << endl;
	}
	catch (ERROR_FUERA_RANGO &error) {
		cerr << "Excepcion: " << error.what() << endl;

	}
	catch (FECHA_NO_VALIDA &error) {
		cerr << "Excepcion: " << error.what() << endl;
	}
	catch (std::ifstream::failure &error) {
		cerr << "Excepcion: Error al leer el fichero" << error.what() << endl;
	}
	catch (ERROR_COMMIT_NO_ENCONTRADO &error) {
		cerr << "Excepcion: " << error.what() << endl;
	}
	catch (ERROR_COMMIT_REPETIDO &error) {
		cerr << "Excepcion: " << error.what() << endl;
	}
	catch (ERROR_FICHERO_REPETIDO &error) {
		cerr << "Excepcion: " << error.what() << endl;
	}
}