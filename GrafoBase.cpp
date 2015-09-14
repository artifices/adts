#ifndef GRAFOBASE_CPP
#define GRAFOBASE_CPP

#include "GrafoBase.h"

template <class V, class A, typename FHashV>
GrafoBase<V,A,FHashV>::GrafoBase(nat cantVertices)
{
	arrayVertices = Array<Puntero<NodoVertice<V>>>(cantVertices);
	tablaVertices = new TablaHashAbierto<V, Puntero<NodoVertice<V>>, FHashV>(cantVertices, 1);
	this->cantVertices = 0;
}

template <class V, class A, typename FHashV>
void GrafoBase<V,A,FHashV>::AgregarVertice(const V& v)
{
	assert(!ExisteVertice(v));
	assert(!EstaLleno());
	Puntero<NodoVertice<V>> nodoV = new NodoVertice<V>(v, cantVertices);
	tablaVertices->Agregar(v, nodoV);
	arrayVertices[cantVertices] = nodoV;
	cantVertices++;
}

template <class V, class A, typename FHashV>
void GrafoBase<V,A,FHashV>::BorrarVertice(const V& v)
{
	assert(false);
}

template <class V, class A, typename FHashV>
nat GrafoBase<V,A,FHashV>::CantidadVertices() const
{
	return cantVertices;
}

template <class V, class A, typename FHashV>
Iterador<V> GrafoBase<V,A,FHashV>::ObtenerIterador() const
{
	return tablaVertices->Claves();
}

template <class V, class A, typename FHashV>
bool GrafoBase<V,A,FHashV>::ExisteVertice(const V& v) const
{
	return tablaVertices->Pertenece(v);
}

template <class V, class A, typename FHashV>
bool GrafoBase<V,A,FHashV>::EstaLleno() const
{
	return cantVertices == arrayVertices.Largo;
}

template <class V, class A, typename FHashV>
bool GrafoBase<V,A,FHashV>::EstaVacio() const
{
	return cantVertices == 0;
}

template <class V, class A, typename FHashV>
const Puntero<NodoVertice<V>>& GrafoBase<V,A,FHashV>::ObtenerVertice(const V& v) const
{
	assert(tablaVertices->Pertenece(v));
	return tablaVertices->Obtener(v);
}

template <class V, class A, typename FHashV>
const Puntero<NodoVertice<V>>& GrafoBase<V,A,FHashV>::ObtenerVerticePrt(nat pos) const
{
	assert(pos < CantidadVertices());
	return arrayVertices[pos];
}

#endif