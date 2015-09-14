#ifndef TABLAAVLINORDER_H
#define TABLAAVLINORDER_H

#include "Tupla.h"
#include "Iteracion.h"
#include "Lista.h"
#include "NodoAvl.h"

template <class C, class V>
class TablaAvlInOrder : public Iteracion<Tupla<C,V>>
{
	typedef Puntero<NodoAvl<Tupla<C,V>>> pNodoAvl;
public:
	TablaAvlInOrder(pNodoAvl raiz);

	void Reiniciar();
	bool HayElemento() const;
	const Tupla<C,V>& ElementoActual() const;
	void Avanzar();

	Puntero<Iteracion<Tupla<C,V>>> Clonar() const;

private:
	TablaAvlInOrder(pNodoAvl raiz, Puntero<Lista<pNodoAvl>> stack);

	pNodoAvl raiz;
	Puntero<Lista<pNodoAvl>> stack;

	void AgregarHastaMenor(pNodoAvl nodo);
};

#include "TablaAvlInOrder.cpp"

#endif