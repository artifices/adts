#ifndef NODOAVL_H
#define NODOAVL_H

#include "Puntero.h"

template <class T>
class NodoAvl
{
	typedef Puntero<NodoAvl> pNodoAvl;

public:
	NodoAvl(const T& dato, pNodoAvl izq = nullptr, pNodoAvl der = nullptr)
		: dato(dato), fb(0), izq(izq), der(der)
	{
	}

	T dato;
	pNodoAvl izq;
	pNodoAvl der;
	int fb;
};

enum AvlIteration
{
	INORDER,
	PREORDER,
	POSORDER
};

#endif