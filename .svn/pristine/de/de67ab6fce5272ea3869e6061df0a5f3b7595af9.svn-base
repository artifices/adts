#include "Mochila.h"

Tupla</* valorMaximo */nat, Array<Tupla</* nombre */Cadena, /* cantidad */nat>>> Mochila::MaximizarValor(Array<ItemLimitado> items, nat pesoMaximo)
{
	Matriz<NodoMochila> mat = Matriz<NodoMochila>(items.Largo, pesoMaximo + 1);
	for (nat i = 0; i < items.Largo; i++)
	{
		nat cant = items[i].Dato4;
		nat peso = items[i].Dato3;
		nat valor = items[i].Dato2;
		for (nat p = 0; p <= pesoMaximo; p++)
		{
			if (i == 0)
			{
				nat cantI = p / peso;
				if (cantI > cant)
					cantI = cant;
				mat[i][p] = NodoMochila(valor * cantI, cantI);
			}
			else if (p < peso){
				mat[i][p] = NodoMochila(mat[i-1][p].valor, 0);
				
			}
			else
			{
				nat cantI = mat[i][p-peso].cant;
				nat valorI;
				if (cantI < cant)
				{
					cantI++;
					valorI = mat[i][p-peso].valor + valor;
				}
				else
					valorI = mat[i][p-peso].valor;
				nat cantA = 0;
				nat valorA = mat[i-1][p].valor;
				nat cantD;
				nat valorD;
				if (cant > 0)
				{
					cantD = 1;
					valorD = mat[i-1][p-peso].valor + valor;
				}
				else
				{
					cantD = 0;
					valorD = mat[i-1][p-peso].valor;
				}
				if (valorD >= valorA && valorD >= valorI)
				{
					mat[i][p] = NodoMochila(valorD, cantD);
				}
				else if (valorI >= valorA && valorI >= valorD)
				{
					mat[i][p] = NodoMochila(valorI, cantI);
				}
				else
				{
					mat[i][p] = NodoMochila(valorA, cantA);
				}
			}
		}
	}

	nat valorMaximo = mat[items.Largo - 1][pesoMaximo].valor;
	Array<Tupla<Cadena,nat>> ret = Array<Tupla<Cadena,nat>>(items.Largo);
	nat p = pesoMaximo;
	for (nat i = items.Largo; i > 0; i--)
	{
		Tupla<Cadena,nat> tup = Tupla<Cadena,nat>(items[i-1].Dato1, mat[i-1][p].cant);
		ret[i-1] = tup;
		p -= mat[i-1][p].cant * items[i-1].Dato3;
	}

	return Tupla</* valorMaximo */nat, Array<Tupla</* nombre */Cadena, /* cantidad */nat>>>(valorMaximo, ret);
}


Tupla</* valorMaximo */nat, Array<Tupla</* nombre */Cadena, /* cantidad */nat>>> Mochila::MaximizarValor(Array<ItemIlimitado> items, nat pesoMaximo)
{
	return Tupla</* valorMaximo */nat, Array<Tupla</* nombre */Cadena, /* cantidad */nat>>>(0, Array<Tupla</* nombre */Cadena, /* cantidad */nat>>(0));
}
