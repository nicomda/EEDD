#include "ListaDEnlazada.h"
#include <iostream>

using namespace std;


void main() {

	ListaDEnlazada<int> listaEnteros;
	int m = 333;
	int n = 444;
	for (int i = 0; i < 100; i++) {
		listaEnteros.insertarFinal(i);
	}
	Iterador<int> i = listaEnteros.iteradorInicio();
	while (i.existe()) {
		cout << i.getDato() << "-";
		i.siguiente;
	}
	cout << endl;
	i = listaEnteros.iteradorInicio();

	for (int j = 0; j < 50; j++)i.siguiente;
	listaEnteros.insertar(i, m);
	i = listaEnteros.iteradorInicio();
	for (int j = 0; j < 80; j++)i.siguiente;
	listaEnteros.insertar(i, n);
	i = listaEnteros.iteradorInicio();
	cout << endl;
	while (i.existe()) {
		cout << i.getDato() << "-";
		i.siguiente;
	}

	listaEnteros.borrarInicio();
	listaEnteros.borrarInicio();
	listaEnteros.borrarInicio();
	i = listaEnteros.iteradorInicio();
	cout << endl;
	while (i.existe()) {
		cout << i.getDato() << "-";
		i.siguiente;
	}

	listaEnteros.borrarFinal();
	listaEnteros.borrarFinal();
	listaEnteros.borrarFinal();
	listaEnteros.borrarFinal();

	i = listaEnteros.iteradorInicio();
	cout << endl;
	while (i.existe()) {
		cout << i.getDato() << "-";
		i.siguiente;
	}

	i = listaEnteros.iteradorInicio();
	for (int j = 0; j < 25; j++)i.siguiente;
	listaEnteros.borrar(i);

	i = listaEnteros.iteradorInicio();
	cout << endl;
	while (i.existe()) {
		cout << i.getDato() << "-";
		i.siguiente;
	}

	int a;
	cin >> a;
}