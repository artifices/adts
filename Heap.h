#ifndef HEAP_H
#define HEAP_H

#include "Iterable.h"

template <class T>
class Heap abstract : public Iterable<T>
{
public:
	/* CONSTRUCTORAS */
	virtual void Agregar(const T &e) abstract;
	virtual void BorrarMin() abstract;
	virtual void BorrarElemento(const T &e) abstract;

	/* SELECTORAS */
	virtual T& ObtenerMin() const abstract;
	virtual nat Largo() const abstract;

	/* PREDICADOS */
	virtual bool EstaVacia() const abstract;
	virtual bool EstaLlena() const abstract;
};

#endif