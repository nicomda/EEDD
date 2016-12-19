#include "Lector.h"
vector<Libro*> Lector::librosLeidos(){
	multimap<int, Valoracion, greater<int>>::iterator iValoraciones = valoraciones.begin();
	vector<Libro*> vLibros;
	while (iValoraciones != valoraciones.end()) {
		vLibros.push_back(((*iValoraciones).second).getLibro());
		iValoraciones++;
	}
	return vLibros;
	
}

vector<Libro*> Lector::librosRecomendados(){
	multimap<int, Libro*, greater<int>> lRecomendados;
	multimap<int, Libro*, greater<int>>::iterator iLibrosRecomendados;
	pair<int, Libro*> pairlRecomendados;
	map<int, Libro*> leidosR;
	map<int, Libro*>::iterator iLeidosR;
	pair<int, Libro*> pairLeidosR;
	vector<Libro*> librosL = librosLeidos();
	for (int i = 0; i < librosL.size(); i++) {
		vector<Lector*> vLectores = librosL[i]->getLectores();
		for (int j = 0; j < vLectores.size(); j++) {
			vector<Libro*> vLibrosLectores = vLectores[j]->librosLeidos();
			for (int k = 0; k < vLibrosLectores.size(); k++) {
				iLeidosR = leidosR.find(vLibrosLectores[k]->getId());
				if (iLeidosR != leidosR.end()) {
					pairLeidosR.first = vLibrosLectores[k]->getId();
					pairLeidosR.second = vLibrosLectores[k];
					leidosR.insert(pairLeidosR);

					pairlRecomendados.first = vLibrosLectores[k]->getNumValoraciones;
					pairlRecomendados.second = vLibrosLectores[k];
					lRecomendados.insert(pairlRecomendados);
				}
			}
		}
	}
	iLibrosRecomendados = lRecomendados.begin();
	vector<Libro*> vLibros;
	for(int i=0;i<10 && iLibrosRecomendados != lRecomendados.end();i++){
		vLibros.push_back((*iLibrosRecomendados).second);
		iLibrosRecomendados++;
	}
	return vLibros;
}

void Lector::nuevaValoracion(Libro * l, int puntuacion) {
	if (puntuacion < 0 || puntuacion>5) throw ERROR_PUNTUACION_FUERA_DE_RANGO();
	l->nuevaValoracion(puntuacion);
	Valoracion v(puntuacion, l);
	pair<int, Valoracion> pairValoracion;
	pairValoracion.first = puntuacion;
	pairValoracion.second = v;
	valoraciones.insert(pairValoracion);
	l->nuevoLector(this);
}
