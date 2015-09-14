#ifndef TABLAAVLPOSORDER_H
#define TABLAAVLPOSORDER_H

#include "Tupla.h"
#include "Iteracion.h"
#include "NodoAvl.h"

template <class C, class V>
class TablaAvlPosOrder : public Iteracion<Tupla<C,V>>
{
	typedef Puntero<NodoAvl<Tupla<C,V>>> pNodoAvl;
public:
	TablaAvlPosOrder(pNodoAvl raiz);

	void Reiniciar();
	bool HayElemento() const;
	const Tupla<C,V>& ElementoActual() const;
	void Avanzar();

	Puntero<Iteracion<Tupla<C,V>>> Clonar() const;

private:
	pNodoAvl raiz;
};

#include "TablaAvlPosOrder.cpp"

#endif