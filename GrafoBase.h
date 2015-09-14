#ifndef GRAFOBASE_H
#define GRAFOBASE_H

#include "Grafo.h"
#include "NodoVertice.h"
#include "Tabla.h"

template <class V, class A, typename FHashV>
class GrafoBase abstract : public Grafo<V,A,FHashV>
{
public:
	GrafoBase(nat cantVertices);

	// CONSTRUCTORAS
	void AgregarVertice(const V& v);
	void BorrarVertice(const V& v);

	// SELECTORAS
	nat CantidadVertices() const;
	Iterador<V> ObtenerIterador() const;

	// PREDICADOS
	bool ExisteVertice(const V& v) const;
	bool EstaLleno() const;
	bool EstaVacio() const;

protected:
	const Puntero<NodoVertice<V>>& ObtenerVertice(const V& v) const;
	const Puntero<NodoVertice<V>>& ObtenerVerticePrt(nat pos) const;

private:
	Array<Puntero<NodoVertice<V>>> arrayVertices;
	Puntero<Tabla <V, Puntero<NodoVertice<V>> > > tablaVertices;
	nat cantVertices;
};

#include "GrafoBase.cpp"

#endif