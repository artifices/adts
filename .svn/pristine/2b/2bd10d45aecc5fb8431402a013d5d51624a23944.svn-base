#ifndef TABLAHASHABIERTOITERACION_H
#define TABLAHASHABIERTOITERACION_H

#include "Array.h"
#include "Tupla.h"
#include "Iteracion.h"
#include "Tabla.h"

template <class C, class V>
class TablaHashAbiertoIteracion : public Iteracion<Tupla<C,V>>
{
public:
	TablaHashAbiertoIteracion(Array<Puntero<Tabla<C,V>>> arreglo);

	void Reiniciar() override;
	bool HayElemento() const override;
	const Tupla<C,V>& ElementoActual() const override;
	void Avanzar() override;

	Puntero<Iteracion<Tupla<C,V>>> Clonar() const override;

private:
	TablaHashAbiertoIteracion(Iterador<Puntero<Tabla<C,V>>> iterArreglo, Iterador<Tupla<C,V>> iterLista);

	Iterador<Puntero<Tabla<C,V>>> iterArreglo;
	Iterador<Tupla<C,V>> iterLista;
};

#include "TablaHashAbiertoIteracion.cpp"

#endif