#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include "Lista.h"
#include "NodoLista.h"
#include "Puntero.h"

template <class T>
class ListaEnlazada : public Lista<T>
{
	typedef Puntero<NodoLista<T>> pNodoLista;
public:
	ListaEnlazada();
	ListaEnlazada(Iterador<T> iterador);

	// CONSTRUCTORAS

	// Inserta un elemento e del tipo T en la posición indicada
	// Precondición: 0 <= pos <= Largo()
	void AgregarEn(const T& e, nat pos) override;

	// Borra todos los elementos de la lista, construyendo la lista vacia
	void BorrarTodos() override;

	// Borra el elemento que se encuentra en la posoción pos
	// Precondición: 0 <= pos < Largo()
	void Borrar(nat pos) override;

	// Devuelve una nueva lista que es una copia de la actual
	// Los elementos que pertenecen a ambas listas son los mismos
	// pero los nodos de las listas no deben compartir memoria
	Puntero<Lista<T>> Clonar() const override;


	// SELECTORAS

	// Retorna el elemento que se encuentra en la posicion pos
	// Precondición: 0 <= pos < Largo()
	const T& ElementoEn(nat pos) const override;

	// Retorna el elemento que se encuentra en la posicion pos
	// Precondición: 0 <= pos < Largo()
	T& ElementoEn(nat pos) override;

	// Devuelve la cantidad de elementos de la lista
	nat Largo() const override;

	Iterador<T> ObtenerIterador() const override;


	// PREDICADOS

	// Retorna true si y solo si la lista esta llena
	bool EstaLlena() const override;

private:
	pNodoLista primero;
	pNodoLista ultimo;
	nat largo;

	mutable pNodoLista nodoActual;
	mutable nat posActual;
};

#include "ListaEnlazada.cpp"

#endif