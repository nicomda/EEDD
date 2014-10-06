/* 
 * File:   Vdinamico.h
 * Author: nicomda
 *
 * Created on 5 de octubre de 2014, 12:28
 */

#ifndef VDINAMICO_H
#define	VDINAMICO_H

template<class T>class Vdinamico {
private:
    int tamal,tamaf;
    int *v;
public:
    Vdinamico();
    Vdinamico(const Vdinamico& orig);
    virtual ~Vdinamico();
    int lee(int pos){ return v[pos]; }
    void escribe(int pos, int dato){ v[pos] = dato; }
    void inserta(int dato, unsigned pos);
    int elimina(unsigned pos);
    void aumenta(int dato); // Inserción por la derecha
    int disminuye(); // Eliminar dato por la derecha
    unsigned tama(){ return tamal; };
    void ordenar();
    int busca(int dato); 
    int busquedaBin(int dato);
};

template<class T>
Vdinamico<T>::Vdinamico(){
    //TODO
}

template<class T>
Vdinamico<T>::inserta(int dato, unsigned pos){
    if(tamal==tamaf){
    int *vaux;
    vaux= new int[tamaf=tamaf*2];
    for (unsigned i=tamal-1;i>pos;i--){
        v[i+1]=v[i];
    }
    }
    v[pos]=dato;
}

template<class T>
Vdinamico<T>::aumenta(int dato){
    if(tamal==tamaf){
        int *vaux;
        vaux= new int[tamaf=tamaf*2];
        for(int i=0;i<tamal;i++)
            vaux[i]=v[i];
        delete []v;
        v=vaux;
    }
    v[tamal++]=dato;
}

template<class T>
Vdinamico<T>::disminuye(){
    if (tamal*3<tamaf){
        tamaf=tamaf/2;
        int *vaux = new T[tamaf];
        for(unsigned i=0;i<tamal;i++){
            vaux[i]=v[i];
        };
       
    }
}
#endif	/* VDINAMICO_H */

