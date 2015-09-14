#ifndef TablaHashAbierto_H
#define TablaHashAbierto_H

#include "Array.h"
#include "Tupla.h"
#include "FuncionHash.h"
#include "Tabla.h"
#include <assert.h>

#define LAMBDA 1.2

template <class C, class V, typename FHash>
class TablaHashAbierto : public Tabla<C,V> {
public:
	TablaHashAbierto(nat buckets, float fc = LAMBDA);

	bool Agregar(const C& c, const V& v) override;
	bool Borrar(const C& c) override;
	void BorrarTodos() override;

	Puntero<Tabla<C,V>> Clonar() const override;


	/* PREDICADOS */
	bool EstaLlena() const override;
	bool Pertenece(const C& c) const override;


	/* SELECTORAS */
	const V& Obtener(const C& c) const override;
	bool IntentarObtener(const C& c, V& v) const override;
	nat Largo() const override;

	Iterador<Tupla<C,V>> ObtenerIterador() const override;

private:
	Array<Puntero<Tabla<C,V>>> arreglo;
	nat largo;

	nat H(const C& c) const;
	float fc;
};

#include "TablaHashAbierto.cpp"

#endif
