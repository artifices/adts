#ifndef GRAFOAVLSADY_H
#define GRAFOAVLSADY_H

#include "GrafoTablasAdy.h"

template <class V, class A, typename FHashV>
class GrafoAvlsAdy : public GrafoTablasAdy<V,A,FHashV>
{
public:
	GrafoAvlsAdy(nat cantVertices, bool esDirigido);

protected:
	Puntero<Grafo<V,nat,FHashV>> CrearGrafoAux(bool esDirigido) const;

private:
	class TablaAvlFactory : public TablaFactory
	{
	public:
		Puntero<Tabla<V, Puntero<NodoArco<A>>>> CrearTabla() const;
	};
};

#include "GrafoAvlsAdy.cpp"

#endif