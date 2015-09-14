#ifndef TablaHashAbierto_CPP
#define TablaHashAbierto_CPP

#include "TablaLista.h"
#include "TablaHashAbierto.h"
#include "TablaHashAbiertoIteracion.h"

template <class C, class V, typename FHash>
TablaHashAbierto<C,V,FHash>::TablaHashAbierto(nat buckets, float fc)
{
	if (buckets % 2 == 0)
		buckets++;
	arreglo = Array<Puntero<Tabla<C,V>>>(buckets);
	largo = 0;
	this->fc = fc;
	for (nat i = 0; i < buckets; i++)
		arreglo[i] = new TablaLista<C,V>();
}

template <class C, class V, typename FHash>
void TablaHashAbierto<C,V,FHash>::BorrarTodos()
{
	for (nat i = 0; i < arreglo.Largo; i++)
		arreglo[i]->BorrarTodos();
}

template <class C, class V, typename FHash>
bool TablaHashAbierto<C,V,FHash>::Agregar(const C& c, const V& v)
{
	nat pos = H(c);
	if (arreglo[pos]->Agregar(c, v))
	{
		assert(!EstaLlena());
		largo++;
		return true;
	}
	return false;
}

template <class C, class V, typename FHash>
bool TablaHashAbierto<C,V,FHash>::Pertenece(const C& c) const
{
	nat pos = H(c);
	return arreglo[pos]->Pertenece(c);
}

template <class C, class V, typename FHash>
const V& TablaHashAbierto<C,V,FHash>::Obtener(const C& c) const
{
	assert(Pertenece(c));
	nat pos = H(c);
	return arreglo[pos]->Obtener(c);
}

template <class C, class V, typename FHash>
bool TablaHashAbierto<C,V,FHash>::IntentarObtener(const C& c, V& v) const
{
	nat pos = H(c);
	return arreglo[pos]->IntentarObtener(c, v);
}

template <class C, class V, typename FHash>
bool TablaHashAbierto<C,V,FHash>::Borrar(const C& c)
{
	assert(Pertenece(c));
	nat pos = H(c);
	if (arreglo[pos]->Borrar(c))
	{
		largo--;
		return true;
	}
	return false;
}

template <class C, class V, typename FHash>
Iterador<Tupla<C,V>> TablaHashAbierto<C,V,FHash>::ObtenerIterador() const
{
	return new TablaHashAbiertoIteracion<C,V>(arreglo);
}

template <class C, class V, typename FHash>
Puntero<Tabla<C,V>> TablaHashAbierto<C,V,FHash>::Clonar() const
{
	Puntero<Tabla<C,V>> tabla = new TablaHashAbierto<C,V,FHash>(arreglo.Largo, fc);
	foreach (auto t, this)
		tabla->Agregar(t.Dato1, t.Dato2);
	return tabla;
}

template <class C, class V, typename FHash>
bool TablaHashAbierto<C,V,FHash>::EstaLlena() const
{
	return fc < (static_cast<float>(Largo()) + 1) / arreglo.Largo;
}

template <class C, class V, typename FHash>
nat TablaHashAbierto<C,V,FHash>::Largo() const
{
	return largo;
}

template <class C, class V, typename FHash>
nat TablaHashAbierto<C,V,FHash>::H(const C& c) const
{
	const FuncionHash<C>& fHash = FHash();
	return fHash(c) % arreglo.Largo;
}

#endif
