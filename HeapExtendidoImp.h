#ifndef HEAPEXTENDIDOIMP_H
#define HEAPEXTENDIDOIMP_H

#include "Array.h"
#include "HeapExtendido.h"
#include "Comparador.h"
#include "Tabla.h"
#include "FuncionHash.h"

template <class T, typename FHash>
class HeapExtendidoImp : public HeapExtendido<T>
{
public:
	HeapExtendidoImp(nat tamanio, const Comparador<T>& comp);

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

	/* OTRAS */
	void Actualizar(const T& dato) override;
private:
	nat PosHijoIzq(nat pos) const;
	nat PosHijoDer(nat pos) const;
	nat PosPadre(nat pos) const;
	nat PosRaiz() const;

	nat Flotar(nat pos);
	nat Hundir(nat pos);

	nat tope;
	Array<T> arreglo;
	Comparador<T> comp;
	Puntero<FuncionHash<T>> fHash;
	Puntero<Tabla<T, nat>> HashPosicionesElementos;
};

#include "HeapExtendidoImp.cpp"

#endif