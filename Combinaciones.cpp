#ifndef COMBINACIONES_CPP
#define COMBINACIONES_CPP

#include "Combinaciones.h"
#include "ListaEnlazada.h"

template <class T>
Iterador<Iterador<T>> Combinaciones::TodasLasSoluciones(Array<Iterador<T>> opciones)
{
	Puntero<Lista<Iterador<T>>> soluciones = new ListaEnlazada<Iterador<T>>();
	TodasLasSoluciones(opciones, 0, Array<T>(opciones.Largo), soluciones);
	return soluciones->ObtenerIterador();
}

template <class T>
void Combinaciones::TodasLasSoluciones(Array<Iterador<T>> opciones, nat pos, Array<T> actual, Puntero<Lista<Iterador<T>>> soluciones)
{
	if (pos == actual.Largo)
	{
		Array<T> nueva(actual.Largo);
		Array<T>::Copiar(actual, nueva);
		soluciones->Agregar(nueva.ObtenerIterador());
	}
	else
	{
		foreach (auto a, opciones[pos])
		{
			actual[pos] = a;
			TodasLasSoluciones(opciones, pos + 1, actual, soluciones);
		}
	}
}

#endif