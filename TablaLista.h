#ifndef TABLALISTA_H
#define TABLALISTA_H

#include "Tabla.h"
#include "Lista.h"

template <class C, class V>
class TablaLista : public Tabla<C,V>
{
public:
	TablaLista();

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
	Iterador<Tupla<C,V>> ObtenerIterador() const override;

private:
	TablaLista(Puntero<Lista<Tupla<C,V>>> lista);

	Puntero<Lista<Tupla<C,V>>> m_Lista;
};

#include "TablaLista.cpp"

#endif