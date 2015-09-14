#ifndef TABLA_H
#define TABLA_H

#include "Iterable.h"
#include "Puntero.h"
#include "Tupla.h"

typedef unsigned int nat;

template <class C, class V>
class Tabla abstract : public Iterable<Tupla<C,V>>
{
public:
	/* CONSTRUCTORAS */
	/* returna true SII no existía un elemento con la misma clave */
	virtual bool Agregar(const C& c, const V& v) abstract;
	/* retorna true SII encuentra un elemento con la clave a borrar */
	virtual bool Borrar(const C& c) abstract;
	virtual void BorrarTodos() abstract;

	virtual Puntero<Tabla<C,V>> Clonar() const abstract;


	/* PREDICADOS */
	virtual bool EstaVacia() const;
	virtual bool EstaLlena() const abstract;
	virtual bool Pertenece(const C& c) const abstract;


	/* SELECTORAS */
	virtual const V& Obtener(const C& c) const abstract;
	virtual bool IntentarObtener(const C& c, V& v) const;
	virtual nat Largo() const abstract;

	virtual Iterador<C> Claves() const;
	virtual Iterador<V> Valores() const;
};

#include "Tabla.cpp"

#endif