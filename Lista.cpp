#ifndef LISTA_CPP
#define LISTA_CPP

#include "Lista.h"
#include "Comparador.h"

template <class T>
void Lista<T>::Agregar(const T& e)
{
	AgregarEn(e, Largo());
}

template <class T>
void Lista<T>::BorrarTodos()
{
	while (Largo() > 0)
		Borrar(0);
}

template <class T>
const T& Lista<T>::Primero() const
{
	assert(Largo() > 0);
	return ElementoEn(0);
}

template <class T>
const T& Lista<T>::Ultimo() const
{
	assert(Largo() > 0);
	return ElementoEn(Largo() - 1);
}

template <class T>
bool Lista<T>::Pertenece(const T& e, const Comparador<T>& comparador) const
{
	foreach (auto v, this)
	{
		if (comparador.SonIguales(v, e))
			return true;
	}
	return false;
}

template <class T>
bool Lista<T>::EstaVacia() const
{
	return Largo() == 0;
}

#endif