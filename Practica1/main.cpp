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
      getline(stream,titulo,'|');
      getline(stream,interprete,'\n');
      Cancion* cancion=new Cancion(std::stoi(cod),titulo,interprete);
      vcancion.aumenta(cancion);
      
   }
   for (int i=0; i<vcancion.tama();i++){
      cout << vcancion.lee(i)->GetCodigo() << endl;
      cout << vcancion.lee(i)->GetTitulo() << endl;
      cout << vcancion.lee(i)->GetInterprete() << endl;}
    
    
    return 0;
}

