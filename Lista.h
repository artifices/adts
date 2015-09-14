#ifndef LISTA_H
#define LISTA_H

#include "Iterable.h"
#include "Puntero.h"

typedef unsigned int nat;

template <class T>
class Lista abstract : public Iterable<T>
{
public:
	// CONSTRUCTORAS

	// Inserta un elemento e del tipo T al final de la lista
	virtual void Agregar(const T& e);

	// Inserta un elemento e del tipo T en la posición indicada
	// Precondición: 0 <= pos <= Largo()
	virtual void AgregarEn(const T& e, nat pos) abstract;

	// Borra todos los elementos de la lista, construyendo la lista vacia
	virtual void BorrarTodos();

	// Borra el elemento que se encuentra en la posoción pos
	// Precondición: 0 <= pos < Largo()
	virtual void Borrar(nat pos) abstract;

	// Devuelve una nueva lista que es una copia de la actual
	// Los elementos que pertenecen a ambas listas son los mismos
	// pero los nodos de las listas no deben compartir memoria
	virtual Puntero<Lista<T>> Clonar() const abstract;


	// SELECTORAS

	// Retorna el elemento que se encuentra en la posicion pos
	// Precondición: 0 <= pos < Largo()
	virtual const T& ElementoEn(nat pos) const abstract;

	// Retorna el elemento que se encuentra en la posicion pos
	// Precondición: 0 <= pos < Largo()
	virtual T& ElementoEn(nat pos) abstract;

	// Retorna el primer elemento de la lista
	// Precondición: Largo() > 0
	virtual const T& Primero() const;

	// Retorna el último elemento de la lista
	// Precondición: Largo() > 0
	virtual const T& Ultimo() const;

	// Devuelve la cantidad de elementos de la lista
	virtual nat Largo() const abstract;


	// PREDICADOS

	// Retorna true si y solo si el elemento e pertenece a la lista
	bool Pertenece(const T& e, const Comparador<T>& comparador =  Comparador<T>::Default) const;

	// Retorna true si y solo si la lista esta llena
	virtual bool EstaLlena() const abstract;

	// Retorna true si y solo si la lista esta vacia
	virtual bool EstaVacia() const;
};

#include "Lista.cpp"

#endif