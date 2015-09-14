#ifndef HEAPIMP_H
#define HEAPIMP_H

#include "Array.h"
#include "Heap.h"
#include "Comparador.h"

template <class T>
class HeapImp : public Heap<T>
{
public:
	HeapImp(nat tamanio, const Comparador<T>& comp = Comparador<T>::Default);

	void Agregar(const T &e) override;
	void BorrarMin() override;
	void BorrarElemento(const T &e) override;

	/* SELECTORAS */
	T& ObtenerMin() const override;
	nat Largo() const override;
	Iterador<T> ObtenerIterador() const override;

	/* PREDICADOS */
	bool EstaVacia() const override;
	bool EstaLlena() const override;

private:
	nat PosHijoIzq(nat pos) const;
	nat PosHijoDer(nat pos) const;
	nat PosPadre(nat pos) const;
	nat PosRaiz() const;

	void Flotar(nat pos);
	void Hundir(nat pos);

	nat tope;
	Array<T> arreglo;
	Comparador<T> comp;
};

#include "HeapImp.cpp"

#endif