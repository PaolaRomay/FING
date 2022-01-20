#include "../include/mapping.h"
#include "../include/listaInfo.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

struct repMap
{
	TLista lst;
};

TMapping crearMapping()
{
	TMapping resultado = new repMap;
	(*resultado).lst = crearLista();
	return resultado;
}

TMapping asociar(nat clave, double valor, TMapping map)
{
	info_t aux;
	nat largo = longitud((*map).lst);
	aux.real = valor;
	aux.natural = clave;
	if ((largo < MAX) && (!esClave(clave, map)))
	{
		insertar(largo + 1, aux, (*map).lst);
	}
	return map;
}

bool esClave(nat clave, TMapping map)
{
	return ((posNat(clave, (*map).lst)) != 0);
}

double valor(nat clave, TMapping map)
{
	info_t aux_clave;
	aux_clave = infoLista(posNat(clave, (*map).lst), (*map).lst);
	return aux_clave.real;
}

TMapping desasociar(nat clave, TMapping map)
{
	info_t aux;
	aux.natural = clave;
	nat pos;
	if (esClave(aux.natural, map))
	{
		aux.real = valor(aux.natural, map);
		pos = (posNat(clave, (*map).lst));
		(*map).lst = remover(pos, (*map).lst);
	}
	return map;
}
