#ifndef GRAFOTABLASADY_H
#define GRAFOTABLASADY_H

#include "GrafoBase.h"
#include "NodoArco.h"
#include "Tabla.h"

template <class V, class A, typename FHashV>
class GrafoTablasAdy abstract : public GrafoBase<V,A,FHashV>
{
protected:
	class TablaFactory abstract
	{
	public:
		virtual Puntero<Tabla<V, Puntero<NodoArco<A>>>> CrearTabla() const abstract;
	};

public:
	GrafoTablasAdy(nat cantVertices, bool esDirigido, Puntero<TablaFactory> fabrica);

	// CONSTRUCTORAS
	void AgregarArco(const V& v1, const V& v2, const A& arco);
	void BorrarArco(const V& v1, const V& v2);

	// SELECTORAS
	Iterador<V> Adyacentes(const V& v) const;
	Iterador<V> Incidentes(const V& v) const;
	const A& ObtenerArco(const V& v1, const V& v2) const;
	bool IntentarObtenerArco(const V& v1, const V& v2, A& a) const;
	nat CantidadArcos() const;
	nat CantidadAdyacentes(const V& v) const;
	nat CantidadIncidentes(const V& v) const;

	// PREDICADOS
	bool ExisteArco(const V& v1, const V& v2) const;
	bool EsDirigido() const;

private:
	Array<Puntero<Tabla<V, Puntero<NodoArco<A>>>>> m_Adyacentes;
	Array<Puntero<Tabla<V, Puntero<NodoArco<A>>>>> m_Incidentes;
	nat cantArcos;
	bool esDirigido;
};

#include "GrafoTablasAdy.cpp"

#endif