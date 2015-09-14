#ifndef LISTAENLAZADA_CPP
#define LISTAENLAZADA_CPP

#include "ListaEnlazada.h"
#include "ListaEnlazadaIteracion.h"

template <class T>
ListaEnlazada<T>::ListaEnlazada()
{
	largo = 0;
	posActual = 0;
}

template <class T>
ListaEnlazada<T>::ListaEnlazada(Iterador<T> it)
{
	largo = 0;
	posActual = 0;
	foreach (auto v, it)
		Agregar(v);
}

template <class T>
void ListaEnlazada<T>::AgregarEn(const T& e, nat pos)
{
	assert(pos <= Largo());
	if (pos == 0)
	{
		primero = new NodoLista<T>(e, primero);
		if (!ultimo)
		{
			ultimo = nodoActual = primero;
			posActual = 0;
		}
		else
			posActual++;
	}
	else if (pos == Largo())
	{
		ultimo->sig = new NodoLista<T>(e);
		ultimo = ultimo->sig;
	}
	else
	{
		if (posActual >= pos)
		{
			posActual = 0;
			nodoActual = primero;
		}

		while (posActual - 1 < pos)
		{
			posActual++;
			nodoActual = nodoActual->sig;
		}

		pNodoLista nuevo = new NodoLista<T>(e, nodoActual->sig);
		nodoActual->sig = nuevo;
		nodoActual = nuevo;
		posActual = pos;
	}
	largo++;
}

template <class T>
void ListaEnlazada<T>::BorrarTodos()
{
	largo = 0;
	primero = nullptr;
	ultimo = nullptr;
	nodoActual = nullptr;
	posActual = 0;
}

template <class T>
void ListaEnlazada<T>::Borrar(nat pos)
{
	assert(pos < Largo());

	if (pos == 0)
	{
		primero = primero->sig;
		if (Largo() == 1)
			ultimo = nullptr;
	}
	else
	{
		if (pos == Largo() -1)
		{
			if (posActual < Largo() - 1)
				ultimo = nodoActual;
			else
				ultimo = primero;
			while (ultimo->sig->sig)
				ultimo = ultimo->sig;
			ultimo->sig = nullptr;
		}
		else
		{
			if (posActual >= pos)
			{
				posActual = 0;
				nodoActual = primero;
			}
			while (posActual < pos - 1)
			{
				posActual++;
				nodoActual = nodoActual->sig;
			}
			nodoActual->sig = nodoActual->sig->sig;
		}
	}

	if (posActual == pos)
		nodoActual = nodoActual->sig;
	else if (posActual > pos)
		posActual--;
	largo--;
}

template <class T>
Puntero<Lista<T>> ListaEnlazada<T>::Clonar() const
{
	return new ListaEnlazada<T>(this->ObtenerIterador());
}

template <class T>
const T& ListaEnlazada<T>::ElementoEn(nat pos) const
{
	assert(pos < Largo());
	if (pos == 0)
		return primero->dato;
	else if (pos == Largo() - 1)
		return ultimo->dato;

	if (posActual > pos)
	{
		posActual = 0;
		nodoActual = primero;
	}

	while (posActual < pos)
	{
		nodoActual = nodoActual->sig;
		posActual++;
	}

	return nodoActual->dato;
}

template <class T>
T& ListaEnlazada<T>::ElementoEn(nat pos)
{
	assert(pos < Largo());
	if (pos == 0)
		return primero->dato;
	else if (pos == Largo() - 1)
		return ultimo->dato;

	if (posActual > pos)
	{
		posActual = 0;
		nodoActual = primero;
	}

	while (posActual < pos)
	{
		nodoActual = nodoActual->sig;
		posActual++;
	}

	return nodoActual->dato;
}

template <class T>
nat ListaEnlazada<T>::Largo() const
{
	return largo;
}

template <class T>
Iterador<T> ListaEnlazada<T>::ObtenerIterador() const
{
	return new ListaEnlazadaIteracion<T>(primero);
}

template <class T>
bool ListaEnlazada<T>::EstaLlena() const
{
	return false;
}

#endif