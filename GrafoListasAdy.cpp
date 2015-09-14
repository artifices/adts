#ifndef GRAFOLISTASADY_CPP
#define GRAFOLISTASADY_CPP

#include "GrafoListasAdy.h"

#include "TablaLista.h"

template <class V, class A, typename FHashV>
GrafoListasAdy<V,A,FHashV>::GrafoListasAdy(nat cantVertices, bool esDirigido)
	: GrafoTablasAdy(cantVertices, esDirigido, new TablaListaFactory())
{
}

template <class V, class A, typename FHashV>
Puntero<Grafo<V,nat,FHashV>> GrafoListasAdy<V,A,FHashV>::CrearGrafoAux(bool esDirigido) const
{
	return new GrafoListasAdy<V,nat,FHashV>(CantidadVertices(), esDirigido);
}

template <class V, class A, typename FHashV>
Puntero<Tabla<V,Puntero<NodoArco<A>>>> GrafoListasAdy<V,A,FHashV>::TablaListaFactory::CrearTabla() const
{
	return new TablaLista<V,Puntero<NodoArco<A>>>();
}

#endif