#ifndef TABLAHASHABIERTOITERACION_CPP
#define TABLAHASHABIERTOITERACION_CPP

#include "TablaHashAbiertoIteracion.h"

template <class C, class V>
TablaHashAbiertoIteracion<C,V>::TablaHashAbiertoIteracion(Array<Puntero<Tabla<C,V>>> arreglo)
{
	iterArreglo = arreglo.ObtenerIterador();
}

template <class C, class V>
void TablaHashAbiertoIteracion<C,V>::Reiniciar()
{
	iterArreglo.Reiniciar();
	if (iterArreglo)
		iterLista = (*iterArreglo)->ObtenerIterador();
	else
		iterLista = nullptr;
	while (iterArreglo && !iterLista)
	{
		++iterArreglo;
		if (iterArreglo)
			iterLista = (*iterArreglo)->ObtenerIterador();
		else
			iterLista = nullptr;
	}
}

template <class C, class V>
bool TablaHashAbiertoIteracion<C,V>::HayElemento() const
{
	return iterArreglo && iterLista;
}

template <class C, class V>
const Tupla<C,V>& TablaHashAbiertoIteracion<C,V>::ElementoActual() const
{
	return *iterLista;
}

template <class C, class V>
void TablaHashAbiertoIteracion<C,V>::Avanzar()
{
	++iterLista;
	while (iterArreglo && !iterLista)
	{
		++iterArreglo;
		if (iterArreglo)
			iterLista = (*iterArreglo)->ObtenerIterador();
		else
			iterLista = nullptr;
	}
}

template <class C, class V>
TablaHashAbiertoIteracion<C,V>::TablaHashAbiertoIteracion(Iterador<Puntero<Tabla<C,V>>> iterArreglo, Iterador<Tupla<C,V>> iterLista)
{
	this->iterArreglo = iterArreglo;
	this->iterLista = iterLista;
}

template <class C, class V>
Puntero<Iteracion<Tupla<C,V>>> TablaHashAbiertoIteracion<C,V>::Clonar() const
{
	return new TablaHashAbiertoIteracion<C,V>(iterArreglo.Clonar(), iterLista.Clonar());
}

#endif