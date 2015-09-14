#ifndef GRAFOLISTASADY_H
#define GRAFOLISTASADY_H

#include "GrafoTablasAdy.h"

template <class V, class A, typename FHashV>
class GrafoListasAdy : public GrafoTablasAdy<V,A,FHashV>
{
public:
	GrafoListasAdy(nat cantVertices, bool esDirigido);

protected:
	Puntero<Grafo<V,nat,FHashV>> CrearGrafoAux(bool esDirigido) const;

private:
	class TablaListaFactory : public TablaFactory
	{
	public:
		Puntero<Tabla<V, Puntero<NodoArco<A>>>> CrearTabla() const;
	};
};

#include "GrafoListasAdy.cpp"

#endif