#ifndef TABLAAVLPOSORDER_CPP
#define TABLAAVLPOSORDER_CPP

#include "TablaAvlPosOrder.h"

template <class C, class V>
TablaAvlPosOrder<C,V>::TablaAvlPosOrder(pNodoAvl raiz)
{
	this->raiz = raiz;
}

template <class C, class V>
void TablaAvlPosOrder<C,V>::Reiniciar()
{
}

template <class C, class V>
bool TablaAvlPosOrder<C,V>::HayElemento() const
{
	return false;
}

template <class C, class V>
const Tupla<C,V>& TablaAvlPosOrder<C,V>::ElementoActual() const
{
	assert(raiz);
	return raiz->dato;
}

template <class C, class V>
void TablaAvlPosOrder<C,V>::Avanzar()
{
}

template <class C, class V>
Puntero<Iteracion<Tupla<C,V>>> TablaAvlPosOrder<C,V>::Clonar() const
{
	return new TablaAvlPosOrder<C,V>(raiz);
}

#endif