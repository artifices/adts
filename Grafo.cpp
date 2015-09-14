// A VER SI SE REFLEJA EL CAMBIO

#ifndef GRAFO_CPP
#define GRAFO_CPP

#include "Grafo.h"
#include "FuncionCosto.h"
#include "ListaEnlazada.h"
#include "TablaHashAbierto.h"
#include "ConversorIterableIterador.h"


template <class V, class A, typename FHashV>
bool Grafo<V,A,FHashV>::IntentarObtenerArco(const V& v1, const V& v2, A& a) const
{
	assert(ExisteVertice(v1));
	assert(ExisteVertice(v2));
	bool existe = ExisteArco(v1,v2);
	if (existe)
		a = ObtenerArco(v1,v2);
	return existe;
}

template <class V, class A, typename FHashV>
Tupla<Iterador<Iterador<V>>, nat> Grafo<V,A,FHashV>::CaminosMasCortos(const V& vO, const V& vD, const FuncionCosto<V,A>& fCosto) const
{
	assert(ExisteVertice(vD));
	auto tabla = Dijkstra(vO, fCosto);
	Tupla<bool,nat,Puntero<Lista<V>>> tD;
	if (!tabla->IntentarObtener(vD, tD) || tD.Dato2 == INFINITO)
		return Tupla<Iterador<Iterador<V>>, nat>(nullptr, INFINITO);

	Lista<Iterador<V>>& caminos = ListaEnlazada<Iterador<V>>();
	ArmarCaminos(ListaEnlazada<V>(), vO, vD, tabla, caminos);
	return Tupla<Iterador<Iterador<V>>, nat>(caminos.ObtenerIterador(), tD.Dato2);
}

template <class V, class A, typename FHashV>
void Grafo<V,A,FHashV>::ArmarCaminos(Lista<V>& caminoActual, const V& vO, const V& vA, Puntero<Tabla<V, Tupla<bool,nat,Puntero<Lista<V>>>>> tabla, Lista<Iterador<V>>& caminos) const
{
	caminoActual.AgregarEn(vA, 0);
	if (vA == vO)
		caminos.Agregar(caminoActual.Clonar()->ObtenerIterador());
	else
	{
		foreach (auto ant, tabla->Obtener(vA).Dato3)
			ArmarCaminos(caminoActual, vO, ant, tabla, caminos);
	}
	caminoActual.Borrar(0);
}

template <class V, class A, typename FHashV>
Iterador<Iterador<V>> Grafo<V,A,FHashV>::TodosLosCaminos(const V& vO, const V& vD) const
{
	assert(ExisteVertice(vO));
	assert(ExisteVertice(vD));
	Lista<Iterador<V>>& caminos = ListaEnlazada<Iterador<V>>();
	Tabla<V, bool>& visitados = TablaHashAbierto<V, bool, FHashV>(CantidadVertices());
	TodosLosCaminos(vO, vD, caminos, ListaEnlazada<V>(), visitados);
	return caminos.ObtenerIterador();
}

template <class V, class A, typename FHashV>
Puntero<Tabla<V, Tupla<bool,nat,Puntero<Lista<V>>>>> Grafo<V,A,FHashV>::Dijkstra(const V& vO, const FuncionCosto<V,A>& fCosto) const
{
	assert(ExisteVertice(vO));
	Puntero<Tabla<V, Tupla<bool,nat,Puntero<Lista<V>>>>> tabla = new TablaHashAbierto<V, Tupla<bool,nat,Puntero<Lista<V>>>, FHashV>(CantidadVertices());
	foreach (auto v, this)
		tabla->Agregar(v, Tupla<bool,nat,Puntero<Lista<V>>>(false,INFINITO));
	tabla->Agregar(vO, Tupla<bool,nat,Puntero<Lista<V>>>(false,0));

	nat cantVisitados = 0;
	while (cantVisitados < tabla->Largo())
	{
		V v = MenorCostoNoVisitado(tabla);
		assert(tabla->Pertenece(v));
		Tupla<bool,nat,Puntero<Lista<V>>> tuplaV = tabla->Obtener(v);

		//Grafo no conexo?.. no hay más vertices no conocidos
		if (tuplaV.Dato2 == INFINITO)
			break;

		assert(!tuplaV.Dato1);
		tuplaV.Dato1 = true;
		tabla->Agregar(v, tuplaV);
		cantVisitados++;

		foreach (auto w, Adyacentes(v))
		{
			Tupla<bool,nat,Puntero<Lista<V>>> tuplaW = tabla->Obtener(w);
			nat costo_vO_w = tuplaV.Dato2 + fCosto(v, w, ObtenerArco(v, w));
			if (costo_vO_w < INFINITO)
			{
				if (costo_vO_w < tuplaW.Dato2)
				{
					tuplaW.Dato2 = costo_vO_w;
					tuplaW.Dato3 = new ListaEnlazada<V>();
				}
				if (costo_vO_w == tuplaW.Dato2)
				{
					assert(!tuplaW.Dato1);
					tuplaW.Dato3->Agregar(v);
					tabla->Agregar(w, tuplaW);
				}
			}
		}
	}

	return tabla;
}

template <class V, class A, typename FHashV>
template <typename FVertice>
V Grafo<V,A,FHashV>::MenorCostoNoVisitado(const Puntero<Tabla<V, Tupla<bool,nat,FVertice>>>& tabla) const
{
	nat menorCosto = INFINITO + 1;
	V menorV;
	foreach (auto actual, tabla)
	{
		if (!actual.Dato2.Dato1 && actual.Dato2.Dato2 < menorCosto)
		{
			menorCosto = actual.Dato2.Dato2;
			menorV = actual.Dato1;
		}
	}
	return menorV;
}

template <class V, class A, typename FHashV>
void Grafo<V,A,FHashV>::TodosLosCaminos(const V& vO, const V& vD, Lista<Iterador<V>>& caminos, Lista<V>& caminoActual, Tabla<V,bool>& visitados) const
{
	caminoActual.Agregar(vO);
	visitados.Agregar(vO, true);
	if (vO == vD)
		caminos.Agregar(caminoActual.Clonar()->ObtenerIterador());
	if (vO != vD || caminoActual.Largo() == 1)
	{
		foreach (auto v, Adyacentes(vO))
		{
			if (!visitados.Pertenece(v))
				TodosLosCaminos(v, vD, caminos, caminoActual, visitados);
		}
	}
	caminoActual.Borrar(caminoActual.Largo() - 1);
	visitados.Borrar(vO);
}

template <class V, class A, typename FHashV>
Iterador<V> Grafo<V,A,FHashV>::CaminoMasCortoRestringido(const V& vO, const V& vD, nat K, const FuncionCosto<V,A>& fCosto) const
{
	assert(ExisteVertice(vO));
	assert(ExisteVertice(vD));
	Iterador<V> mejorCamino = nullptr;
	nat mejorCosto = INFINITO;
	CaminoMasCortoRestringido(vO, vD, K, 0, ListaEnlazada<V>(), mejorCosto, mejorCamino, fCosto);
	return mejorCamino;
}

template <class V, class A, typename FHashV>
void Grafo<V,A,FHashV>::CaminoMasCortoRestringido(const V& vO, const V& vD, nat K, nat costoActual, Lista<V>& caminoActual, nat& mejorCosto, Iterador<V>& mejorCamino, const FuncionCosto<V,A>& fCosto) const
{
	caminoActual.Agregar(vO);
	if (vO == vD)
	{
		if (costoActual < mejorCosto)
		{
			mejorCosto = costoActual;
			mejorCamino = caminoActual.Clonar()->ObtenerIterador();
		}
	}
	else if (K > 0)
	{
		foreach (auto v, Adyacentes(vO))
		{
			nat costoAux = costoActual + fCosto(vO, v, ObtenerArco(vO, v));
			if (costoAux < mejorCosto)
				CaminoMasCortoRestringido(v, vD, K - 1, costoAux, caminoActual, mejorCosto, mejorCamino);
		}
	}
	caminoActual.Borrar(caminoActual->Largo() - 1);
}

template <class V, class A, typename FHashV>
bool Grafo<V,A,FHashV>::EsConexo() const
{
	bool conexo = true;
	for (Iterador<V> it = this->ObtenerIterador(); it.HayElemento() && conexo; it++)
	{
		V v = *it;
		Tabla<V, bool>& visitados = TablaHashAbierto<V, bool, FHashV>(CantidadVertices());
		Lista<V>& cola = ListaEnlazada<V>();
		cola.Agregar(v);
		visitados.Agregar(v, true);
		while (!cola.EstaVacia())
		{
			v = cola.Primero();
			cola.Borrar(0);

			foreach (auto w, Adyacentes(v))
			{
				if (!visitados.Pertenece(w))
				{
					cola.Agregar(w);
					visitados.Agregar(w, true);
				}
			}
		}

		conexo = visitados.Largo() == CantidadVertices();
		if (!EsDirigido())
			break;
	}
	return conexo;
}

template <class V, class A, typename FHash>
bool Grafo<V,A,FHash>::HayCamino(const V& vO, const V& vD) const
{
	assert(ExisteVertice(vO));
	assert(ExisteVertice(vD));
	auto tabla = Dijkstra(vO);
	Tupla<bool,nat,Puntero<Lista<V>>> tD;
	return tabla->IntentarObtener(vD, tD) && tD.Dato2 != INFINITO;
}

template <class V, class A, typename FHashV>
Iterador<Iterador<V>> Grafo<V,A,FHashV>::CaminosEnAmplitud(const V& v) const
{
	return CaminosEnAmplitud(v, CantidadVertices());
}

template <class V, class A, typename FHashV>
Iterador<Iterador<V>> Grafo<V,A,FHashV>::CaminosEnAmplitud(const V& v, nat k) const
{
	assert(ExisteVertice(v));
	return CaminosDesdeVertice(v, true, k);
}

template <class V, class A, typename FHashV>
Iterador<Iterador<V>> Grafo<V,A,FHashV>::CaminosEnProfundidad(const V& v) const
{
	return CaminosEnProfundidad(v, CantidadVertices());
}

template <class V, class A, typename FHashV>
Iterador<Iterador<V>> Grafo<V,A,FHashV>::CaminosEnProfundidad(const V& v, nat k) const
{
	assert(ExisteVertice(v));
	return CaminosDesdeVertice(v, false, k);
}

template <class V, class A, typename FHashV>
Iterador<Iterador<V>> Grafo<V,A,FHashV>::CaminosDesdeVertice(const V& v, bool enAmplitud, nat k) const
{
	Puntero<Lista<Puntero<Lista<V>>>> caminos = new ListaEnlazada<Puntero<Lista<V>>>();
	Puntero<Lista<Tupla<Puntero<Lista<V>>, Iterador<V>>>> huella = new ListaEnlazada<Tupla<Puntero<Lista<V>>, Iterador<V>>>();
	Puntero<Lista<V>> caminoActual = new ListaEnlazada<V>();
	caminoActual->Agregar(v);
	huella->Agregar(Tupla<Puntero<Lista<V>>, Iterador<V>>(caminoActual, Adyacentes(v)));
	caminos->Agregar(caminoActual);
	while (huella->Largo() > 0)
	{
		Tupla<Puntero<Lista<V>>, Iterador<V>> tope = huella->ElementoEn(0);
		Iterador<V> adyacentes = tope.Dato2;
		if (adyacentes.HayElemento())
		{
			V ady = *adyacentes;
			++adyacentes;
			caminoActual = tope.Dato1;
			if (!caminoActual->Pertenece(ady))
			{
				caminoActual = caminoActual->Clonar();
				caminoActual->Agregar(ady);
				caminos->Agregar(caminoActual);
				if (caminoActual->Largo() < k)
				{
					if (enAmplitud)
						huella->Agregar(Tupla<Puntero<Lista<V>>, Iterador<V>>(caminoActual, Adyacentes(ady)));
					else
						huella->AgregarEn(Tupla<Puntero<Lista<V>>, Iterador<V>>(caminoActual, Adyacentes(ady)), 0);
				}
			}
		}
		else
			huella->Borrar(0);
	}

	Iterador<Puntero<Iterable<V>>> iterador = caminos->ObtenerIterador();
	return iterador.template Convert<Iterador<V>, ConversorIterableIterador<V>>();
}

template <class V, class A, typename FHashV>
Iterador<Tupla<V,V,A>> Grafo<V,A,FHashV>::ArcosEnAmplitud(const V& v) const
{
	return ArcosDesdeVertice(v, true);
}

template <class V, class A, typename FHashV>
Iterador<Tupla<V,V,A>> Grafo<V,A,FHashV>::ArcosEnProfundidad(const V& v) const
{
	return ArcosDesdeVertice(v, false);
}

template <class V, class A, typename FHashV>
Iterador<Tupla<V,V,A>> Grafo<V,A,FHashV>::ArcosDesdeVertice(const V& v, bool enAmplitud) const
{
	assert(ExisteVertice(v));
	Puntero<Lista<Tupla<V, V, A>>> arcos = new ListaEnlazada<Tupla<V, V, A>>();
	Puntero<Lista<Tupla<V, Iterador<V>>>> huella = new ListaEnlazada<Tupla<V, Iterador<V>>>();
	Puntero<Lista<V>> visitados = new ListaEnlazada<V>();
	visitados->Agregar(v);
	huella->Agregar(Tupla<V, Iterador<V>>(v, Adyacentes(v)));
	while (huella->Largo() > 0)
	{
		Tupla<V, Iterador<V>> tope = huella->ElementoEn(0);
		Iterador<V> adyacentes = tope.Dato2;
		if (adyacentes.HayElemento())
		{
			V inc = tope.Dato1;
			V ady = *adyacentes;
			++adyacentes;
			arcos->Agregar(Tupla<V, V, A>(inc, ady, ObtenerArco(inc, ady)));
			if (!visitados->Pertenece(ady))
			{
				visitados->Agregar(ady);
				if (enAmplitud)
					huella->Agregar(Tupla<V, Iterador<V>>(ady, Adyacentes(ady)));
				else
					huella->AgregarEn(Tupla<V, Iterador<V>>(ady, Adyacentes(ady)), 0);
			}
		}
		else
			huella->Borrar(0);
	}

	return arcos->ObtenerIterador();
}

template <class V>
void AgregarAlcanzables(Puntero<Lista<V>> caminosDesdeV, V w, Puntero<Lista<V>> caminosDesdeW)
{
	if (!caminosDesdeV->Pertenece(w))
		caminosDesdeV->Agregar(w);
	if (caminosDesdeW)
	{
		foreach (auto k, caminosDesdeW)
		{
			if (!caminosDesdeV->Pertenece(k))
				caminosDesdeV->Agregar(k);
		}
	}
}

template <class V, class A, typename FHashV>
Iterador<Tupla<V,V,A>> Grafo<V,A,FHashV>::CubrimientoMinimo(const FuncionCosto<V,A>& fCosto) const
{
	assert(!EsDirigido());
	Puntero<Tabla<V, Tupla<bool,nat,V>>> tabla = new TablaHashAbierto<V, Tupla<bool,nat,V>, FHashV>(CantidadVertices());
	foreach (auto v, this)
		tabla->Agregar(v, Tupla<bool,nat,V>(false, INFINITO));

	nat cantVisitados = 0;
	while (cantVisitados < tabla->Largo())
	{
		V v = MenorCostoNoVisitado(tabla);
		assert(tabla->Pertenece(v));
		Tupla<bool,nat,V> tuplaV = tabla->Obtener(v);
		assert(!tuplaV.Dato1);
		tuplaV = Tupla<bool,nat,V>(true,tuplaV.Dato2,tuplaV.Dato3);
		tabla->Agregar(v, tuplaV);
		cantVisitados++;

		foreach (auto w, Adyacentes(v))
		{
			Tupla<bool,nat,V> tuplaW = tabla->Obtener(w);
			nat costo_v_w = fCosto(v, w, ObtenerArco(v, w));
			if (!tuplaW.Dato1 && costo_v_w < tuplaW.Dato2)
				tabla->Agregar(w, Tupla<bool,nat,V>(false, costo_v_w, v));
		}
	}

	Puntero<Lista<Tupla<V, V, A>>> arcos = new ListaEnlazada<Tupla<V, V, A>>();
	foreach (auto t, tabla)
	{
		V v = t.Dato1;
		Tupla<bool,nat,V> tuplaV = t.Dato2;
		if (tuplaV.Dato2 < INFINITO)
		{
			V w = tuplaV.Dato3;
			arcos->Agregar(Tupla<V, V, A>(v, w, ObtenerArco(w, v)));
		}
	}

	return arcos->ObtenerIterador();
}

template <class V, class A, typename FHashV>
Iterador<Iterador<V>> Grafo<V,A,FHashV>::Packing(const FuncionCosto<V,A>& fCosto) const
{
	assert(!EsDirigido());
	Array<bool> packActual(CantidadVertices());
	Array<V> vertices(CantidadVertices());
	Iterador<V> it = this->ObtenerIterador();
	for (nat i = 0; i < packActual.Largo; i++, it++)
	{
		assert(it.HayElemento());
		packActual[i] = false;
		vertices[i] = *it;
	}

	nat mejorT = 0;
	Puntero<Lista<Iterador<V>>> mejoresPacks = new ListaEnlazada<Iterador<V>>();
	Packing(0, packActual, mejoresPacks, 0, mejorT, vertices, fCosto);
	return mejoresPacks->ObtenerIterador();
}

template <class V, class A, typename FHashV>
void Grafo<V,A,FHashV>::Packing(nat pos, Array<bool> packActual, Lista<Iterador<V>>& mejoresPacks, nat tamActual, nat& mejorTam, Array<V> vertices, const FuncionCosto<V,A>& fCosto) const
{
	if (pos == packActual.Largo)
	{
		if (tamActual >= mejorTam)
		{
			bool esSolucion = true;
			for (nat i = 0; i < packActual.Largo && esSolucion; i++)
			{
				if (packActual[i])
				{
					for (nat j = i + 1; j < packActual.Largo && esSolucion; j++)
						esSolucion = !packActual[j] || !ExisteArco(vertices[i], vertices[j]);
				}
			}
			if (esSolucion)
			{
				if (tamActual > mejorTam)
				{
					mejorTam = tamActual;
					mejoresPacks.BorrarTodos();
				}
				Lista<V>& mejorPack = ListaEnlazada<V>();
				for (nat i = 0; i < packActual.Largo; i++)
				{
					if (packActual[i])
						mejorPack.Agregar(vertices[i]);
				}
				mejoresPacks.Agregar(mejorPack.ObtenerIterador());
			}
		}
	}
	else
	{
		Packing(pos + 1, packActual, mejoresPacks, tamActual, mejorTam, vertices, fCosto);
		packActual[pos] = true;
		Packing(pos + 1, packActual, mejoresPacks, tamActual + fCosto(vertices[pos]), mejorTam, vertices, fCosto);
		packActual[pos] = false;
	}
}

template <class V, class A, typename FHashV>
Iterador<V> Grafo<V,A,FHashV>::PuntosDeInflexion() const
{
	assert(!EsDirigido());
	assert(CantidadVertices() > 0);

	Tabla<V,NodoArticulacion>& orden = TablaHashAbierto<V, NodoArticulacion, FHashV>(CantidadVertices());
	Lista<V>& articulacion = ListaEnlazada<V>();
	foreach (auto v, this)
	{
		if (!orden.Pertenece(v))
			PuntosDeInflexion(orden, 1, v, articulacion);
	}
	return articulacion.ObtenerIterador();
}

template <class V, class A, typename FHashV>
void Grafo<V, A, FHashV>::PuntosDeInflexion(Tabla<V,NodoArticulacion>& orden, nat profundidad, const V& v, Lista<V>& articulacion) const
{
	assert(!orden.Pertenece(v));
	orden.Agregar(v, NodoArticulacion(profundidad, INFINITO));
	Lista<V>& hijos = ListaEnlazada<V>();
	foreach (auto w, Adyacentes(v))
	{
		if (!orden.Pertenece(w))
		{
			hijos.Agregar(w);
			PuntosDeInflexion(orden, profundidad + 1, w, articulacion);
		}
	}
	bool encontreAlPadre = false;
	nat minimo = INFINITO;
	foreach (auto w, Adyacentes(v))
	{
		NodoArticulacion na = orden.Obtener(w);
		if (na.profundidad == profundidad - 1 && !encontreAlPadre)
			encontreAlPadre = true;
		else if (na.profundidad < minimo)
			minimo = na.profundidad;
	}
	bool esarticulado = profundidad == 1 && hijos.Largo() > 1;
	foreach (auto hijo, hijos.ObtenerIterador())
	{
		NodoArticulacion na = orden.Obtener(hijo);
		if (na.minimo < minimo)
			minimo = na.minimo;
		if (profundidad > 1 && na.minimo >= profundidad)
			esarticulado = true;
	}
	orden.Agregar(v, NodoArticulacion(profundidad, minimo));
	if (esarticulado)
	{
		assert(!articulacion.Pertenece(v));
		articulacion.Agregar(v);
	}
}

template <class V, class A, typename FHashV>
nat Grafo<V, A, FHashV>::FlujoMaximo(const V& vO, const V& vD, const FuncionCosto<V,A>& fCosto) const
{
	assert(EsDirigido());
	assert(ExisteVertice(vO));
	assert(ExisteVertice(vD));
	assert(vO != vD);

	Puntero<Grafo<V,nat,FHashV>> aux = CrearGrafoAux(true);

	foreach (auto v, this)
		aux->AgregarVertice(v);

	A arco;
	foreach (auto v, this)
	{
		foreach (auto u, this)
		{
			if (IntentarObtenerArco(v, u, arco))
				aux->AgregarArco(v, u, fCosto(v, u, arco));
		}
	}

	nat flujoMaximo = 0;
	auto caminos = aux->TodosLosCaminos(vO, vD);
	while (caminos.HayElemento())
	{
		foreach (auto camino, caminos)
		{
			nat masAngosto = INFINITO;
			V ant = vO;
			camino.Reiniciar();
			++camino;
			while (masAngosto > 0 && camino.HayElemento())
			{
				V sig = *camino;
				nat tramo;
				if (!aux->IntentarObtenerArco(ant, sig, tramo))
					masAngosto = 0;
				else
				{
					if (tramo < masAngosto)
						masAngosto = tramo;
					ant = sig;
					++camino;
				}
			}
			assert(masAngosto < INFINITO);
			if (masAngosto > 0)
			{
				flujoMaximo += masAngosto;
				ant = vO;
				camino.Reiniciar();
				++camino;
				while (camino.HayElemento())
				{
					V sig = *camino;
					nat tramo = aux->ObtenerArco(ant, sig);
					if (tramo > masAngosto)
						aux->AgregarArco(ant, sig, tramo - masAngosto);
					else
						aux->BorrarArco(ant, sig);
					if (aux->IntentarObtenerArco(sig, ant, tramo))
						aux->AgregarArco(sig, ant, tramo + masAngosto);
					else
						aux->AgregarArco(sig, ant, masAngosto);
					ant = sig;
					++camino;
				}
			}
		}

		caminos = aux->TodosLosCaminos(vO, vD);
	}

	return flujoMaximo;
}

#endif