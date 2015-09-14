#ifndef NODOVERTICE_H
#define NODOVERTICE_H

template <class V>
class NodoVertice
{
public:
	V vertice;
	nat id;

	nat adyacentes;
	nat incidentes;

	NodoVertice(const V& v, nat id)
		: vertice(v), id(id)
	{
		adyacentes = 0;
		incidentes = 0;
	}
};

#endif