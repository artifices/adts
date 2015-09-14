#pragma once

#include "Array.h"
#include "Cadena.h"
#include "Tupla.h"
#include "Matriz.h"

typedef Tupla</*nombre*/Cadena, /* valor */nat, /* peso */nat, /* cantidad */nat> ItemLimitado;
typedef Tupla</*nombre*/Cadena, /* valor */nat, /* peso */nat> ItemIlimitado;


class Mochila
{
public:
	static Tupla</* valorMaximo */nat, Array<Tupla</* nombre */Cadena, /* cantidad */nat>>> MaximizarValor(Array<ItemLimitado> items, nat pesoMaximo);
	static Tupla</* valorMaximo */nat, Array<Tupla</* nombre */Cadena, /* cantidad */nat>>> MaximizarValor(Array<ItemIlimitado> items, nat pesoMaximo);
private:

	struct NodoMochila
	{
	public:
		NodoMochila(nat Valor = 0, nat Cant = 0)
		{
			valor = Valor;
			cant = Cant;
		}
		
		nat valor;
		nat cant;
	};
};