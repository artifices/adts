#ifndef GRAFO_H
#define GRAFO_H

#include "Iterable.h"
#include "FuncionHash.h"
#include "Tabla.h"
#include "Tupla.h"
#include "Lista.h"
#include "Array.h"
#include "FuncionCosto.h"

typedef unsigned int nat;

template <class V, class A, typename FHashV>
class Grafo abstract : public Iterable<V>
{
public:
	// CONSTRUCTORAS

	virtual void AgregarVertice(const V& v) abstract;
	virtual void BorrarVertice(const V& v) abstract;
	virtual void AgregarArco(const V& v1, const V& v2, const A& arco) abstract;
	virtual void BorrarArco(const V& v1, const V& v2) abstract;

	// SELECTORAS

	virtual Iterador<V> Adyacentes(const V& v) const abstract;
	virtual Iterador<V> Incidentes(const V& v) const abstract;

	virtual const A& ObtenerArco(const V& v1, const V& v2) const abstract;
	virtual bool IntentarObtenerArco(const V& v1, const V& v2, A& a) const;
	virtual nat CantidadVertices() const abstract;
	virtual nat CantidadArcos() const abstract;
	virtual nat CantidadAdyacentes(const V& v) const abstract;
	virtual nat CantidadIncidentes(const V& v) const abstract;
	Tupla<Iterador<Iterador<V>>, nat> CaminosMasCortos(const V& vO, const V& vD, const FuncionCosto<V,A>& fCosto = FuncionCosto<V,A>::Default) const;
	virtual Iterador<Iterador<V>> TodosLosCaminos(const V& vO, const V& vD) const;
	Iterador<V> CaminoMasCortoRestringido(const V& vO, const V& vD, nat K, const FuncionCosto<V,A>& fCosto = FuncionCosto<V,A>::Default) const;
	virtual Iterador<Iterador<V>> CaminosEnAmplitud(const V& v) const;
	virtual Iterador<Iterador<V>> CaminosEnAmplitud(const V& v, nat k) const;
	virtual Iterador<Iterador<V>> CaminosEnProfundidad(const V& v) const;
	virtual Iterador<Iterador<V>> CaminosEnProfundidad(const V& v, nat k) const;
	virtual Iterador<Tupla<V,V,A>> ArcosEnAmplitud(const V& v) const;
	virtual Iterador<Tupla<V,V,A>> ArcosEnProfundidad(const V& v) const;
	Iterador<Tupla<V,V,A>> CubrimientoMinimo(const FuncionCosto<V,A>& fCosto) const;
	Puntero<Tabla<V, Tupla<bool,nat,Puntero<Lista<V>>>>> Dijkstra(const V& vO, const FuncionCosto<V,A>& fCosto = FuncionCosto<V,A>::Default) const;
	Iterador<Iterador<V>> Packing(const FuncionCosto<V,A>& fCosto = FuncionCosto<V,A>::Default) const;
	virtual Iterador<V> PuntosDeInflexion() const;
	virtual nat FlujoMaximo(const V& vO, const V& vD, const FuncionCosto<V,A>& fCosto) const;

	// PREDICADOS

	virtual bool ExisteVertice(const V& v) const abstract;
	virtual bool ExisteArco(const V& v1, const V& v2) const abstract;
	virtual bool EstaLleno() const abstract;
	virtual bool EstaVacio() const abstract;
	virtual bool EsDirigido() const abstract;
	virtual bool EsConexo() const;
	virtual bool HayCamino(const V& vO, const V& vD) const;

protected:
	template <typename FVertice>
	V MenorCostoNoVisitado(const Puntero<Tabla<V, Tupla<bool,nat,FVertice>>>& tabla) const;
	virtual void TodosLosCaminos(const V& vO, const V& vD, Lista<Iterador<V>>& caminos, Lista<V>& caminoActual, Tabla<V,bool>& visitados) const;
	void CaminoMasCortoRestringido(const V& vO, const V& vD, nat K, nat costoActual, Lista<V>& caminoActual, nat& mejorCosto, Iterador<V>& mejorCamino, const FuncionCosto<V,A>& fCosto) const;
	virtual Iterador<Iterador<V>> CaminosDesdeVertice(const V& v, bool enAmplitud, nat k) const;
	virtual Iterador<Tupla<V,V,A>> ArcosDesdeVertice(const V& v, bool enAmplitud) const;
	void Packing(nat pos, Array<bool> packActual, Lista<Iterador<V>>& mejoresPacks, nat tamActual, nat& mejorTam, Array<V> vertices, const FuncionCosto<V,A>& fCosto) const;
	void ArmarCaminos(Lista<V>& caminoActual, const V& vO, const V& vA, Puntero<Tabla<V, Tupla<bool,nat,Puntero<Lista<V>>>>> tabla, Lista<Iterador<V>>& caminos) const;

	virtual Puntero<Grafo<V,nat,FHashV>> CrearGrafoAux(bool esDirigido) const abstract;

	struct NodoArticulacion
	{
	public:
		NodoArticulacion(nat Profundidad = 0, nat Minimo = 0)
		{
			profundidad = Profundidad;
			minimo = Minimo;
		}
		nat profundidad;
		nat minimo;
	};

	void PuntosDeInflexion(Tabla<V,NodoArticulacion>& orden, nat profundidad, const V& v, Lista<V>& articulacion) const;
};

#include "Grafo.cpp"

#endif