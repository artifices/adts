#ifndef NODOARCO_H
#define NODOARCO_H

template <class A>
class NodoArco
{
public:
	A arco;

	NodoArco(const A& a)
	{
		arco = a;
	}
};

#endif