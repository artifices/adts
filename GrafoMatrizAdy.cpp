#ifndef GRAFOMATRIZADY_CPP
#define GRAFOMATRIZADY_CPP

#include <Assert.h>

#include "GrafoMatrizAdy.h"
#include "TablaHashAbierto.h"

template <class V, class A, typename FHashV>
GrafoMatrizAdy<V,A,FHashV>::GrafoMatrizAdy(nat cantVertices, bool esDirigido)
{
	matriz = Matriz<Puntero<NodoArco<A>>>(cantVertices);
	arrayVertices = Array<Puntero<NodoVertice<V>>>(cantVertices);
	tablaVertices = new TablaHashAbierto<V, Puntero<NodoVertice<V>>, FHashV>(cantVertices, 1);
	this->esDirigido = esDirigido;
	this->cantVertices = 0;
	this->cantArcos = 0;
}

template <class V, class A, typename FHashV>
Puntero<Grafo<V,nat,FHashV>> GrafoMatrizAdy<V,A,FHashV>::CrearGrafoAux(bool esDirigido) const
{
	return new GrafoMatrizAdy<V,nat,FHashV>(CantidadVertices(), esDirigido);
}

template <class V, class A, typename FHashV>
void GrafoMatrizAdy<V,A,FHashV>::AgregarVertice(const V& v)
{
	assert(!ExisteVertice(v));

	Puntero<NodoVertice<V>> nodoV = new NodoVertice<V>(v, cantVertices);
	tablaVertices->Agregar(v, nodoV);
	arrayVertices[cantVertices] = nodoV;
	cantVertices++;
}

template <class V, class A, typename FHashV>
void GrafoMatrizAdy<V,A,FHashV>::BorrarVertice(const V& v)
{
	assert(false);
}

template <class V, class A, typename FHashV>
void GrafoMatrizAdy<V,A,FHashV>::AgregarArco(const V& v1, const V& v2, const A& arco)
{
	Puntero<NodoVertice<V>> nodoV1 = ObtenerVertice(v1);
	Puntero<NodoVertice<V>> nodoV2 = ObtenerVertice(v2);

	if (matriz[nodoV1->id][nodoV2->id])
		matriz[nodoV1->id][nodoV2->id]->arco = arco;
	else
	{
		cantArcos++;
		++nodoV1->adyacentes;
		++nodoV2->incidentes;
		Puntero<NodoArco<A>> nodoA = new NodoArco<A>(arco);
		matriz[nodoV1->id][nodoV2->id] = nodoA;
		if (!EsDirigido() && nodoV1->id != nodoV2->id)
		{
			++nodoV1->incidentes;
			++nodoV2->adyacentes;
			matriz[nodoV2->id][nodoV1->id] = nodoA;
		}
	}
}

template <class V, class A, typename FHashV>
void GrafoMatrizAdy<V,A,FHashV>::BorrarArco(const V& v1, const V& v2)
{
	assert(ExisteArco(v1, v2));

	Puntero<NodoVertice<V>> nodoV1 = ObtenerVertice(v1);
	Puntero<NodoVertice<V>> nodoV2 = ObtenerVertice(v2);

	--nodoV1->incidentes;
	--nodoV2->adyacentes;
	matriz[nodoV1->id][nodoV2->id] = nullptr;
	if (!EsDirigido() && nodoV1->id != nodoV2->id)
	{
		--nodoV1->incidentes;
		--nodoV2->adyacentes;
		matriz[nodoV2->id][nodoV1->id] = nullptr;
	}
	cantArcos--;
}

template <class V, class A, typename FHashV>
Iterador<V> GrafoMatrizAdy<V,A,FHashV>::Adyacentes(const V& v) const
{
	return new MatrizAdyacentesIteracion(ObtenerVertice(v), arrayVertices, matriz, EsAdyacente);
}

template <class V, class A, typename FHashV>
Iterador<V> GrafoMatrizAdy<V,A,FHashV>::Incidentes(const V& v) const
{
	return new MatrizAdyacentesIteracion(ObtenerVertice(v), arrayVertices, matriz, EsIncidente);
}

template <class V, class A, typename FHashV>
Puntero<NodoVertice<V>> GrafoMatrizAdy<V,A,FHashV>::ObtenerVertice(const V& v) const
{
	Puntero<NodoVertice<V>> nodoV;
	assert(tablaVertices->IntentarObtener(v, nodoV));
	return nodoV;
}

template <class V, class A, typename FHashV>
const A& GrafoMatrizAdy<V,A,FHashV>::ObtenerArco(const V& v1, const V& v2) const
{
	Puntero<NodoVertice<V>> nodoV1 = ObtenerVertice(v1);
	Puntero<NodoVertice<V>> nodoV2 = ObtenerVertice(v2);
	return matriz[nodoV1->id][nodoV2->id]->arco;
}

template <class V, class A, typename FHashV>
bool GrafoMatrizAdy<V,A,FHashV>::IntentarObtenerArco(const V& v1, const V& v2, A& a) const
{
	Puntero<NodoVertice<V>> nodoV1 = ObtenerVertice(v1);
	Puntero<NodoVertice<V>> nodoV2 = ObtenerVertice(v2);
	auto arco = matriz[nodoV1->id][nodoV2->id];
	if (arco)
	{
		a = arco->arco;
		return true;
	}
	else
		return false;
}

template <class V, class A, typename FHashV>
nat GrafoMatrizAdy<V,A,FHashV>::CantidadVertices() const
{
	return cantVertices;
}

template <class V, class A, typename FHashV>
nat GrafoMatrizAdy<V,A,FHashV>::CantidadArcos() const
{
	assert(cantArcos <= CantidadVertices() * CantidadVertices());
	return cantArcos;
}

template <class V, class A, typename FHashV>
nat GrafoMatrizAdy<V,A,FHashV>::CantidadAdyacentes(const V& v) const
{
	assert(ExisteVertice(v));
	return ObtenerVertice(v)->adyacentes;
}

template <class V, class A, typename FHashV>
nat GrafoMatrizAdy<V,A,FHashV>::CantidadIncidentes(const V& v) const
{
	assert(ExisteVertice(v));
	return ObtenerVertice(v)->incidentes;
}

template <class V, class A, typename FHashV>
bool GrafoMatrizAdy<V,A,FHashV>::ExisteVertice(const V& v) const
{
	return tablaVertices->Pertenece(v);
}

template <class V, class A, typename FHashV>
bool GrafoMatrizAdy<V,A,FHashV>::ExisteArco(const V& v1, const V& v2) const
{
	Puntero<NodoVertice<V>> nodoV1 = ObtenerVertice(v1);
	Puntero<NodoVertice<V>> nodoV2 = ObtenerVertice(v2);

	return matriz[nodoV1->id][nodoV2->id];
}

template <class V, class A, typename FHashV>
bool GrafoMatrizAdy<V,A,FHashV>::EstaLleno() const
{
	return cantVertices == arrayVertices.Largo;
}

template <class V, class A, typename FHashV>
bool GrafoMatrizAdy<V,A,FHashV>::EstaVacio() const
{
	return cantVertices == 0;
}

template <class V, class A, typename FHashV>
bool GrafoMatrizAdy<V,A,FHashV>::EsDirigido() const
{
	return esDirigido;
}

template <class V, class A, typename FHashV>
Iterador<V> GrafoMatrizAdy<V,A,FHashV>::ObtenerIterador() const
{
	return tablaVertices->Claves();
}


template <class V, class A, typename FHashV>
GrafoMatrizAdy<V,A,FHashV>::MatrizAdyacentesIteracion::MatrizAdyacentesIteracion(Puntero<NodoVertice<V>> nodo, Array<Puntero<NodoVertice<V>>> vertices, Matriz<Puntero<NodoArco<A>>> matriz, bool (*posValida)(Puntero<NodoVertice<V>> nodo, Matriz<Puntero<NodoArco<A>>> matriz, nat posActual))
{
	m_Nodo = nodo;
	m_Vertices = vertices;
	m_Matriz = matriz;
	m_PosValida = posValida;
}

template <class V, class A, typename FHashV>
GrafoMatrizAdy<V,A,FHashV>::MatrizAdyacentesIteracion::MatrizAdyacentesIteracion(Puntero<NodoVertice<V>> nodo, Array<Puntero<NodoVertice<V>>> vertices, Matriz<Puntero<NodoArco<A>>> matriz, nat posActual, bool (*posValida)(Puntero<NodoVertice<V>> nodo, Matriz<Puntero<NodoArco<A>>> matriz, nat posActual))
{
	m_Nodo = nodo;
	m_Vertices = vertices;
	m_Matriz = matriz;
	m_PosActual = posActual;
	m_PosValida = posValida;
}

template <class V, class A, typename FHashV>
GrafoMatrizAdy<V,A,FHashV>::MatrizAdyacentesIteracion::~MatrizAdyacentesIteracion()
{
}

template <class V, class A, typename FHashV>
void GrafoMatrizAdy<V,A,FHashV>::MatrizAdyacentesIteracion::Reiniciar()
{
	m_PosActual = 0;
	BuscarSiguiente();
}

template <class V, class A, typename FHashV>
bool GrafoMatrizAdy<V,A,FHashV>::MatrizAdyacentesIteracion::HayElemento() const
{
	return m_PosActual < m_Vertices.Largo && m_PosValida(m_Nodo, m_Matriz, m_PosActual);
}

template <class V, class A, typename FHashV>
const V& GrafoMatrizAdy<V,A,FHashV>::MatrizAdyacentesIteracion::ElementoActual() const
{
	return m_Vertices[m_PosActual]->vertice;
}

template <class V, class A, typename FHashV>
void GrafoMatrizAdy<V,A,FHashV>::MatrizAdyacentesIteracion::Avanzar()
{
	m_PosActual++;
	BuscarSiguiente();
}

template <class V, class A, typename FHashV>
void GrafoMatrizAdy<V,A,FHashV>::MatrizAdyacentesIteracion::BuscarSiguiente()
{
	while (m_PosActual < m_Vertices.Largo && !HayElemento())
		m_PosActual++;
}

template <class V, class A, typename FHashV>
Puntero<Iteracion<V>> GrafoMatrizAdy<V,A,FHashV>::MatrizAdyacentesIteracion::Clonar() const
{
	return new MatrizAdyacentesIteracion(m_Nodo, m_Vertices, m_Matriz, m_PosActual, m_PosValida);
}

template <class V, class A, typename FHashV>
bool GrafoMatrizAdy<V,A,FHashV>::EsAdyacente(Puntero<NodoVertice<V>> nodo, Matriz<Puntero<NodoArco<A>>> matriz, nat posActual)
{
	return matriz[nodo->id][posActual];
}

template <class V, class A, typename FHashV>
bool GrafoMatrizAdy<V,A,FHashV>::EsIncidente(Puntero<NodoVertice<V>> nodo, Matriz<Puntero<NodoArco<A>>> matriz, nat posActual)
{
	return matriz[posActual][nodo->id];
}

#endif