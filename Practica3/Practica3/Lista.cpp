#include "ListaDEnlazada.h"
#include <iostream>
#include <string>

using namespace std;
void main() {
	int l = 333;
	int g = 444;

	ListaDEnlazada<int> listaEnteros;
	for (int i = 0; i < 100; i++) {
		listaEnteros.iteradorFinal(i);
	}
	Iterador<int> i = listaEnteros.iteradorInicio();
	while (i.existe()) {
		cout << i.getDato() << "-";
		i++;
	}
	cout << endl;
	i = listaEnteros.iteradorInicio();

	for (int j = 0; j < 50; j++)i++;
	listaEnteros.insertar(i, l);
	i = listaEnteros.iteradorInicio();
	for (int j = 0; j < 80; j++)i++;
	listaEnteros.insertar(i, g);
	i = listaEnteros.iteradorInicio();
	cout << endl;
	while (i.existe()) {
		cout << i.getDato() << "-";
		i++;
	}

	listaEnteros.borrarInicio();
	listaEnteros.borrarInicio();
	listaEnteros.borrarInicio();
	i = listaEnteros.iteradorInicio();
	cout << endl;
	while (i.existe()) {
		cout << i.getDato() << "-";
		i++;
	}

	listaEnteros.borrarFinal();
	listaEnteros.borrarFinal();
	listaEnteros.borrarFinal();
	listaEnteros.borrarFinal();

	i = listaEnteros.iteradorInicio();
	cout << endl;
	while (i.existe()) {
		cout << i.getDato() << "-";
		i++;
	}

	i = listaEnteros.iteradorInicio();
	for (int j = 0; j < 25; j++)i++;
	listaEnteros.borrar(i);

	i = listaEnteros.iteradorInicio();
	cout << endl;
	while (i.existe()) {
		cout << i.getDato() << "-";
	}

	int a;
	cin >> a;

}