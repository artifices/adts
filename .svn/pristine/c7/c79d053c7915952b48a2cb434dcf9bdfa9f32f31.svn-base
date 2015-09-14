#ifndef GRAFOMATRIZADY_H
#define GRAFOMATRIZADY_H

#include "FuncionHash.h"
#include "Grafo.h"
#include "Matriz.h"
#include "NodoArco.h"
#include "NodoVertice.h"
#include "Tabla.h"
#include "Puntero.h"

template <class V, class A, typename FHashV>
class GrafoMatrizAdy : public Grafo<V, A, FHashV>
{
public:
	GrafoMatrizAdy(nat cantVertices, bool esDirigido);

	// CONSTRUCTORAS

	void AgregarVertice(const V& v);
	void BorrarVertice(const V& v);
	void AgregarArco(const V& v1, const V& v2, const A& arco);
	void BorrarArco(const V& v1, const V& v2);

	// SELECTORAS
	Iterador<V> Adyacentes(const V& v) const;
	Iterador<V> Incidentes(const V& v) const;
	const A& ObtenerArco(const V& v1, const V& v2) const;
	bool IntentarObtenerArco(const V& v1, const V& v2, A& a) const;
	nat CantidadVertices() const;
	nat CantidadArcos() const;
	nat CantidadAdyacentes(const V& v) const;
	nat CantidadIncidentes(const V& v) const;

	// PREDICADOS
	bool ExisteVertice(const V& v) const;
	bool ExisteArco(const V& v1, const V& v2) const;
	bool EstaLleno() const;
	bool EstaVacio() const;
	bool EsDirigido() const;

	Iterador<V> ObtenerIterador() const;

protected:
	Puntero<Grafo<V,nat,FHashV>> CrearGrafoAux(bool esDirigido) const;

private:
	Puntero<NodoVertice<V>> ObtenerVertice(const V& v) const;

	Matriz<Puntero<NodoArco<A>>> matriz;
	Array<Puntero<NodoVertice<V>>> arrayVertices;
	Puntero<Tabla <V, Puntero<NodoVertice<V>>>> tablaVertices;
	nat cantVertices;
	nat cantArcos;
	bool esDirigido;

	class MatrizAdyacentesIteracion : public Iteracion<V>
	{
	public:
		MatrizAdyacentesIteracion(Puntero<NodoVertice<V>> nodo, Array<Puntero<NodoVertice<V>>> vertices, Matriz<Puntero<NodoArco<A>>> matriz, bool (*posValida)(Puntero<NodoVertice<V>> nodo, Matriz<Puntero<NodoArco<A>>> matriz, nat posActual));
		virtual ~MatrizAdyacentesIteracion();

		void Reiniciar();
		bool HayElemento() const;
		const V& ElementoActual() const;
		void Avanzar();
		Puntero<Iteracion<V>> Clonar() const;

	private:
		Puntero<NodoVertice<V>> m_Nodo;
		Array<Puntero<NodoVertice<V>>> m_Vertices;
		Matriz<Puntero<NodoArco<A>>> m_Matriz;
		nat m_PosActual;
		bool (*m_PosValida)(Puntero<NodoVertice<V>> nodo, Matriz<Puntero<NodoArco<A>>> matriz, nat posActual);
		void BuscarSiguiente();
		MatrizAdyacentesIteracion(Puntero<NodoVertice<V>> nodo, Array<Puntero<NodoVertice<V>>> vertices, Matriz<Puntero<NodoArco<A>>> matriz, nat posActual, bool (*posValida)(Puntero<NodoVertice<V>> nodo, Matriz<Puntero<NodoArco<A>>> matriz, nat posActual));
	};

	static bool EsAdyacente(Puntero<NodoVertice<V>> nodo, Matriz<Puntero<NodoArco<A>>> matriz, nat posActual);
	static bool EsIncidente(Puntero<NodoVertice<V>> nodo, Matriz<Puntero<NodoArco<A>>> matriz, nat posActual);
};

#include "GrafoMatrizAdy.cpp"

#endif