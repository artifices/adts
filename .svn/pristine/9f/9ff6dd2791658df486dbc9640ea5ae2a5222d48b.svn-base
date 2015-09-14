#ifndef GRAFOAVLSADY_CPP
#define GRAFOAVLSADY_CPP

#include "GrafoAvlsAdy.h"

#include "TablaAvl.h"

template <class V, class A, typename FHashV>
GrafoAvlsAdy<V,A,FHashV>::GrafoAvlsAdy(nat cantVertices, bool esDirigido)
	: GrafoTablasAdy(cantVertices, esDirigido, new TablaAvlFactory())
{
}

template <class V, class A, typename FHashV>
Puntero<Grafo<V,nat,FHashV>> GrafoAvlsAdy<V,A,FHashV>::CrearGrafoAux(bool esDirigido) const
{
	return new GrafoAvlsAdy<V,nat,FHashV>(CantidadVertices(), esDirigido);
}

template <class V, class A, typename FHashV>
Puntero<Tabla<V,Puntero<NodoArco<A>>>> GrafoAvlsAdy<V,A,FHashV>::TablaAvlFactory::CrearTabla() const
{
	return new TablaAvl<V,Puntero<NodoArco<A>>>();
}

#endif