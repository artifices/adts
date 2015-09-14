#ifndef HEAPIMP_CPP
#define HEAPIMP_CPP

#include "HeapImp.h"
#include "ArrayIteracion.h"

template <class T>
HeapImp<T>::HeapImp(nat tamanio, const Comparador<T>& comp)
{
	arreglo = Array<T>(tamanio);
	this->comp = comp;
	tope = 0;
}

template <class T>
void HeapImp<T>::Agregar(const T &e)
{
	arreglo[tope] = e;
	Flotar(tope);
	tope++;
}

template <class T>
void HeapImp<T>::BorrarMin()
{
	assert(!EstaVacia());
	tope--;
	arreglo[PosRaiz()] = arreglo[tope];
	Hundir(PosRaiz());
}

template <class T>
void HeapImp<T>::BorrarElemento(const T &e)
{
	for (nat i = PosRaiz(); i < tope; i++)
	{
		if (arreglo[i] == e)
		{
			tope--;
			arreglo[i] = arreglo[tope];
			Flotar(i);
			Hundir(i);
			break;
		}
	}
}

template <class T>
T& HeapImp<T>::ObtenerMin() const
{
	assert(!EstaVacia());
	return arreglo[PosRaiz()];
}

template <class T>
nat HeapImp<T>::Largo() const
{
	return tope;
}

template <class T>
Iterador<T> HeapImp<T>::ObtenerIterador() const
{
	return new ArrayIteracion<T>(arreglo, tope);
}

template <class T>
bool HeapImp<T>::EstaVacia() const
{
	return Largo() == 0;
}

template <class T>
bool HeapImp<T>::EstaLlena() const
{
	return Largo() == arreglo.Largo;
}

template <class T>
nat HeapImp<T>::PosHijoIzq(nat pos) const
{
	return pos * 2 + 1;
}

template <class T>
nat HeapImp<T>::PosHijoDer(nat pos) const
{
	return pos * 2 + 2;
}

template <class T>
nat HeapImp<T>::PosPadre(nat pos) const
{
	assert(pos > PosRaiz());
	return (pos - 1) / 2;
}

template <class T>
nat HeapImp<T>::PosRaiz() const
{
	return 0;
}

template <class T>
void HeapImp<T>::Flotar(nat pos)
{
	if (pos > PosRaiz() && comp.EsMenor(arreglo[pos], arreglo[PosPadre(pos)]))
	{
		T aux = arreglo[PosPadre(pos)];
		arreglo[PosPadre(pos)] = arreglo[pos];
		arreglo[pos] = aux;
		Flotar(PosPadre(pos));
	}
}

template <class T>
void HeapImp<T>::Hundir(nat pos)
{
	if (PosHijoIzq(pos) < tope)
	{
		nat j = PosHijoIzq(pos);
		nat k = PosHijoDer(pos);

		if (k < tope && comp.EsMenor(arreglo[k], arreglo[j]))
			j = k;

		if (comp.EsMenor(arreglo[j], arreglo[pos]))
		{
			T aux = arreglo[j];
			arreglo[j] = arreglo[pos];
			arreglo[pos] = aux;
			Hundir(j);
		}
	}
}


#endif