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

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    string cod, titulo, interprete;
    string filename="canciones.txt";
    
   // Abre un fichero de entrada
   ifstream stream;
   stream.open(filename.c_str());
   while(!stream.eof()) {
      
      getline(stream,cod,'|');
      getline(stream,titulo,'|');
      getline(stream,interprete,'\n');
      cout << cod << endl;
      cout << titulo << endl;
      cout << interprete << endl;
   }
    
    
    return 0;
}

