#ifndef TABLAAVL_CPP
#define TABLAAVL_CPP

#include "TablaAvl.h"
#include "TablaAvlInOrder.h"
#include "TablaAvlPreOrder.h"
#include "TablaAvlPosOrder.h"

template <class C, class V>
TablaAvl<C,V>::TablaAvl(const Comparador<C>& comparador)
	: comp(comparador)
{
	varioBalance = false;
	largo = 0;
}

template <class C, class V>
bool TablaAvl<C,V>::Agregar(const C& c, const V& v)
{
	nat largoActual = Largo();
	Agregar(raiz, c, v);
	return largoActual + 1 == Largo();
}

template <class C, class V>
const V& TablaAvl<C,V>::Obtener(const C& c) const
{
	return Obtener(raiz, c);
}

template <class C, class V>
bool TablaAvl<C,V>::Pertenece(const C& c) const
{
	return Pertenece(raiz, c);
}

template <class C, class V>
const V& TablaAvl<C,V>::Obtener(pNodoAvl avl,  const C& c) const
{
	assert(avl!=nullptr);

	if (comp.SonIguales(avl->dato.Dato1, c))
		return avl->dato.Dato2;
	else if (comp.EsMayor(avl->dato.Dato1, c))
		return Obtener(avl->izq, c);
	else
		return Obtener(avl->der, c);
}

template <class C, class V>
bool TablaAvl<C,V>::Pertenece(pNodoAvl avl, const C& c) const
{
	if (avl)
	{
		if (comp.SonIguales(avl->dato.Dato1, c))
			return true;
		else if (comp.EsMayor(avl->dato.Dato1, c))
			return Pertenece(avl->izq, c);
		else
			return Pertenece(avl->der, c);
	}
	else
		return false;
}

template <class C, class V>
void TablaAvl<C,V>::Agregar(pNodoAvl& avl, const C& c, const V& v)
{
	pNodoAvl p1;
	pNodoAvl p2;

	if (!avl)
	{
		avl = new NodoAvl<Tupla<C,V>>(Tupla<C,V>(c, v));
		varioBalance = true;
		largo++;
	}
	else
	{
		if (comp.EsMayor(avl->dato.Dato1, c))
		{
			Agregar(avl->izq, c, v);
			if (varioBalance)
			{
				switch(avl->fb)
				{
					case 1:
						avl->fb = 0;
						varioBalance = false;
						break;
					case 0:
						avl->fb = -1;
						break;
					case -1:
						p1 = avl->izq;
						if (p1->fb == -1)
						{
							//rotacion simple
							avl->izq = p1->der;
							p1->der = avl;
							avl->fb = 0;
							avl = p1;
						}
						else
						{
							//rotacion doble
							p2 = p1->der;
							p1->der = p2->izq;
							p2->izq = p1;
							avl->izq = p2->der;
							p2->der = avl;
							avl->fb = p2->fb == -1 ? 1 : 0;
							p1->fb = p2->fb == 1 ? -1 : 0;
							avl = p2;
						}
						varioBalance = false;
						avl->fb = 0;
						break;
				}
			}
		}
		else if (comp.EsMenor(avl->dato.Dato1, c))
		{
			Agregar(avl->der, c, v);
			if (varioBalance)
			{
				switch (avl->fb)
				{
					case -1:
						avl->fb = 0;
						varioBalance = false;
						break;
					case 0:
						avl->fb = 1;
						break;
					case 1:
						p1 = avl->der;
						if (p1->fb == 1)
						{
							//rotacion simple
							avl->der = p1->izq;
							p1->izq = avl; 
							avl->fb = 0;
							avl = p1;
						}
						else
						{
							//rotacion doble
							p2 = p1->izq;
							p1->izq = p2->der;
							p2->der = p1;
							avl->der = p2->izq;
							p2->izq = avl;
							avl->fb = p2->fb == 1 ? -1 : 0;
							p1->fb = p2->fb == -1 ? 1 : 0;
							avl = p2;
						}
						varioBalance = false;
						avl->fb = 0;
				}
			}
		}
		else
		{
			avl->dato = Tupla<C,V>(c, v);
			varioBalance = false;
		}
	}
}

template <class C, class V>
bool TablaAvl<C,V>::Borrar(const C& c)
{
	if (!Pertenece(c))
		return false;

	Iterador<Tupla<C,V>> it = ObtenerIterador();
	BorrarTodos();
	foreach (auto t, it)
	{
		if (comp.SonDistintos(t.Dato1, c))
			Agregar(t.Dato1, t.Dato2);
	}
	return true;
}

template <class C, class V>
Iterador<Tupla<C,V>> TablaAvl<C,V>::InOrder() const
{
	return new TablaAvlInOrder<C,V>(raiz);
}

template <class C, class V>
Iterador<Tupla<C,V>> TablaAvl<C,V>::PreOrder() const
{
	return new TablaAvlPreOrder<C,V>(raiz);
}

template <class C, class V>
Iterador<Tupla<C,V>> TablaAvl<C,V>::PosOrder() const
{
	return new TablaAvlPosOrder<C,V>(raiz);
}

template <class C, class V>
Iterador<Tupla<C,V>> TablaAvl<C,V>::ObtenerIterador() const
{
	return InOrder();
}

template <class C, class V>
void TablaAvl<C,V>::BorrarTodos()
{
	raiz = nullptr;
	largo = 0;
}

template <class C, class V>
Puntero<Tabla<C,V>> TablaAvl<C,V>::Clonar() const
{
	return nullptr;
}

template <class C, class V>
bool TablaAvl<C,V>::EstaLlena() const
{
	return false;
}

template <class C, class V>
nat TablaAvl<C,V>::Largo() const
{
	return largo;
}


#endif