#ifndef COMBINACIONES_H
#define COMBINACIONES_H

#include "Iterador.h"
#include "Array.h"
#include "Lista.h"

class Combinaciones
{
public:
	// Devuelve todas las soluciones, tomando un elemento de cada Iterador
	template <class T>
	static Iterador<Iterador<T>> TodasLasSoluciones(Array<Iterador<T>> opciones);
private:
	template <class T>
	static void TodasLasSoluciones(Array<Iterador<T>> opciones, nat pos, Array<T> actual, Puntero<Lista<Iterador<T>>> soluciones);
};

#include "Combinaciones.cpp"

#endif