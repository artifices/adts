#ifndef TABLAAVLPREORDER_H
#define TABLAAVLPREORDER_H

#include "Tupla.h"
#include "Iteracion.h"
#include "Lista.h"
#include "NodoAvl.h"

template <class C, class V>
class TablaAvlPreOrder : public Iteracion<Tupla<C,V>>
{
	typedef Puntero<NodoAvl<Tupla<C,V>>> pNodoAvl;
public:
	TablaAvlPreOrder(pNodoAvl raiz);

	void Reiniciar();
	bool HayElemento() const;
	const Tupla<C,V>& ElementoActual() const;
	void Avanzar();

	Puntero<Iteracion<Tupla<C,V>>> Clonar() const;

private:
	pNodoAvl raiz;
	Puntero<Lista<pNodoAvl>> stack;

	TablaAvlPreOrder(pNodoAvl raiz, Puntero<Lista<pNodoAvl>> stack);
};

#include "TablaAvlPreOrder.cpp"

#endif