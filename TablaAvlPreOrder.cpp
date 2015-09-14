#ifndef TABLAAVLPREORDER_CPP
#define TABLAAVLPREORDER_CPP

#include "TablaAvlPreOrder.h"
#include "ListaEnlazada.h"

template <class C, class V>
TablaAvlPreOrder<C,V>::TablaAvlPreOrder(pNodoAvl raiz)
{
	this->raiz = raiz;
	stack = new ListaEnlazada<pNodoAvl>();
}

template <class C, class V>
TablaAvlPreOrder<C,V>::TablaAvlPreOrder(pNodoAvl raiz, Puntero<Lista<pNodoAvl>> stack)
{
	this->raiz = raiz;
	this->stack = stack;
}

template <class C, class V>
void TablaAvlPreOrder<C,V>::Reiniciar()
{
	stack->BorrarTodos();
	stack->AgregarEn(raiz, 0);
}

template <class C, class V>
bool TablaAvlPreOrder<C,V>::HayElemento() const
{
	return !stack->EstaVacia();
}

template <class C, class V>
const Tupla<C,V>& TablaAvlPreOrder<C,V>::ElementoActual() const
{
	return stack->Primero()->dato;
}

template <class C, class V>
void TablaAvlPreOrder<C,V>::Avanzar()
{
	pNodoAvl actual = stack->Primero();
	stack->Borrar(0);
	if (actual->der)
		stack->AgregarEn(actual->der, 0);
	if (actual->izq)
		stack->AgregarEn(actual->izq, 0);
}

template <class C, class V>
Puntero<Iteracion<Tupla<C,V>>> TablaAvlPreOrder<C,V>::Clonar() const
{
	return new TablaAvlPreOrder<C,V>(raiz, stack->Clonar());
}

#endif