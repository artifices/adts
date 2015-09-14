#ifndef HEAPEXTENDIDOIMP_CPP
#define HEAPEXTENDIDOIMP_CPP

#include "HeapExtendidoImp.h"
#include "ArrayIteracion.h"
#include "TablaHashAbierto.h"

template <class T, typename FHash>
HeapExtendidoImp<T, FHash>::HeapExtendidoImp(nat tamanio, const Comparador<T>& comp)
{
	arreglo = Array<T>(tamanio);
	HashPosicionesElementos = new TablaHashAbierto<T, nat, FHash>(tamanio);
	this->comp = comp;
	this->fHash = fHash;
	tope = 0;
}

template <class T, typename FHash>
void HeapExtendidoImp<T, FHash>::Agregar(const T &e)
{
	arreglo[tope] = e;
	//FELIPE:
	HashPosicionesElementos->Agregar(e, tope);
	Flotar(tope);
	tope++;
}


template <class T, typename FHash>
void HeapExtendidoImp<T, FHash>::BorrarMin()
{
	assert(!EstaVacia());
	tope--;
	arreglo[PosRaiz()] = arreglo[tope];
	Hundir(PosRaiz());
}

template <class T, typename FHash>
void HeapExtendidoImp<T, FHash>::BorrarElemento(const T &e)
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

template <class T, typename FHash>
T& HeapExtendidoImp<T, FHash>::ObtenerMin() const
{
	assert(!EstaVacia());
	return arreglo[PosRaiz()];
}

template <class T, typename FHash>
nat HeapExtendidoImp<T, FHash>::Largo() const
{
	return tope;
}

template <class T, typename FHash>
Iterador<T> HeapExtendidoImp<T, FHash>::ObtenerIterador() const
{
	return new ArrayIteracion<T>(arreglo, tope);
}

template <class T, typename FHash>
bool HeapExtendidoImp<T, FHash>::EstaVacia() const
{
	return Largo() == 0;
}

template <class T, typename FHash>
bool HeapExtendidoImp<T, FHash>::EstaLlena() const
{
	return Largo() == arreglo.Largo;
}

template <class T, typename FHash>
nat HeapExtendidoImp<T, FHash>::PosHijoIzq(nat pos) const
{
	return pos * 2 + 1;
}

template <class T, typename FHash>
nat HeapExtendidoImp<T, FHash>::PosHijoDer(nat pos) const
{
	return pos * 2 + 2;
}

template <class T, typename FHash>
nat HeapExtendidoImp<T, FHash>::PosPadre(nat pos) const
{
	assert(pos > PosRaiz()); 
	return (pos - 1) / 2;
}

template <class T, typename FHash>
nat HeapExtendidoImp<T, FHash>::PosRaiz() const
{
	return 0;
}

template <class T, typename FHash>
nat HeapExtendidoImp<T, FHash>::Flotar(nat pos)
{
	if (pos > PosRaiz() ){
		if(comp.EsMenor(arreglo[pos], arreglo[PosPadre(pos)])){
			T aux = arreglo[PosPadre(pos)];
			arreglo[PosPadre(pos)] = arreglo[pos];
			arreglo[pos] = aux;

			//FELIPE:
			HashPosicionesElementos->Borrar(arreglo[PosPadre(pos)]);
			HashPosicionesElementos->Borrar(arreglo[pos]);
			HashPosicionesElementos->Agregar(arreglo[PosPadre(pos)], PosPadre(pos));
			HashPosicionesElementos->Agregar(arreglo[pos], pos);

			return Flotar(PosPadre(pos));
		}else{
			return pos;
		}
	}
	return PosRaiz();
}

template <class T, typename FHash>
nat HeapExtendidoImp<T, FHash>::Hundir(nat pos)
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

			//FELIPE:
			HashPosicionesElementos->Borrar(arreglo[j]);
			HashPosicionesElementos->Borrar(arreglo[pos]);
			HashPosicionesElementos->Agregar(arreglo[j], j);
			HashPosicionesElementos->Agregar(arreglo[pos], pos);

			return Hundir(j);
		}else{
			return pos;
		}
	}
	return PosPadre(pos);
}

template <class T, typename FHash>
void HeapExtendidoImp<T, FHash>::Actualizar(const T &e){
	nat posActual = HashPosicionesElementos->Obtener(e);
	nat nuevaPos = Flotar(posActual);
	if(nuevaPos == posActual)
		nuevaPos = Hundir(posActual);
	if(nuevaPos != posActual)
	{
		HashPosicionesElementos->Borrar(e);
		HashPosicionesElementos->Agregar(e, nuevaPos);
	}
}

#endif