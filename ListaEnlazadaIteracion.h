#pragma once

#include "Iteracion.h"
#include "NodoLista.h"
#include "Puntero.h"

template <class T>
class ListaEnlazadaIteracion : public Iteracion<T>
{
public:
	ListaEnlazadaIteracion(const Puntero<NodoLista<T>>& lista);

	void Reiniciar() override;
	bool HayElemento() const override;
	const T& ElementoActual() const override;
	void Avanzar() override;

	Puntero<Iteracion<T>> Clonar() const override;

private:
	ListaEnlazadaIteracion(const Puntero<NodoLista<T>>& lista, const Puntero<NodoLista<T>>& actual);

	Puntero<NodoLista<T>> m_Primero;
	Puntero<NodoLista<T>> m_Actual;
};

#include "ListaEnlazadaIteracion.cpp"