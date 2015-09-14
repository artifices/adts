#ifndef GRAFOTABLASADY_CPP
#define GRAFOTABLASADY_CPP

#include "GrafoTablasAdy.h"

template <class V, class A, typename FHashV>
GrafoTablasAdy<V,A,FHashV>::GrafoTablasAdy(nat cantVertices, bool esDirigido, Puntero<TablaFactory> fabrica)
	: GrafoBase(cantVertices)
{
	m_Adyacentes = Array<Puntero<Tabla<V, Puntero<NodoArco<A>>>>>(cantVertices);
	for (nat i = 0; i < cantVertices; i++)
		m_Adyacentes[i] = fabrica->CrearTabla();
	if (esDirigido)
	{
		m_Incidentes = Array<Puntero<Tabla<V, Puntero<NodoArco<A>>>>>(cantVertices);
		for (nat i = 0; i < cantVertices; i++)
			m_Incidentes[i] = fabrica->CrearTabla();
	}
	else
		m_Incidentes = m_Adyacentes;
	this->esDirigido = esDirigido;
	cantArcos = 0;
}

template <class V, class A, typename FHashV>
void GrafoTablasAdy<V,A,FHashV>::AgregarArco(const V& v1, const V& v2, const A& arco)
{
	Puntero<NodoVertice<V>> nodoV1 = ObtenerVertice(v1);
	Puntero<NodoVertice<V>> nodoV2 = ObtenerVertice(v2);

	if (!ExisteArco(v1, v2))
	{
		cantArcos++;
		nodoV1->adyacentes++;
		nodoV2->incidentes++;
		if (!EsDirigido() && nodoV1 != nodoV2)
		{
			nodoV1->incidentes++;
			nodoV2->adyacentes++;
		}
	}
	Puntero<NodoArco<A>> nodoA = new NodoArco<A>(arco);
	m_Adyacentes[nodoV1->id]->Agregar(v2, nodoA);
	m_Incidentes[nodoV2->id]->Agregar(v1, nodoA);
}

template <class V, class A, typename FHashV>
void GrafoTablasAdy<V,A,FHashV>::BorrarArco(const V& v1, const V& v2)
{
	assert(ExisteArco(v1, v2));

	Puntero<NodoVertice<V>> nodoV1 = ObtenerVertice(v1);
	Puntero<NodoVertice<V>> nodoV2 = ObtenerVertice(v2);

	nodoV1->incidentes--;
	nodoV2->adyacentes--;
	m_Adyacentes[nodoV1->id]->Borrar(v2);
	m_Incidentes[nodoV2->id]->Borrar(v1);
	if (!EsDirigido() && nodoV1 != nodoV2)
	{
		nodoV1->incidentes--;
		nodoV2->adyacentes--;
	}
	cantArcos--;
}

template <class V, class A, typename FHashV>
Iterador<V> GrafoTablasAdy<V,A,FHashV>::Adyacentes(const V& v) const
{
	return m_Adyacentes[ObtenerVertice(v)->id]->Claves();
}

template <class V, class A, typename FHashV>
Iterador<V> GrafoTablasAdy<V,A,FHashV>::Incidentes(const V& v) const
{
	return m_Incidentes[ObtenerVertice(v)->id]->Claves();
}

template <class V, class A, typename FHashV>
const A& GrafoTablasAdy<V,A,FHashV>::ObtenerArco(const V& v1, const V& v2) const
{
	Puntero<NodoVertice<V>> nodoV1 = ObtenerVertice(v1);
	Puntero<NodoVertice<V>> nodoV2 = ObtenerVertice(v2);

	if (nodoV1->adyacentes <= nodoV2->incidentes)
		return m_Adyacentes[nodoV1->id]->Obtener(v2)->arco;
	else
		return m_Incidentes[nodoV2->id]->Obtener(v1)->arco;
}

template <class V, class A, typename FHashV>
bool GrafoTablasAdy<V,A,FHashV>::IntentarObtenerArco(const V& v1, const V& v2, A& a) const
{
	Puntero<NodoVertice<V>> nodoV1 = ObtenerVertice(v1);
	Puntero<NodoVertice<V>> nodoV2 = ObtenerVertice(v2);

	Puntero<NodoArco<A>> arco;
	bool existe;

	if (nodoV1->adyacentes <= nodoV2->incidentes)
		existe = m_Adyacentes[nodoV1->id]->IntentarObtener(v2, arco);
	else
		existe = m_Incidentes[nodoV2->id]->IntentarObtener(v1, arco);

	if (existe)
	{
		a = arco->arco;
		return true;
	}
	else
		return false;
}

template <class V, class A, typename FHashV>
nat GrafoTablasAdy<V,A,FHashV>::CantidadArcos() const
{
	assert(cantArcos <= CantidadVertices() * CantidadVertices());
	return cantArcos;
}

template <class V, class A, typename FHashV>
nat GrafoTablasAdy<V,A,FHashV>::CantidadAdyacentes(const V& v) const
{
	return ObtenerVertice(v)->adyacentes;
}

template <class V, class A, typename FHashV>
nat GrafoTablasAdy<V,A,FHashV>::CantidadIncidentes(const V& v) const
{
	return ObtenerVertice(v)->incidentes;
}

template <class V, class A, typename FHashV>
bool GrafoTablasAdy<V,A,FHashV>::ExisteArco(const V& v1, const V& v2) const
{
	Puntero<NodoVertice<V>> nodoV1 = ObtenerVertice(v1);
	Puntero<NodoVertice<V>> nodoV2 = ObtenerVertice(v2);

	if (nodoV1->adyacentes <= nodoV2->incidentes)
		return m_Adyacentes[nodoV1->id]->Pertenece(v2);
	else
		return m_Incidentes[nodoV2->id]->Pertenece(v1);
}

template <class V, class A, typename FHashV>
bool GrafoTablasAdy<V,A,FHashV>::EsDirigido() const
{
	return esDirigido;
}

#endif