#ifndef LISTAENLAZADAITERACION_CPP
#define LISTAENLAZADAITERACION_CPP

#include "ListaEnlazadaIteracion.h"

template <class T>
ListaEnlazadaIteracion<T>::ListaEnlazadaIteracion(const Puntero<NodoLista<T>>& lista)
: m_Primero(lista)
{
}

template <class T>
void ListaEnlazadaIteracion<T>::Reiniciar()
{
	m_Actual = m_Primero;
}

template <class T>
bool ListaEnlazadaIteracion<T>::HayElemento() const
{
	return m_Actual;
}

template <class T>
const T& ListaEnlazadaIteracion<T>::ElementoActual() const
{
	return m_Actual->dato;
}

template <class T>
void ListaEnlazadaIteracion<T>::Avanzar()
{
	m_Actual = m_Actual->sig;
}

template <class T>
ListaEnlazadaIteracion<T>::ListaEnlazadaIteracion(const Puntero<NodoLista<T>>& lista, const Puntero<NodoLista<T>>& actual)
: m_Primero(lista), m_Actual(actual)
{
}

template <class T>
Puntero<Iteracion<T>> ListaEnlazadaIteracion<T>::Clonar() const
{
	return new ListaEnlazadaIteracion<T>(m_Primero, m_Actual);
}

#endif