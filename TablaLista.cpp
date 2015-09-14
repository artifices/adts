#ifndef TABLALISTA_CPP
#define TABLALISTA_CPP

#include "TablaLista.h"
#include "ListaEnlazada.h"

template <class C, class V>
TablaLista<C,V>::TablaLista()
{
	m_Lista = new ListaEnlazada<Tupla<C,V>>();
}

template <class C, class V>
TablaLista<C,V>::TablaLista(Puntero<Lista<Tupla<C,V>>> lista)
{
	m_Lista = lista->Clonar();
}

template <class C, class V>
bool TablaLista<C,V>::Agregar(const C& c, const V& v)
{
	bool inserto = !Borrar(c);
	m_Lista->AgregarEn(Tupla<C,V>(c, v), 0);
	return inserto;
}

template <class C, class V>
bool TablaLista<C,V>::Borrar(const C& c)
{
	for (nat pos = 0; pos < m_Lista->Largo(); pos++)
	{
		if (m_Lista->ElementoEn(pos).Dato1 == c)
		{
			m_Lista->Borrar(pos);
			return true;
		}
	}
	return false;
}

template <class C, class V>
void TablaLista<C,V>::BorrarTodos()
{
	m_Lista->BorrarTodos();
}

template <class C, class V>
Puntero<Tabla<C,V>> TablaLista<C,V>::Clonar() const
{
	return new TablaLista<C,V>(m_Lista);
}

template <class C, class V>
bool TablaLista<C,V>::EstaLlena() const
{
	return false;
}

template <class C, class V>
bool TablaLista<C,V>::Pertenece(const C& c) const
{
	foreach (auto clave, this->Claves())
	{
		if (clave == c)
			return true;
	}
	return false;
}

template <class C, class V>
const V& TablaLista<C,V>::Obtener(const C& c) const
{
	nat pos;
	for (pos = 0; pos < m_Lista->Largo(); pos++)
	{
		if (m_Lista->ElementoEn(pos).Dato1 == c)
			break;
	}
	assert(pos < m_Lista->Largo());
	return m_Lista->ElementoEn(pos).Dato2;
}

template <class C, class V>
nat TablaLista<C,V>::Largo() const
{
	return m_Lista->Largo();
}

template <class C, class V>
Iterador<Tupla<C,V>> TablaLista<C,V>::ObtenerIterador() const
{
	return m_Lista->ObtenerIterador();
}

#endif