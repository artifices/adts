#ifndef TABLAAVL_H
#define TABLAAVL_H

#include "Tupla.h"
#include "NodoAvl.h"
#include "Tabla.h"
#include "Comparador.h"

template <class C, class V>
class TablaAvl : public Tabla<C,V>
{
	typedef Puntero<NodoAvl<Tupla<C,V>>> pNodoAvl;

public:
	TablaAvl(const Comparador<C>& comparador = Comparador<C>::Default);
	
	/* CONSTRUCTORAS */
	bool Agregar(const C& c, const V& v) override;
	bool Borrar(const C& c) override;
	void BorrarTodos() override;

	Puntero<Tabla<C,V>> Clonar() const override;


	/* PREDICADOS */
	bool EstaLlena() const override;
	bool Pertenece(const C& c) const override;


	/* SELECTORAS */
	const V& Obtener(const C& c) const override;
	nat Largo() const override;
	Iterador<Tupla<C,V>> InOrder() const;
	Iterador<Tupla<C,V>> PreOrder() const;
	Iterador<Tupla<C,V>> PosOrder() const;

	Iterador<Tupla<C,V>> ObtenerIterador() const override;

private:
	pNodoAvl raiz;
	nat largo;
	bool varioBalance;

	const V& Obtener(pNodoAvl avl, const C& c) const;
	void Agregar(pNodoAvl& avl, const C& c, const V& v);
	bool Pertenece(pNodoAvl avl, const C& c) const;

	const Comparador<C> comp;
};

#include "TablaAvl.cpp"

#endif
