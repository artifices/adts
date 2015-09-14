#ifndef NODOLISTA_H
#define NODOLISTA_H

#include "Puntero.h"

template <class T>
class NodoLista
{
	typedef Puntero<NodoLista> pNodoLista;

public:
	NodoLista(const T& dato)
		: dato(dato), sig(nullptr)
	{
	}

	NodoLista(const T& dato, const pNodoLista& sig)
		: dato(dato), sig(sig)
	{
	}

	T dato;
	pNodoLista sig;
};

#endif