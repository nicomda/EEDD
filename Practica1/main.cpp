/* 
 * File:   main.cpp
 * Author: nicomda
 *
 * Created on 27 de septiembre de 2014, 16:18
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <string>
#include "Vdinamico.h"
#include "Cancion.h"
#include "Peticion.h"
#include <typeinfo>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    //PRUEBA CON ENTEROS
//    Vdinamico<int> vint;
//    for(int i=0; i<20000; i++){
//        vint.aumenta(rand()%100+1);
//        cout << vint.lee(i);
//    }
    Vdinamico<Cancion*> vcancion;
    string cod, titulo, interprete;
    string filename="canciones.txt";
    
   // Abre un fichero de entrada
   ifstream stream;
   stream.open(filename.c_str());
   while(!stream.eof()) {
      getline(stream,cod,'|');
      int aux=atoi(cod.c_str());
      getline(stream,titulo,'|');
      getline(stream,interprete,'\n');
      Cancion* cancion=new Cancion(aux,titulo,interprete);
      vcancion.aumenta(cancion);
      cout<< "---Lista de Canciones Actualizada---" << endl;
   }
   
   Vdinamico <Peticion*> vpeticion;
   int menu=0;
   do{
        switch(menu){
            
            case 1: cout << "uno" << endl;
                    menu=0;
                    break;
            case 2: cout << "dos" << endl;
                    menu=0;
                    break;
            case 3: menu=3;
                    break;
            default:
                    cout << "**MENU**" << endl;
                    cout << "1-Añadir Peticion" << endl;
                    cout << "2-Eliminar Peticion" << endl;
                    cout << "3-Salir" << endl;
                    int c=1;
                    while(typeid(c)!=typeid(int)) {
                        cin >> c;}
                    if(c<=-1 || c>=4){
                        cout << "Error. Elige una opcion del menú." << endl;
                    }
                    else{
                        menu=c;
                        break;
                    };
                    break;
        }
   }
   while(menu!=3);
   cout << "FIN" << endl;
   /*for (int i=0; i<vcancion.tama();i++){
      cout << vcancion.lee(i)->GetCodigo() << endl;
      cout << vcancion.lee(i)->GetTitulo() << endl;
      cout << vcancion.lee(i)->GetInterprete() << endl;}*/
    
    
    return 0;
}

