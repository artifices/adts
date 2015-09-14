#ifndef TABLA_CPP
#define TABLA_CPP

#include "Tabla.h"
#include "ConversorTuplaDato1.h"
#include "ConversorTuplaDato2.h"
#include "ConvertIteracion.h"

template <class C, class V>
bool Tabla<C,V>::EstaVacia() const
{
	return Largo() == 0;
}

template <class C, class V>
bool Tabla<C,V>::IntentarObtener(const C& c, V& v) const
{
	bool pertenece = Pertenece(c);
	if (pertenece)
		v = Obtener(c);
	return pertenece;
}

template <class C, class V>
Iterador<C> Tabla<C,V>::Claves() const
{
	return this->ObtenerIterador().template Convert<C, ConversorTuplaDato1<C,V>>();
}

template <class C, class V>
Iterador<V> Tabla<C,V>::Valores() const
{
	return this->ObtenerIterador().template Convert<V, ConversorTuplaDato2<C,V>>();
}

#endif