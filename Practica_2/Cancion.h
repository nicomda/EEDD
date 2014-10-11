/* 
 * File:   Cancion.h
 * Author: macosx
 *
 * Created on 25 de septiembre de 2014, 17:57
 */
#include <cstdlib>
#include <string>

#ifndef CANCION_H
#define	CANCION_H
using namespace std;
class Cancion {
    
private:
    int _codigo;
    std::string _titulo;
    std::string _interprete;
    
public:
	Cancion (int codigo, string titulo, string interprete);
	Cancion(const Cancion& orig);
	virtual ~Cancion();
        void SetInterprete(std::string _interprete);
        std::string GetInterprete() const;
        void SetTitulo(std::string _titulo);
        std::string GetTitulo() const;
        void SetCodigo(int _codigo);
        int GetCodigo() const;
        

};

#endif	/* CANCION_H */
