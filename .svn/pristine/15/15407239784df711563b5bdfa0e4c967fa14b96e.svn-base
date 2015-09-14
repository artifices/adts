#ifndef TABLAAVLINORDER_CPP
#define TABLAAVLINORDER_CPP

#include "TablaAvlInOrder.h"
#include "ListaEnlazada.h"

template <class C, class V>
TablaAvlInOrder<C,V>::TablaAvlInOrder(pNodoAvl raiz)
{
	this->raiz = raiz;
	stack = new ListaEnlazada<pNodoAvl>();
}

template <class C, class V>
void TablaAvlInOrder<C,V>::Reiniciar()
{
	stack->BorrarTodos();
	AgregarHastaMenor(raiz);
}

template <class C, class V>
bool TablaAvlInOrder<C,V>::HayElemento() const
{
	return !stack->EstaVacia();
}

template <class C, class V>
const Tupla<C,V>& TablaAvlInOrder<C,V>::ElementoActual() const
{
	return stack->Primero()->dato;
}

template <class C, class V>
void TablaAvlInOrder<C,V>::Avanzar()
{
	pNodoAvl actual = stack->Primero();
	stack->Borrar(0);
	AgregarHastaMenor(actual->der);
}

template <class C, class V>
void TablaAvlInOrder<C,V>::AgregarHastaMenor(pNodoAvl nodo)
{
	while (nodo)
	{
		stack->AgregarEn(nodo, 0);
		nodo = nodo->izq;
	}
}

template <class C, class V>
Puntero<Iteracion<Tupla<C,V>>> TablaAvlInOrder<C,V>::Clonar() const
{
	return new TablaAvlInOrder<C,V>(raiz, stack->Clonar());
}

template <class C, class V>
TablaAvlInOrder<C,V>::TablaAvlInOrder(pNodoAvl raiz, Puntero<Lista<pNodoAvl>> stack)
{
	this->raiz = raiz;
	this->stack = stack;
}

#endif